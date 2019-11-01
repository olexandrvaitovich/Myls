cmake_minimum_required(VERSION 3.15)
project(myls)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -lboost_filesystem -lboost_system")
find_package(Boost COMPONENTS system filesystem date_time REQUIRED)
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )

set(CMAKE_CXX_STANDARD 17)

add_executable(myls main.cpp config.h sort.cpp sort.h print.cpp print.h)
target_link_libraries(myls  boost_system boost_filesystem readline)
