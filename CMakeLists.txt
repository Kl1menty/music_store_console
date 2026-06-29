cmake_minimum_required(VERSION 3.31)
project(project)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

add_executable(project
        filemanager.cpp
        filemanager.h
        main.cpp
        product.cpp
        product.h
        sale.cpp
        sale.h
        store.cpp
        store.h
        supply.cpp
        supply.h)
