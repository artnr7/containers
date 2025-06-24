foreach(CONTAINER ${CONTAINERS}) # Coverage-версия теста
  set(COVERAGE_TEST_NAME "s21_coverage_${CONTAINER}")

  add_executable(${COVERAGE_TEST_NAME} tests/s21_test_${CONTAINER}.cc)

  target_link_libraries(${COVERAGE_TEST_NAME} PRIVATE GTest::GTest GTest::Main
                                                      Threads::Threads)

  target_compile_options(${COVERAGE_TEST_NAME} PRIVATE -Wall -Wextra -Werror
                                                       --coverage)

  target_link_options(${COVERAGE_TEST_NAME} PRIVATE --coverage)

  target_include_directories(${COVERAGE_TEST_NAME} PRIVATE ${CMAKE_SOURCE_DIR})

  add_custom_target(
    run_coverage_${CONTAINER}
    COMMAND ./${COVERAGE_TEST_NAME}
    DEPENDS ${COVERAGE_TEST_NAME}
    COMMENT "Running coverage tests for
${CONTAINER}"
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
endforeach()

# Глобальная цель coverage find_program(LCOV_PATH lcov)
find_program(GENHTML_PATH genhtml)

set(COVERAGE_DIR "${CMAKE_SOURCE_DIR}/coverage")

if(LCOV_PATH AND GENHTML_PATH)
  set(COVERAGE_TARGETS)
  foreach(CONTAINER ${CONTAINERS})
    list(APPEND COVERAGE_TARGETS run_coverage_${CONTAINER})
  endforeach()

  add_custom_target(
    coverage_all
    COMMAND find . -name "*.gcda" -delete
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target
            ${COVERAGE_TARGETS}
    COMMAND lcov --capture --directory . --output-file coverage.info
            -ignore-errors mismatch
    COMMAND lcov --remove coverage.info '/usr/include/*' --output-file
            coverage_filtered.info
    COMMAND genhtml --output-directory ${COVERAGE_DIR} coverage_filtered.info
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Generating coverage report"
    DEPENDS ${COVERAGE_TARGETS})
else()
  message(WARNING "lcov or genhtml not found - coverage targets disabled")
endif()