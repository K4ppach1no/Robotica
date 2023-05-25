#cmake boilerplate
cmake_minimum_required(VERSION 3.18.4)
project(Robotics)


#Tell CMake that we're making an executable and where to find the cpp files

add_executable(Robotics
    /var/dev/Robotica/Robotics/pch.h
    /var/dev/Robotica/Robotics/camera.cpp
    /var/dev/Robotica/Robotics/camera.h 
    /var/dev/Robotica/Robotics/controller.cpp
    /var/dev/Robotica/Robotics/controller.h
)

set_target_properties(Robotics PROPERTIES LINKER_LANGUAGE CXX)

#Add the include directory
target_include_directories(
    Robotics
    PUBLIC /var/dev/Robotica/opencv/include/
)

#Link the libraries
target_link_libraries(
    Robotics
   
    /var/dev/Robotica/opencv/lib/libopencv_calib3d.so
    /var/dev/Robotica/opencv/lib/libopencv_core.so
    /var/dev/Robotica/opencv/lib/libopencv_dnn.so
    /var/dev/Robotica/opencv/lib/libopencv_features2d.so
    /var/dev/Robotica/opencv/lib/libopencv_flann.so
    /var/dev/Robotica/opencv/lib/libopencv_gapi.so
    /var/dev/Robotica/opencv/lib/libopencv_highgui.so
    /var/dev/Robotica/opencv/lib/libopencv_imgcodecs.so
    /var/dev/Robotica/opencv/lib/libopencv_imgproc.so
    /var/dev/Robotica/opencv/lib/libopencv_ml.so
    /var/dev/Robotica/opencv/lib/libopencv_objdetect.so
    /var/dev/Robotica/opencv/lib/libopencv_photo.so
    /var/dev/Robotica/opencv/lib/libopencv_stitching.so
    /var/dev/Robotica/opencv/lib/libopencv_ts.a
    /var/dev/Robotica/opencv/lib/libopencv_video.so
    /var/dev/Robotica/opencv/lib/libopencv_videoio.so
)