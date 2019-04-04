cmake_minimum_required (VERSION 2.8)
project(LogisticRegression)
add_executable(logistic_regression_train train.cpp)
install(TARGETS  logistic_regression_train RUNTIME DESTINATION bin)

add_executable(logistic_regression_test test.cpp)
install(TARGETS  logistic_regression_test RUNTIME DESTINATION bin)