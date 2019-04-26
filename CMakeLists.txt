cmake_minimum_required(VERSION 3.14)

#enable_testing()

project(videoconversion
	VERSION 1.0
	LANGUAGES CXX
)

add_subdirectory(src)

set(OpenCV_DIR "d:/lib/opencv/build")
find_package(OpenCV REQUIRED )
include_directories(${OpenCV_INCLUDE_DIRS})
link_libraries(${OpenCV_LIBS})

include_directories(src)
link_directories(src)
add_executable(videoconversion main.cpp)
set_property(TARGET videoconversion PROPERTY CXX_STANDARD 17)
target_link_libraries(videoconversion videoconverter)
