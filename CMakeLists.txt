cmake_minimum_required(VERSION 3.9)
project(image_enhancement_implementation)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES src/main.cpp src/filters/FilterInterface.h src/filters/SpatialDomainFilter.h src/filters/MedianFilter.cpp src/filters/MedianFilter.h src/filters/LowPassFilter.cpp src/filters/LowPassFilter.h src/filters/HighPassFilter.h src/filters/HighPassFilter.cpp src/kernel.cpp src/kernel.h src/KernelImageConvolver.cpp src/KernelImageConvolver.h src/filters/GaussianFilter.cpp src/filters/GaussianFilter.h src/FilterApplicator.cpp src/FilterApplicator.h src/ImageEnhancer.cpp src/ImageEnhancer.h)

add_executable(image_enhancement_implementation ${SOURCE_FILES})

find_package(OpenCV REQUIRED)

set(OpenCV_LIBS
        opencv_core
        opencv_highgui
        opencv_imgproc
        opencv_imgcodecs
        )


target_link_libraries(image_enhancement_implementation ${OpenCV_LIBS} )