#!/bin/sh
MAIN_PATH="$(dirname "$(readlink -f "$0")")"
PROGRAM_FILES_PATH=$(powershell -c '${env:ProgramFiles}')
ENV_VARIABLES=$(powershell -c "[Environment]::GetEnvironmentVariable('PATH', 'Machine')")
PACKAGES_DIR="$PROGRAM_FILES_PATH/packages/"

# install chocolatey
function install_chocolatey() {

  # check if chocolatey is already installed
  if ! command -v choco &>/dev/null; then
    # install chocolatey
    powershell.exe -ExecutionPolicy Bypass -Command "iex ((New-Object System.Net.WebClient).DownloadString('https://chocolatey.org/install.ps1'))"
  else
    echo "chocolatey is already installed"
  fi
}

function install_using_choco() {
  for package_name in "$@"; do
    # check if $package_name is already installed
    if command -v $package_name &>/dev/null; then
      echo "$package_name is already installed"
      continue
    fi

    # install $package_name using chocolatey
    powershell.exe -ExecutionPolicy Bypass -Command "choco install $package_name -y"

    #get exe path in chocolatey
    EXE_PATH_CHOCOLATEY=$(powershell.exe -ExecutionPolicy Bypass -Command "(Get-ChildItem -Path $env:ChocolateyInstall -Filter \"$package_name.exe\" -Recurse | Select-Object -First 1).DirectoryName")

    #exe path to program files, choco doesn't always install it to the choco bin
    EXE_PATH_PROGRAMFILES=$(powershell.exe -ExecutionPolicy Bypass -Command "(Get-ChildItem -Path \"$PROGRAM_FILES_PATH\" -Filter \"$package_name.exe\" -Recurse | Select-Object -First 1).DirectoryName")

    #if we can find package.exe in chocolatey files add it to the env variables
    if [[ -n "$EXE_PATH_CHOCOLATEY" ]]; then
      ENV_VARIABLES="$EXE_PATH_CHOCOLATEY;$ENV_VARIABLES"
      export PATH="$(echo $EXE_PATH_CHOCOLATEY | sed 's/^\([a-zA-Z]\):/\/\1/'):$PATH"

    #else we look in the program files directory, if it's installed there we add it
    elif [[ -n "$EXE_PATH_PROGRAMFILES" ]]; then
      ENV_VARIABLES="$EXE_PATH_PROGRAMFILES;$ENV_VARIABLES"
      export PATH="$(echo $EXE_PATH_PROGRAMFILES | sed 's/^\([a-zA-Z]\):/\/\1/'):$PATH"

    #else give error
    else
      echo "can't find install directory"
    fi
  done
  #add env variables permanently
  powershell.exe -Command "[Environment]::SetEnvironmentVariable('PATH', '"$ENV_VARIABLES"', 'Machine')"
}

function add_package_exe() {
  local tar_url=$1
  local name=$2

  local LOCAL_PACKAGE_DIR="$PACKAGES_DIR$name"

  #check if package already exists
  if [[ -d "$LOCAL_PACKAGE_DIR" ]]; then
    echo "$name already exists"
    return
  fi
  
  # make directory for package
  mkdir -p "$LOCAL_PACKAGE_DIR"

  cd "$LOCAL_PACKAGE_DIR" || die
  wget "$tar_url" -O "$name.exe"
  
  chmod +x "$name".exe
  ./"$name".exe -o . -y -gm2
  rm "$name.exe"
}

function install_from_github_using_cmake() {
  local url=$1
  local name=$2
  local LOCAL_PACKAGE_DIR="$PACKAGES_DIR$name"

  #check if package already exists
  if [[ -d "$LOCAL_PACKAGE_DIR" ]]; then
    echo "$name already exists"
    return
  fi

  # download the package from gitHub
  curl -L -o "$name.zip" "$url"

  # make directory for package
  mkdir -p "$LOCAL_PACKAGE_DIR"

  # unzip the file
  unzip -d "$LOCAL_PACKAGE_DIR" "$name.zip"

  # remove the downloaded zip file
  rm "$name.zip"

  cd "$LOCAL_PACKAGE_DIR" || exit

  # if the zip has only one directory and 0 files in it go into that
  if [ "$(find . -maxdepth 1 -type d | wc -l)" -eq 2 ] && [ "$(find . -maxdepth 1 -type f | wc -l)" -eq 0 ]; then
    cd "$(find . -maxdepth 1 -type d -not -path "." -print)" || exit
  fi

  # release
  cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
  cmake --build build --config Release
  cmake --install build --config Release --prefix "$LOCAL_PACKAGE_DIR/release"

  # debugs
  cmake -S . -B build-debug -DCMAKE_BUILD_TYPE=Debug
  cmake --build build-debug --config Debug
  cmake --install build-debug --config Debug --prefix "$LOCAL_PACKAGE_DIR/debug"
}

# check if cmd is running as admin
if ! net session >nul 2>&1; then
  echo "not admin"
  powershell -WindowStyle Hidden "start cmd \"/k cd /d $MAIN_PATH\\ && $0 && exit\" -WindowStyle Hidden -Verb runAs"
  exit
fi

#install packages
install_chocolatey
install_using_choco "unzip" "cmake" "tar" "wget"

#install opencv
add_package_exe "https://github.com/opencv/opencv/releases/download/4.7.0/opencv-4.7.0-windows.exe" "opencv"

#use like this -> install_from_github_using_cmake "https://github.com/martinus/nanobench/archive/refs/tags/v4.3.11.zip" "nanobench"

rm nul
echo "All done"
