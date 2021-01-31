cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 17)

project (ted)

add_subdirectory(doctest)

add_library (ted INTERFACE)

target_include_directories(ted INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

file(GLOB TED_TEST_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp)

add_executable (ted_tests ${TED_TEST_SOURCES})
target_link_libraries(ted_tests PRIVATE doctest ted)
add_test(NAME ted_tests COMMAND ted_tests)