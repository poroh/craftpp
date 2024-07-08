
set(TEST_NAME craftpp_tests)

set(TEST_SOURCES
    result_result_tests.cpp
    result_reduce_tests.cpp
)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/release-1.11.0.zip
)
FetchContent_GetProperties(googletest)
if(NOT googletest_POPULATED)
    FetchContent_Populate(googletest)
    add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

add_executable(${TEST_NAME} ${TEST_SOURCES})
target_include_directories(${TEST_NAME} PRIVATE ${CMAKE_SOURCE_DIR})

# Link test executable with library and testing framework
target_link_libraries(${TEST_NAME} PRIVATE craftpp)
target_link_libraries(${TEST_NAME} PRIVATE gtest_main)

include(GoogleTest)
gtest_discover_tests(${TEST_NAME})
