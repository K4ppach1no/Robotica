#cmake boilerplate
cmake_minimum_required(VERSION 3.18.4)
project(Robotics)

#Step 4: success?
add_executable(Robotics /var/dev/Robotica/Robotics/Robotics.cpp)

#Step 1: include the library
target_include_directories(
    Robotics
    PUBLIC /var/dev/Robotica/opencv/include/opencv2/
)

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