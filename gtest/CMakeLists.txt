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

add_executable(testSimpleEvaluate testSimpleEvaluate.cpp)
target_include_directories(testSimpleEvaluate
        PUBLIC ${CMAKE_SOURCE_DIR}
        PUBLIC ${gtest_SOURCE_DIR}/include)
target_link_libraries(testSimpleEvaluate
        PUBLIC libEvaluate
        PUBLIC libGameState
        PUBLIC libBoard
        PUBLIC testgtestmain
        PUBLIC gtest)

add_executable(testStrongerEvaluate testStrongerEvaluate.cpp)
target_include_directories(testStrongerEvaluate
        PUBLIC ${CMAKE_SOURCE_DIR}
        PUBLIC ${gtest_SOURCE_DIR}/include)
target_link_libraries(testStrongerEvaluate
        PUBLIC libEvaluate
        PUBLIC libGameState
        PUBLIC libBoard
        PUBLIC testgtestmain
        PUBLIC gtest)

add_executable(testRunAll gtestmain.cpp testBoard.cpp testGameState.cpp
        testSimpleEvaluate.cpp testStrongerEvaluate.cpp)
target_include_directories(testRunAll
        PUBLIC ${CMAKE_SOURCE_DIR}
        PUBLIC ${gtest_SOURCE_DIR}/include)
target_link_libraries(testRunAll
        PUBLIC libEvaluate
        PUBLIC libGameState
        PUBLIC libBoard
        PUBLIC gtest)