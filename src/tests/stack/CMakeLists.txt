set(TEST_TYPES int long_double BigData)

foreach(TEST_TYPE ${TEST_TYPES})
  file(GLOB_RECURSE ${TEST_TYPE}_TESTS CONFIGURE_DEPENDS "*/${TEST_TYPE}.cc")

  foreach(TEST_SOURCE ${${TEST_TYPE}_TESTS})
    get_filename_component(TEST_NAME ${TEST_SOURCE} NAME_WE)
    get_filename_component(TEST_DIR ${TEST_SOURCE} DIRECTORY)

    get_filename_component(PARENT_DIR ${TEST_DIR} NAME)

    set(TEST_TARGET "s21_test_stack_${PARENT_DIR}_${TEST_TYPE}")

    string(REGEX REPLACE "[^a-zA-Z0-9_]" "_" TEST_TARGET ${TEST_TARGET})

    add_executable(${TEST_TARGET} ${TEST_SOURCE})

    target_include_directories(${TEST_TARGET} PRIVATE
      ${CMAKE_CURRENT_SOURCE_DIR}
    )

    target_link_libraries(${TEST_TARGET} PRIVATE
      GTest::gtest_main
      Threads::Threads
      s21_containers
    )

    target_compile_options(${TEST_TARGET} PRIVATE
      -Wall -Wextra -Werror
    )

    add_test(NAME ${TEST_TARGET} COMMAND ${TEST_TARGET})

    message(STATUS "Added test: ${TEST_TARGET}")
  endforeach()
endforeach()