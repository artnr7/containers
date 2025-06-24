# =========================→ CLANG-FORMAT
find_program(CLANG_FORMAT "clang-format")
if(CLANG_FORMAT)
  # Цель для проверки форматирования (clang-format-check)
  add_custom_target(
    clang-format-test
    COMMAND ${CLANG_FORMAT} --style=Google -n --verbose ${LIB_SOURCE_FILES}
            ${TEST_SOURCE_FILES}
    COMMENT "Checking code formatting with clang-format (Google Style)"
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

  # Цель для форматирования кода (clang-format)
  add_custom_target(
    clang-format-fix
    COMMAND ${CLANG_FORMAT} --style=Google -i ${LIB_SOURCE_FILES}
            ${TEST_SOURCE_FILES}
    COMMENT "Formatting code with clang-format (Google Style)"
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
else()
  message(
    WARNING
      "clang-format not found. clang-format-check and clang-format targets will not be available."
  )
endif()
