cmake_minimum_required(VERSION 3.30)
project(Spreed_Sheet)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_COMPILER g++)

include_directories(inc)

add_executable(Spreed_Sheet src/main.cpp
        src/Cell.cpp
        src/Sheet.cpp
        inc/Display.hpp
        src/Display.cpp
        inc/Utils.hpp
        src/Utils.cpp
)
