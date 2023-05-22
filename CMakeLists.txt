#cmake boilerplate
cmake_minimum_required(VERSION 3.18.4)
project(Robotics)

#Step 1: tell cmake where the sourcecode is located
set(SOURCES
    Robotics/Robotics.cpp
)
#Step 2: tell cmake where to find OpenCV
include_directories(
    /var/dev/open-cv/opencv-4.7.0/build/include
)
link_directories(
    /var/dev/open-cv/opencv-4.7.0/build/bin
)

#Step 3: ???
file(GLOB SOURCES "*.cpp")
add_executable(Robotics /var/dev/Robotics/Robotics.cpp)
target_link_libraries(
    opencv_annotation
    opencv_test_core
    opencv_interactive-calibration
    opencv_test_dnn
    opencv_model_diagnostics
    opencv_test_features2d
    opencv_perf_calib3d
    opencv_test_flann
    opencv_perf_core
    opencv_test_gapi
    opencv_perf_dnn
    opencv_test_highgui
    opencv_perf_features2d
    opencv_test_imgcodecs
    opencv_perf_gapi
    opencv_test_imgproc
    opencv_perf_imgcodecs
    opencv_test_ml
    opencv_perf_imgproc
    opencv_test_objdetect
    opencv_perf_objdetect
    opencv_test_photo
    opencv_perf_photo
    opencv_test_stitching
    opencv_perf_stitching
    opencv_test_video
    opencv_perf_video
    opencv_test_videoio
    opencv_perf_videoio
    opencv_version
    opencv_test_calib3d
    opencv_visualisation
)

#Step 4: success?