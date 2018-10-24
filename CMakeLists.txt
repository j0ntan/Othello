cmake_minimum_required(VERSION 3.12)
project(Othello)

set(CMAKE_CXX_STANDARD 17)

set(OTHELLO_INCLUDE ${CMAKE_SOURCE_DIR}/include)

add_subdirectory(thirdparty/googletest)