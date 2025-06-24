foreach(CONTAINER ${CONTAINERS})
  # Имя тестового исполняемого файла
  set(TEST_NAME "s21_test_${CONTAINER}")

  if("${CONTAINER}" STREQUAL "deque"
     OR "${CONTAINER}" STREQUAL "queue"
     OR "${CONTAINER}" STREQUAL "stack")
    string(TOUPPER ${CONTAINER} CONTAINER_UPPER)

    add_executable(${TEST_NAME} ${${CONTAINER_UPPER}_SOURCES})
  else()
    add_executable(${TEST_NAME} tests/${TEST_NAME}.cc)
  endif()

  # Создание исполняемого файла

  # Подключение зависимостей
  target_link_libraries(${TEST_NAME} PRIVATE GTest::GTest GTest::Main
                                             Threads::Threads)

  # Добавление в CTest
  add_test(NAME containers_simple_${TEST_NAME} COMMAND ${TEST_NAME})

  # Создание цели для запуска
  add_custom_target(
    run_${TEST_NAME}
    COMMAND ./${TEST_NAME}
    DEPENDS ${TEST_NAME}
    COMMENT "Running ${TEST_NAME} tests"
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR})

  target_compile_options(${TEST_NAME} PRIVATE -Wall -Wextra -Werror)
endforeach()
