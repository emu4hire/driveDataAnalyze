project( driveDataAnalyze )
cmake_minimum_required(VERSION 2.8)

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable( lineFitter lineFitter.cpp )
add_executable( vdmaker vdmaker.cpp )
add_executable( genUniquePose generateUniquePose.cpp)
add_executable( genSnapRequest generateSnapRequest.cpp)
add_executable( parseResponse parseSnapResponse.cpp)
add_executable( genSVRequest generateSVRequests.cpp)
add_executable( analyze svSnapper.cpp )
add_executable( genImgList generateImageList.cpp)
add_executable( correctSV correctSVImages.cpp)

target_link_libraries( lineFitter ${OpenCV_LIBS} )
target_link_libraries( vdmaker ${OpenCV_LIBS} )
target_link_libraries( correctSV ${OpenCV_LIBS} )
