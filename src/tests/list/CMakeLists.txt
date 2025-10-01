set(RB_TREE_TESTS
  s21_test_list.cc
)

foreach(TEST_SOURCE ${RB_TREE_TESTS})
  get_filename_component(TEST_NAME ${TEST_SOURCE} NAME_WE)

  add_executable(${TEST_NAME} ${TEST_SOURCE})

  target_link_libraries(${TEST_NAME} PRIVATE
    GTest::gtest_main
    Threads::Threads
    s21_containers
  )

  target_compile_options(${TEST_NAME} PRIVATE
    -Wall -Wextra -Werror
  )

  add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
  message(STATUS "Added test: ${TEST_NAME}")
endforeach()
