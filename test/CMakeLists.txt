cmake_minimum_required(VERSION 3.10)

project(EffektPedal_Test)

add_executable(EffektPedal_Test_Delay delay.cpp)
target_link_libraries(EffektPedal_Test_Delay libq libqio cycfi::infra)

file(
  COPY resources
  DESTINATION ${CMAKE_CURRENT_BINARY_DIR})