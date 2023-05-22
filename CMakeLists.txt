#cmake boilerplate
cmake_minimum_required(VERSION 3.18.4)
project(Robotics)

#Step 4: success?
add_executable(Robotics /var/dev/Robotica/Robotics/Robotics.cpp)

#Step 1: include the library
target_include_directories(
    Robotics
    /var/dev/open-cv/opencv-4.7.0/build/include
)

target_link_libraries(
    Robotics
   
    /var/dev/open-cv/opencv-4.7.0/build/lib/libopencv_calib3d.so
    /var/dev/open-cv/opencv-4.7.0/build/lib/libopencv_core.so
    /var/dev/open-cv/opencv-4.7.0/build/lib/libopencv_dnn.so
    /var/dev/open-cv/opencv-4.7.0/build/lib/libopencv_features2d.so
    /var/dev/open-cv/opencv-4.7.0/build/lib/libopencv_flann.so
    /var/dev/open-cv/opencv-4.7.0/build/lib/libopencv_gapi.so
    /var/dev/open-cv/opencv-4.7.0/build/lib/libopencv_highgui.so
    /var/dev/open-cv/opencv-4.7.0/build/lib/libopencv_imgcodecs.so
    /var/dev/open-cv/opencv-4.7.0/build/lib/libopencv_imgproc.so
    /var/dev/open-cv/opencv-4.7.0/build/lib/libopencv_ml.so
    /var/dev/open-cv/opencv-4.7.0/build/lib/libopencv_objdetect.so
    /var/dev/open-cv/opencv-4.7.0/build/lib/libopencv_photo.so
    /var/dev/open-cv/opencv-4.7.0/build/lib/libopencv_stitching.so
    /var/dev/open-cv/opencv-4.7.0/build/lib/libopencv_ts.a
    /var/dev/open-cv/opencv-4.7.0/build/lib/libopencv_video.so
    /var/dev/open-cv/opencv-4.7.0/build/lib/libopencv_videoio.so
)