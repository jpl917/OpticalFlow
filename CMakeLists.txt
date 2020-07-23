cmake_minimum_required(VERSION 2.8)
project(optiflow)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})


include_directories(${PROJECT_SOURCE_DIR}/src)

add_library(${PROJECT_NAME} STATIC 
src/GaussianPyramid.cpp
src/OpticalFlow.cpp 
src/Stochastic.cpp
src/FlowVisualizer.cpp
)

target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})



#add_executable(OpticalFlow_opencv OpticalFlow_opencv.cpp )
#target_link_libraries(OpticalFlow_opencv ${PROJECT_NAME})


add_executable(Coarse2FineTwoFrames Coarse2FineTwoFrames.cpp)
target_link_libraries(Coarse2FineTwoFrames ${PROJECT_NAME} )
