cmake_minimum_required(VERSION 2.8)
project( cvPlay )
find_package( OpenCV REQUIRED )
add_executable( GoldenGateBackGround GoldenGateBackGround.cpp )
target_link_libraries( GoldenGateBackGround ${OpenCV_LIBS} )

add_executable( leadingEdge leadingEdge.cpp )
target_link_libraries( leadingEdge ${OpenCV_LIBS} )
