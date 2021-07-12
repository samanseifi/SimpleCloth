cmake_minimum_required(VERSION 3.1)
project(SimpleCloth)

set(BINARY_NAME ${CMAKE_PROJECT_NAME})

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the path of the cmake files to the CMAKE_MODULE_PATH
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -pedantic)
endif()

# Deactivated for Mac build
#find_package(GSL REQUIRED)
#link_libraries(GSL::gsl GSL::gslcblas)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

add_executable(${BINARY_NAME} src/main.cpp includes/ArrayT.h includes/Environment.h includes/MultArrayT.h includes/Vec3.h)

include_directories(includes)

include(CTest)
enable_testing(test)

if (BUILD_TESTING)
    add_subdirectory(test)
endif()
