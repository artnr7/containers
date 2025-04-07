cmake_minimum_required(VERSION 3.10)
project(s21_containers)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin/tests)

find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(CONTAINERS vector list map stack queue set multiset array)

foreach(container ${CONTAINERS})
    set(TEST_NAME s21_test_${container})
    add_executable(${TEST_NAME} tests/s21_test_${container}.cc)
    target_link_libraries(
        ${TEST_NAME}
        PRIVATE
        GTest::GTest
        GTest::Main
        Threads::Threads
    )
endforeach()

enable_testing()
foreach(container ${CONTAINERS})
    add_test(NAME test_${container} COMMAND ${TEST_NAME})
endforeach()
