# =========================→ CPPCHECK
find_program(CPPCHECK "cppcheck")
if(CPPCHECK)
  # Цель для запуска cppcheck с базовыми настройками
  add_custom_target(
    cppcheck-test
    COMMAND
      ${CPPCHECK} --enable=warning,performance,portability,style
      --suppress=missingIncludeSystem --std=c++20
      --template="[{severity}][{id}] {message} {file}:{line}" --error-exitcode=1
      --inline-suppr --project=${CMAKE_BINARY_DIR}/compile_commands.json -i
      ${CMAKE_BINARY_DIR} # Игнорируем build-директорию
    COMMENT "Running cppcheck static analysis"
    VERBATIM)

  # Альтернативная цель для проверки только исходников (без
  # compile_commands.json)
  add_custom_target(
    cppcheck-test-sources
    COMMAND
      ${CPPCHECK} --enable=all --suppress=missingIncludeSystem --std=c++20
      --template="[{severity}][{id}] {message} {file}:{line}" --error-exitcode=1
      --inline-suppr ${LIB_SOURCE_FILES} ${TEST_SOURCE_FILES} -i
      ${CMAKE_BINARY_DIR}
    COMMENT "Running cppcheck on source files directly"
    VERBATIM)
else()
  message(
    WARNING
      "cppcheck not found! Static analysis targets 'cppcheck' and 'cppcheck-sources' will not be available"
  )
endif()
