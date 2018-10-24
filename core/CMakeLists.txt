add_library(libBoard STATIC Board.hpp Board.cpp)
target_include_directories(libBoard PUBLIC ${OTHELLO_INCLUDE})