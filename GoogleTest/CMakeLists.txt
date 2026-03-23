cmake_minimum_required(VERSION 3.14)
cmake_policy(SET CMP0135 NEW) # Tells CMake to use the NEW timestamp behavior
project(my_project)

# GoogleTest requires at least C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
# descrive cosa scaricare
FetchContent_Declare(
  googletest
  # URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
  URL https://github.com/google/googletest/archive/52eb8108c5bdec04579160ae17225d66034bd723.zip # latest release (1.17)
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# scarica effettivamente la dipendenza nella cartella di build
FetchContent_MakeAvailable(googletest)

# ---------------

enable_testing()

add_executable(
  hello_test
  hello_test.cpp
)
target_link_libraries(
  hello_test
  GTest::gtest_main # provides the main() and the include dirs for the header files
)

# enable CMake’s test runner to discover the tests included in the binary, using the GoogleTest CMake module.
include(GoogleTest)
gtest_discover_tests(hello_test)
