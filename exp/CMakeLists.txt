add_executable(mainPrintBoard mainPrintBoard.cpp)
target_include_directories(mainPrintBoard PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(mainPrintBoard PUBLIC libBoard)

add_executable(mainPlayGame mainPlayGame.cpp)
target_include_directories(mainPlayGame PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(mainPlayGame
        PUBLIC libBoard
        PUBLIC libGameState
        PUBLIC libSimpleAI)
