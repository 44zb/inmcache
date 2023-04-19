cmake_minimum_required(VERSION 3.25)
project(inmcache)

set(CMAKE_CXX_STANDARD 20)

find_package(Boost REQUIRED)
file(GLOB_RECURSE INM_SOURCE_FILES "${CMAKE_SOURCE_DIR}/Source/inmem/**.cpp")
set(INM_INCLUDE_FILES "${CMAKE_SOURCE_DIR}/Source/inmem/")

add_library(inmcache_lib ${INM_SOURCE_FILES})
target_link_libraries(inmcache_lib PRIVATE Boost::boost)

add_executable(inmcache "${CMAKE_SOURCE_DIR}/Source/Source.cpp")
target_link_libraries(inmcache PRIVATE inmcache_lib Boost::boost)

enable_testing()
add_subdirectory(Tests)