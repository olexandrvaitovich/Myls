cmake_minimum_required(VERSION 3.15)
project(myls)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -lboost_filesystem -lboost_system")
find_package(Boost COMPONENTS system filesystem date_time REQUIRED)
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} headers sources )

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(myls main.cpp headers/config.h sources/sort.cpp headers/sort.h sources/print.cpp headers/print.h sources/wildcards.cpp)
target_link_libraries(myls  boost_system boost_filesystem stdc++fs)
