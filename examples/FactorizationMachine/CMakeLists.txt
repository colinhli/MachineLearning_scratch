cmake_minimum_required (VERSION 2.8)
project(FM)
add_executable(fm_train train.cpp)
install(TARGETS fm_train RUNTIME DESTINATION bin)

add_executable(fm_test test.cpp)
install(TARGETS fm_test RUNTIME DESTINATION bin)