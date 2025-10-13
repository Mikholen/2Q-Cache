cmake_minimum_required(VERSION 3.20)
project(cache LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(final ./main.cpp)
target_include_directories(final PRIVATE include)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/heads/main.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(cache_tests
    tests/test_cache.cpp
)
target_include_directories(cache_tests PRIVATE include)
target_link_libraries(cache_tests gtest_main)

include(GoogleTest)
gtest_discover_tests(cache_tests)