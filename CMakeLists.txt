cmake_minimum_required(VERSION 3.10)
project(resnake)

set(RESNAKE resnake.cpp)
add_executable(resnake ${RESNAKE})


if(MSVC)
  add_compile_options(/utf-8)
endif()