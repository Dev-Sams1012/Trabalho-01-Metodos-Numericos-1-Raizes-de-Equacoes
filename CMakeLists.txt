cmake_minimum_required(VERSION 3.16)
project(corda)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(corda
    main.cpp
    GUI/MainWindow.hpp
    GUI/MainWindow.cpp
)

target_link_libraries(corda
    Qt6::Widgets
)
