#cmake boilerplate
cmake_minimum_required(VERSION 3.18.4)
project(Robotics)

#Step 1: include the library
target_include_directories(
    /var/dev/open-cv/opencv-4.7.0/build/include
)

target_link_libraries(
    /var/dev/open-cv/opencv-4.7.0/build/lib
)


#Step 4: success?
add_executable(Robotics /var/dev/Robotica/Robotics/Robotics.cpp)