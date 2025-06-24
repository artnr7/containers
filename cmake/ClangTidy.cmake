# =========================→ Поиск clang-tidy и настройка анализа
find_program(CLANG_TIDY "clang-tidy")
if(CLANG_TIDY)

  file(
    WRITE ${CMAKE_CURRENT_SOURCE_DIR}/.clang-tidy
    "---
Checks: >
    -*,
    clang-analyzer-*,
    google-*,
    modernize-*,
    performance-*,
    readability-*,
    bugprone-*
    -readability-magic-numbers,
    -modernize-use-auto,
    -modernize-use-trailing-return-type,
    -modernize-use-nodiscard
WarningsAsErrors: '*'
HeaderFilterRegex: '.*'
...
")

  add_custom_target(
    clang-tidy-test
    COMMAND
      ${CLANG_TIDY} ${LIB_SOURCE_FILES} ${TEST_SOURCE_FILES}
      --config-file=${CMAKE_CURRENT_SOURCE_DIR}/.clang-tidy
      -p=${CMAKE_BINARY_DIR} # Указываем путь к compile_commands.json
      --quiet
    COMMENT "Running clang-tidy static analysis"
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    VERBATIM)
else()
  message(
    WARNING
      "clang-tidy not found! Static analysis target 'clang-tidy' will not be available"
  )
endif()
