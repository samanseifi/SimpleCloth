cmake_minimum_required(VERSION 3.1)
project(SimpleCloth)

# Ensure we have at least CMake 3.14
if(${CMAKE_VERSION} VERSION_LESS 3.14)
    message(FATAL_ERROR "GoogleTest integration requires at least CMake 3.14")
endif()

set(BINARY_NAME ${CMAKE_PROJECT_NAME})

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -pedantic)
endif()

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

add_executable(${BINARY_NAME} src/main.cpp includes/ArrayT.h includes/Environment.h includes/MultArrayT.h includes/Vec3.h)

include_directories(includes)

# Include GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE) # For Windows
FetchContent_MakeAvailable(googletest)

include(CTest)
enable_testing()

# Only include test subdirectory if BUILD_TESTING is on
if (BUILD_TESTING)
    add_subdirectory(test)
endif()

# Example of how to link a test executable
# add_executable(example_test test/example_test.cpp)
# target_link_libraries(example_test gtest_main)
# add_test(NAME example_test COMMAND example_test)
