cmake_minimum_required(VERSION 3.0)
project(boost-graph-example)

set(CMAKE_CXX_STANDARD 11)

find_package(Boost REQUIRED COMPONENTS graph)

include_directories(${Boost_INCLUDE_DIRS})

add_executable(boost-graph-example main.cpp)

target_link_libraries(boost-graph-example ${Boost_LIBRARIES})
