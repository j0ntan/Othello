add_library(libBoard STATIC Board.hpp Board.cpp)
target_include_directories(libBoard PUBLIC ${OTHELLO_INCLUDE})

add_library(libGameState STATIC GameState.hpp GameState.cpp)
target_include_directories(libGameState
        PUBLIC ${OTHELLO_INCLUDE}
        PUBLIC ${CMAKE_SOURCE_DIR})