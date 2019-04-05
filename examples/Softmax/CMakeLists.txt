cmake_minimum_required (VERSION 2.8)
project(Softmax)
add_executable(softmax_train train.cpp)
install(TARGETS softmax_train RUNTIME DESTINATION bin)

add_executable(softmax_test test.cpp)
install(TARGETS softmax_test RUNTIME DESTINATION bin)