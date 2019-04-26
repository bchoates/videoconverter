file(GLOB Sources "*.cpp")

set(OpenCV_DIR "d:/lib/opencv/build")
find_package(OpenCV REQUIRED )
include_directories(${OpenCV_INCLUDE_DIRS})
link_libraries(${OpenCV_LIBS})

add_library(videoconverter ${Sources})
set_property(TARGET videoconverter PROPERTY CXX_STANDARD 17)
