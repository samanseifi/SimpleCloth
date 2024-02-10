# Assuming GoogleTest has already been made available in the main CMakeLists.txt

# Create a test executable target from tests.cpp
add_executable(SimpleCloth_test tests.cpp)

# Link GoogleTest libraries to the new target
target_link_libraries(SimpleCloth_test gtest_main)

# Optionally, if you have additional libraries your tests need to link against, include them here
# target_link_libraries(SimpleCloth_test gtest_main your_additional_libraries)

# Register the executable with CTest
add_test(NAME SimpleCloth_test COMMAND SimpleCloth_test)
