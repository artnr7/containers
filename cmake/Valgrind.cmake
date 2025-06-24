# =========================→ VALGRIND
find_program(VALGRIND "valgrind")
if(VALGRIND)
  # Создаем список всех тестовых исполняемых файлов
  set(TEST_EXECUTABLES)
  foreach(CONTAINER ${CONTAINERS})
    list(APPEND TEST_EXECUTABLES "s21_test_${CONTAINER}")
  endforeach()

  # Основная цель для запуска всех тестов через Valgrind
  add_custom_target(
    valgrind-test
    COMMAND ${CMAKE_COMMAND} -E echo "=== Running all tests with Valgrind ==="
    COMMAND
      ${VALGRIND} --leak-check=full --show-leak-kinds=all --track-origins=yes
      --error-exitcode=1 --log-file=${CMAKE_BINARY_DIR}/valgrind.log
      ${CMAKE_CTEST_COMMAND} --output-on-failure
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Running all tests with Valgrind memory checker"
    DEPENDS ${TEST_EXECUTABLES} # Зависит от скомпилированных тестов
  )

  # Альтернативная цель для запуска отдельных тестов
  foreach(CONTAINER ${CONTAINERS})
    set(TEST_NAME "s21_test_${CONTAINER}")
    add_custom_target(
      valgrind_${TEST_NAME}
      COMMAND
        ${VALGRIND} --leak-check=full --show-leak-kinds=all --track-origins=yes
        --error-exitcode=1
        --log-file=${CMAKE_BINARY_DIR}/valgrind_${TEST_NAME}.log ./${TEST_NAME}
      DEPENDS ${TEST_NAME}
      WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
      COMMENT "Running ${TEST_NAME} with Valgrind")
  endforeach()
else()
  message(
    WARNING "Valgrind not found! Memory checking targets will not be available")
endif()