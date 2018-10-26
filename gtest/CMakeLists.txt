add_library(testgtestmain STATIC gtestmain.cpp)
target_include_directories(testgtestmain PUBLIC ${gtest_SOURCE_DIR}/include)

add_executable(testBoard testBoard.cpp)
target_include_directories(testBoard
        PUBLIC ${CMAKE_SOURCE_DIR}
        PUBLIC ${gtest_SOURCE_DIR}/include)
target_link_libraries(testBoard
        PUBLIC libBoard
        PUBLIC testgtestmain
        PUBLIC gtest)

add_executable(testGameState testGameState.cpp)
target_include_directories(testGameState
        PUBLIC ${CMAKE_SOURCE_DIR}
        PUBLIC ${gtest_SOURCE_DIR}/include)
target_link_libraries(testGameState
        PUBLIC libGameState
        PUBLIC libBoard
        PUBLIC testgtestmain
        PUBLIC gtest)

add_executable(testRunAll gtestmain.cpp testBoard.cpp testGameState.cpp)
target_include_directories(testRunAll
        PUBLIC ${CMAKE_SOURCE_DIR}
        PUBLIC ${gtest_SOURCE_DIR}/include)
target_link_libraries(testRunAll
        PUBLIC libGameState
        PUBLIC libBoard
        PUBLIC gtest)