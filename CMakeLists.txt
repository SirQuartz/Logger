cmake_minimum_required(VERSION 3.5)

project(logger VERSION 1.0.0 LANGUAGES CXX)

add_library(mylib STATIC
  src/Logger.cpp
)
