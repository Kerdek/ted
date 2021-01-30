cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 17)

project (ted)

add_library (ted INTERFACE)

target_include_directories(ted INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)