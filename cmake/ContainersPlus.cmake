foreach(CONTAINER ${CONTAINERS_PLUS})
  # Имя тестового исполняемого файла
  set(TEST_NAME "s21_test_${CONTAINER}")

  add_executable(${TEST_NAME} tests/${TEST_NAME}.cc)

  # Создание исполняемого файла

  # Подключение зависимостей
  target_link_libraries(${TEST_NAME} PRIVATE GTest::GTest GTest::Main
                                             Threads::Threads)

  # Добавление в CTest
  add_test(NAME containers_plus_${TEST_NAME} COMMAND ${TEST_NAME})

  # Создание цели для запуска
  add_custom_target(
    run_${TEST_NAME}
    COMMAND ./${TEST_NAME}
    DEPENDS ${TEST_NAME}
    COMMENT "Running ${TEST_NAME} tests"
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR})

  target_compile_options(${TEST_NAME} PRIVATE -Wall -Wextra -Werror)
endforeach()
