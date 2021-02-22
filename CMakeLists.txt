#
#            CMakeLists.txt
#
# original (c) 2021 theodoric e. stier
# public domain
#

cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)

project (ted)

add_subdirectory(doctest)

find_package(Threads)

add_library (ted_all_headers INTERFACE)

#
# Configure Headers
#
file(GLOB_RECURSE
    TED_SKEL_HEADERS
    RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp")

set(TED_ALL_HEADERS_TEXT "")
set(TED_ALL_HEADERS_HEADER "${CMAKE_CURRENT_BINARY_DIR}/include/ted.hpp")

file(REMOVE "${TED_ALL_HEADERS_HEADER}")

foreach(TED_HEADER ${TED_SKEL_HEADERS})

    #
    # Use custom header configuration
    # script at build time.
    #
    add_custom_command(
        OUTPUT
            "${CMAKE_CURRENT_BINARY_DIR}/include/${TED_HEADER}"
        COMMAND
            ${CMAKE_COMMAND}
            -DIN=\"${CMAKE_CURRENT_SOURCE_DIR}/include/${TED_HEADER}\"
            -DOUT=\"${CMAKE_CURRENT_BINARY_DIR}/include/${TED_HEADER}\"
            -P \"${CMAKE_CURRENT_SOURCE_DIR}/ConfigureHeader.cmake\"
        DEPENDS
            "${CMAKE_CURRENT_SOURCE_DIR}/include/${TED_HEADER}")

    #
    # Support including all headers together.
    #
    file(
        APPEND
        "${TED_ALL_HEADERS_HEADER}"
        "#include<${TED_HEADER}>\n")

    string(REPLACE "/" "" TED_HEADER_TARGET "${TED_HEADER}")
    add_custom_target(
        "ted_header_${TED_HEADER_TARGET}"
        DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/include/${TED_HEADER}")

    add_dependencies(ted_all_headers "ted_header_${TED_HEADER_TARGET}")

endforeach()

add_library (ted INTERFACE)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(ted
        INTERFACE
            "-fcoroutines-ts")

elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(ted
        INTERFACE
            "-fcoroutines")

elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(ted
        INTERFACE
            "/await")
endif()

target_include_directories(ted
    INTERFACE
        "${CMAKE_CURRENT_BINARY_DIR}/include")

target_link_libraries(ted
    INTERFACE
        ted_all_headers
        Threads::Threads)

#
# Compile Tests
#
file(GLOB
    TED_TEST_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp")

add_executable(ted_tests
    ${TED_TEST_SOURCES})

target_link_libraries(ted_tests
    PRIVATE
        doctest
        ted)

add_test(
    NAME ted_tests
    COMMAND ted_tests)