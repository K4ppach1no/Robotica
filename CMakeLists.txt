#cmake boilerplate
cmake_minimum_required(VERSION 3.18.4)
project(Robotics)

#Step 1: tell cmake where the sourcecode is located
set(SOURCES
    Robotics/Robotics.cpp
)
#Step 2: tell cmake where to find OpenCV
include(/var/dev/open-cv/opencv-4.7.0/CMakeList.txt)

#Step 3: ???

#Step 4: success?