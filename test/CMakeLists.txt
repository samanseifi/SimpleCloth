# see https://cmake.org/cmake/help/latest/module/FindBoost.html
set(Boost_USE_STATIC_LIBS OFF) #enable dynamic linking

# search for unit_test_framework
find_package(Boost REQUIRED COMPONENTS unit_test_framework)

include_directories(${Boost_INCLUDE_DIR})

# create a cmake_testapp_boost target from tests.cpp
add_executable(SimpleCloth_boost tests.cpp)

# link Boost libraries to the new target
target_link_libraries(SimpleCloth_boost ${Boost_LIBRARIES})

# link Boost with code library
target_link_libraries(SimpleCloth_boost)
