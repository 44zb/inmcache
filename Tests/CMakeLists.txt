cmake_minimum_required(VERSION 3.25)
project(inmcache_test)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include(GoogleTest)

add_executable(inmcache_test "Test.cpp")

target_link_libraries(inmcache_test PRIVATE inmcache_lib gtest_main)
target_include_directories(inmcache_test PRIVATE ${INM_INCLUDE_FILES})

gtest_discover_tests(inmcache_test)
