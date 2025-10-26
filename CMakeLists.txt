cmake_minimum_required(VERSION 3.20)
project(cache LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(two_q_cache main.cpp)
target_include_directories(two_q_cache PRIVATE include)

enable_testing()

find_package(GTest REQUIRED)

add_executable(cache_tests tests/test_cache.cpp)
target_include_directories(cache_tests PRIVATE include)
target_link_libraries(cache_tests GTest::gtest GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(cache_tests)