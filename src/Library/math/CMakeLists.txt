project(MATH)
cmake_minimum_required(VERSION 3.13)

add_library(${PROJECT_NAME} STATIC
  GlobalRand.cpp
  NormalRand.cpp
  Quantization.cpp
  Quaternion.cpp
  Ran0.cpp
  Ran1.cpp
  Vector.cpp
  s2e_math.cpp
)

include(../../../common.cmake)
