cmake_minimum_required(VERSION 3.14) 
project(ImageAlgorithms)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_library(imageLib include/image_algorithms.hpp include/Image.hpp include/stb_image.h include/stb_image_write.h src/image_algorithms.cpp src/Image.cpp)
set_target_properties(imageLib PROPERTIES LINKER_LANGUAGE CXX)
add_executable(ImageAlgorithms main.cpp)
target_link_libraries(ImageAlgorithms ${OpenCV_LIBS} imageLib)