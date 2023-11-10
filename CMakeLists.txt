cmake_minimum_required(VERSION 3.26)
project(Neo)

set(CMAKE_CXX_STANDARD 20)

#Set your directories.  The dot representes the root application folder.
#Thus my the path to my domain folder:
set(src ./src)
set(inc ./inc)

#Include the directories and now your cpp files will recognize your headers
include_directories(${src})
include_directories(${inc})


add_executable(Neo main.cpp
        inc/neo.hpp
        inc/array.hpp
)