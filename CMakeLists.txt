cmake_minimum_required(VERSION 3.14)
project(sort LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  benchmark
  GIT_REPOSITORY https://github.com/google/benchmark.git
  GIT_TAG        v1.8.3
)
set(BENCHMARK_ENABLE_GTEST_TESTS OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(benchmark)

add_executable(sort_bench sort.cpp)
target_link_libraries(sort_bench PRIVATE benchmark::benchmark_main)
target_link_libraries(sort_bench PRIVATE execution)
