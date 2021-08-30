cmake_minimum_required(VERSION 3.10)

project(effekter)

set(E_HEADERS
   ${CMAKE_CURRENT_SOURCE_DIR}/include/effekter/delay.hpp
   ${CMAKE_CURRENT_SOURCE_DIR}/include/effekter/reverb.hpp
)

file(GLOB_RECURSE E_HEADERS include/*.hpp)

source_group("Header Files\\q"
   FILES
   ${E_HEADERS}
)

add_library(effekter INTERFACE)
target_include_directories(effekter INTERFACE include/)
target_link_libraries(effekter INTERFACE libq libqio cycfi::infra)