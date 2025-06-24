foreach(CONTAINER ${SUNDAEKA_CONTAINERS})
  # Формируем имя переменной, куда положим список файлов
  string(TOUPPER ${CONTAINER} CONTAINER_UPPER)

  file(GLOB_RECURSE FILES
       "${CMAKE_SOURCE_DIR}/tests/${CONTAINER}_test_dir/*.cc")

  set("${CONTAINER_UPPER}_SOURCES" ${FILES})

endforeach()