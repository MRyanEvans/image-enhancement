cmake_minimum_required(VERSION 3.9)
project(image_enhancement_implementation)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES src/main.cpp src/filters/FilterInterface.h src/filters/SpatialDomainFilter.h src/filters/MedianSpatialFilter.cpp src/filters/MedianSpatialFilter.h src/filters/LowPassSpatialFilter.cpp src/filters/LowPassSpatialFilter.h src/kernel.cpp src/kernel.h src/KernelImageConvolver.cpp src/KernelImageConvolver.h src/filters/GaussianSpatialFilter.cpp src/filters/GaussianSpatialFilter.h src/ImageEnhancer.cpp src/ImageEnhancer.h src/filters/FrequencyDomainFilter.h src/filters/LowPassFrequencyFilter.cpp src/filters/LowPassFrequencyFilter.h src/Utilities.cpp src/Utilities.h src/filters/FrequencyDomainFilter.cpp)

add_executable(image_enhancement_implementation ${SOURCE_FILES})

find_package(OpenCV REQUIRED)

set(OpenCV_LIBS
        opencv_core
        opencv_highgui
        opencv_imgproc
        opencv_imgcodecs
        )


target_link_libraries(image_enhancement_implementation ${OpenCV_LIBS} )