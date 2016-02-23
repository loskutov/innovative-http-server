cmake_minimum_required(VERSION 2.8)
project(final)

find_package(Boost 1.60.0 REQUIRED system)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Wextra -Wconversion -pedantic")

set(SRC_LIST main.cpp)

add_executable(${PROJECT_NAME} ${SRC_LIST})
target_include_directories(${PROJECT_NAME} PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
