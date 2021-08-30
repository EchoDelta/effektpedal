cmake_minimum_required(VERSION 3.10)

project(EffektPedal_Test)

add_executable(EffektPedal_Test_Delay delay.cpp)
add_executable(EffektPedal_Test_Reverb reverb.cpp)
target_link_libraries(EffektPedal_Test_Delay effekter libq libqio cycfi::infra)
target_link_libraries(EffektPedal_Test_Reverb effekter libq libqio cycfi::infra)

file(
  COPY resources
  DESTINATION ${CMAKE_CURRENT_BINARY_DIR})