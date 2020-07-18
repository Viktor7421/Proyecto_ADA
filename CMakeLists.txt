cmake_minimum_required(VERSION 2.8)
project( Proyecto_ADA CXX )
find_package( OpenCV REQUIRED )

set( sources main.cpp )

add_executable( Proyecto_ADA ${sources} )

target_compile_options( Proyecto_ADA PUBLIC -std=c++11 -fpermissive -w -Wall )

target_link_libraries( Proyecto_ADA ${OpenCV_LIBS} -L/usr/lib64 -ldl )