#!/bin/sh
MAIN_PATH="$(dirname "$(readlink -f "$0")")"
PROGRAM_FILES_PATH=$(powershell -c '${env:ProgramFiles}')
ENV_VARIABLES=$(powershell -c "[Environment]::GetEnvironmentVariable('PATH', 'Machine')")
DEFAULT_CHOCOLATEY_PATH="C:/ProgramData/Chocolatey"
PACKAGES_DIR="$PROGRAM_FILES_PATH/packages/"

function add_package_exe(){
	local tar_url=$1
	local name=$2
	
	local LOCAL_PACKAGE_DIR="$PACKAGES_DIR"
	
	if [ -d "$LOCAL_PACKAGE_DIR$name" ]; then
		echo "$LOCAL_PACKAGE_DIR already exists"
		return
	fi
	cd "$LOCAL_PACKAGE_DIR"
	wget "$tar_url" -O "$name.exe"
	powershell -WindowStyle Hidden "start cmd \"/k $name.exe -o . -y -gm2\" -v runAs"
	rm "$name.exe"
}

# check if cmd is running as admin
if ! net session >nul 2>&1; then
	echo "not admin"
	powershell -WindowStyle Hidden "start cmd \"/k cd /d $MAIN_PATH\\ && $0\" -v runAs"
	exit 0;
fi

# install chocolatey
if ! command -v choco > /dev/null 2>&1 && [[ ! -d "$DEFAULT_CHOCOLATEY_PATH" ]]; then
	echo "installing chocolatey"
	#install chocolatey
	powershell -NoProfile -InputFormat None -ExecutionPolicy Bypass -Command "iex ((New-Object System.Net.WebClient).DownloadString('https://chocolatey.org/install.ps1'))"
	#add libs to env variables
	ENV_VARIABLES="$(powershell -c '${env:ChocolateyInstall}')/bin/lib*;$ENV_VARIABLES"
	echo "chocolatey installed"
else
	echo "chocolatey already installed"
fi
# Dependencies
declare -A dependencies=(
  #[Git]=2.40.0 #- probably already installed
  [wget]=1.21.1
  [CMake]=3.26.3
  [Tar]=1.34
  [make]=4.3
  #[7zip]=19.0
)

# Check if each dependency is installed and install missing ones
for dep in "${!dependencies[@]}"; do
	version=${dependencies[$dep]}
	#if dependency has alreadready been installed
	if command -v "$dep" > /dev/null 2>&1; then
		installed_version=`$dep --version | grep -Eo '[0-9]+(\.[0-9]+)*'`
		#if the installed version is different than specified version
		#and if it has been installed by choco, we don't want to double install stuff
		if [[ "$installed_version" != "$version" ]] && [ -n "$(powershell -command "choco list -l | findstr -I $dep")" ]; then
			echo "upgrading $dep to $version"
			choco upgrade "$dep" --version="$version" -y
		fi
	else
		echo "installing $dep"
		choco install "$dep" --version="$version" -y -ia "/INSTALLDIR:$PROGRAM_FILES_PATH/$dep"
		
		#set path to env variables if it's not already set
		if  [[ -d "$PROGRAM_FILES_PATH/$dep/bin" ]]; then
			ENV_VARIABLES="$PROGRAM_FILES_PATH/$dep/bin;$ENV_VARIABLES"
			powershell -Command "[Environment]::SetEnvironmentVariable('PATH', '"$ENV_VARIABLES"', 'Machine')"
			echo "$dep installed and added to env variables"
		fi
	fi
done
add_package_exe "https://github.com/opencv/opencv/releases/download/4.7.0/opencv-4.7.0-windows.exe" "opencv"

echo "All done"