cmake_minimum_required(VERSION 3.10)
project(FastQueue VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

include_directories(/opt/homebrew/include)
link_directories(/opt/homebrew/lib)

add_subdirectory(FastQueue)
add_subdirectory(SmallVectorOptimization)
add_subdirectory(SPMCQueue)
add_subdirectory(StableVector)