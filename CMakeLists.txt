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

set(THIRD_PARTY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/3rd_party)
set(STB_LIB_DIR ${THIRD_PARTY_DIR}/stb)

message(${THIRD_PARTY_DIR})

set(PROJECT_SOURCE
  src/image.cpp
  src/main.cpp
)

set(PROJECT_HEADERS
  include/image.hpp
  ${STB_LIB_DIR}/stb_image.h
  ${STB_LIB_DIR}/stb_image_write.h
)

add_executable(color-transfer
  ${PROJECT_SOURCE}
)

target_include_directories(color-transfer 
  PRIVATE 
    include
    ${STB_LIB_DIR}
)