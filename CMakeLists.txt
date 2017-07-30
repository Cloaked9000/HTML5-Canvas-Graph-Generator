cmake_minimum_required(VERSION 3.8)
project(HTMLGraphGenerator)

include_directories(include)
link_directories(/usr/local/lib)

set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake_modules)
set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp include/HTMLGraph.h src/HTMLBarChart.cpp include/HTMLBarChart.h src/HTMLLineChart.cpp include/HTMLLineChart.h include/CanvasContext.h)
add_executable(HTMLGraphGenerator ${SOURCE_FILES})

# Find and link libraries to the executable
FIND_PACKAGE(FRNETLIB)
INCLUDE_DIRECTORIES(${FRNETLIB_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(HTMLGraphGenerator ${FRNETLIB_LIBRARIES})

