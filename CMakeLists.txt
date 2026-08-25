cmake_minimum_required(VERSION 3.16)

project(Gestures)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenCV REQUIRED)

add_executable(gestures main.cpp)

target_include_directories(gestures PRIVATE ${OpenCV_INCLUDE_DIRS})

target_link_libraries(gestures PRIVATE ${OpenCV_LIBS})