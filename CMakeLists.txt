#cmake boilerplate
cmake_minimum_required(VERSION 3.18.4)
project(Robotics)

set(path "{path}")


#Tell CMake that we're making an executable and where to find the cpp files

add_executable(Robotics 
    {path}/Robotics/controller.cpp
    {path}/Robotics/controller.h
)

set_target_properties(Robotics PROPERTIES LINKER_LANGUAGE CXX)

#Add the include directory
target_include_directories(
    Robotics
    PUBLIC {path}opencv/include/
)

#Link the libraries
target_link_libraries(
    Robotics
   
    {path}opencv/lib/libopencv_calib3d.so
    {path}opencv/lib/libopencv_core.so
    {path}opencv/lib/libopencv_dnn.so
    {path}opencv/lib/libopencv_features2d.so
    {path}opencv/lib/libopencv_flann.so
    {path}opencv/lib/libopencv_gapi.so
    {path}opencv/lib/libopencv_highgui.so
    {path}opencv/lib/libopencv_imgcodecs.so
    {path}opencv/lib/libopencv_imgproc.so
    {path}opencv/lib/libopencv_ml.so
    {path}opencv/lib/libopencv_objdetect.so
    {path}opencv/lib/libopencv_photo.so
    {path}opencv/lib/libopencv_stitching.so
    {path}opencv/lib/libopencv_ts.a
    {path}opencv/lib/libopencv_video.so
    {path}opencv/lib/libopencv_videoio.so
)