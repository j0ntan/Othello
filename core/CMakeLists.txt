add_library(libBoard STATIC Board.hpp Board.cpp)
target_include_directories(libBoard PUBLIC ${OTHELLO_INCLUDE})

add_library(libGameState STATIC GameState.hpp GameState.cpp)
target_include_directories(libGameState
        PUBLIC ${OTHELLO_INCLUDE}
        PUBLIC ${CMAKE_SOURCE_DIR})

add_library(libEvaluate STATIC Evaluate.hpp Evaluate.cpp)
target_include_directories(libEvaluate PUBLIC ${OTHELLO_INCLUDE})

add_library(libSimpleAI STATIC SimpleAI.hpp SimpleAI.cpp)
target_include_directories(libSimpleAI
        PUBLIC ${OTHELLO_INCLUDE}
        PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(libSimpleAI PUBLIC libEvaluate)

add_library(libStrongerAI STATIC StrongerAI.hpp StrongerAI.cpp)
target_include_directories(libStrongerAI
        PUBLIC ${OTHELLO_INCLUDE}
        PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(libStrongerAI PUBLIC libEvaluate)