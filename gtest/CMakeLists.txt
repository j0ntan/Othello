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