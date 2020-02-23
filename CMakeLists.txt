cmake_minimum_required(VERSION 3.15)
project(creatPatch)
set(CMAKE_CXX_STANDARD 14)

find_package(OpenCV REQUIRED)
find_package(GDAL REQUIRED)

set(SRCS
        Computing.cpp
        main.cpp
        Patch.cpp
        )
set(HEADERS
        Computing.h
        Patch.h
        )
add_executable(
        creatPatch
        ${SRCS}
        ${HEADERS}
)

link_directories(/usr/lib/x86_64-linux-gnu/libshp.so)

include_directories(${OpenCV_INCLUDE_DIR})
include_directories(include ${GDAL_INCLUDE_DIRS})

target_link_libraries(creatPatch libshp.so ${OpenCV_LIBS} ${GDAL_LIBRARIES})

