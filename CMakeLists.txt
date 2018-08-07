cmake_minimum_required(VERSION 3.5)

project(
  constraints
  VERSION 1.0
  LANGUAGES CXX)

add_compile_options("-g3" "-Wall")
add_library(constraint Constraint.cxx)
target_compile_features(
  constraint PUBLIC
  cxx_generalized_initializers)

add_executable(australia Australia.cxx)
target_link_libraries(australia constraint)

add_executable(sudoku sudoku.cxx)
target_compile_features(sudoku PUBLIC cxx_generalized_initializers)
