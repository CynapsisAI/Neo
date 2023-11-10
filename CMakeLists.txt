cmake_minimum_required(VERSION 3.25.2)
project(Neo)

set(CMAKE_CXX_STANDARD 20)

#Set your directories.  The dot representes the root application folder.
#Thus my the path to my domain folder:
set(src ./src)
set(include ./include)

#Include the directories and now your cpp files will recognize your headers
include_directories(${src})
include_directories(${include})


add_executable(Neo main.cpp
        include/neo.hpp
        include/array.hpp
        include/operations.hpp
        src/operations.cpp
)