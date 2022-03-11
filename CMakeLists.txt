cmake_minimum_required(VERSION 3.10)

project(color-transfer)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic")
set(CMAKE_CXX_FLAGS_DEBUG "-ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(PROJECT_SOURCE
  src/test.cpp
  src/main.cpp
)

set(PROJECT_HEADERS

)

add_executable(color-transfer
  ${PROJECT_SOURCE}
)

target_include_directories(color-transfer PRIVATE include)