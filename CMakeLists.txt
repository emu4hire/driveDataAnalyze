project( thresholder )
cmake_minimum_required(VERSION 2.8)

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
link_directories( ${OpenCV_LIB_DIR} )

add_executable( lineFitter lineFitter.cpp )
add_executable( vdmaker vdmaker.cpp )
add_executable( genUniquePose generateUniquePose.cpp)
add_executable( genSnapRequest generateSnapRequest.cpp)
add_executable( parseResponse parseSnapResponse.cpp)

target_link_libraries( lineFitter ${OpenCV_LIBS} )
target_link_libraries( vdmaker ${OpenCV_LIBS} )
