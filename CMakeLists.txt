cmake_minimum_required(VERSION 3.1)
project(SimpleCloth)

set(BINARY_NAME ${CMAKE_PROJECT_NAME})

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# AddArray the path of the cmake files to the CMAKE_MODULE_PATH
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


find_package(GSL REQUIRED)
link_libraries(GSL::gsl GSL::gslcblas)

# Finding Sundials with FindSUNDIALS.cmake
find_package(SUNDIALS REQUIRED)

# Adding Sundials header files to the includes path
include_directories(${SUNDIALS_INCLUDE_DIR})

# Adding and linking the Sundials library directory
link_directories(${SUNDIALS_LIBRARY_DIR})
link_libraries(${SUNDIALS_LIBRARIES})

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

add_executable(${BINARY_NAME} src/main.cpp includes/utility/ArrayT.h includes/utility/VectorT.h includes/utility/Environment.h includes/utility/MultArrayT.h includes/utility/Vec3.h)


include_directories(includes/utility)

include(CTest)
enable_testing(test)

if (BUILD_TESTING)
    add_subdirectory(test)
endif()
