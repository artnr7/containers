cmake_minimum_required(VERSION 3.28)
project(S21ContainersTests LANGUAGES CXX)

# Настройки компиляции
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Поиск зависимостей: для гугл тестов
find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

# Список тестируемых контейнеров
set(CONTAINERS 
    array
    vector
    list
    map
    set
    stack
    queue
    multiset
)

# Список тестовых файлов
file(GLOB TEST_SOURCE_FILES
    "${CMAKE_SOURCE_DIR}/tests/*.cc"
    "${CMAKE_SOURCE_DIR}/tests/*.h"
)

# Список файлов библиотеки
file(GLOB LIB_SOURCE_FILES
    "${CMAKE_SOURCE_DIR}/*.cc"
    "${CMAKE_SOURCE_DIR}/*.h"
)

enable_testing()

foreach(CONTAINER ${CONTAINERS})
    # Имя тестового исполняемого файла
    set(TEST_NAME "s21_test_${CONTAINER}")
    
    # Создание исполняемого файла
    add_executable(${TEST_NAME} tests/${TEST_NAME}.cc)
    
    # Подключение зависимостей
    target_link_libraries(${TEST_NAME}
        PRIVATE 
        GTest::GTest
        GTest::Main
        Threads::Threads
    )
    
    # Добавление в CTest
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
    
    # Создание цели для запуска
    add_custom_target(run_${TEST_NAME}
        COMMAND ./${TEST_NAME}
        DEPENDS ${TEST_NAME}
        COMMENT "Running ${TEST_NAME} tests"
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    )
    
    target_compile_options(${TEST_NAME} PRIVATE
        -Wall
        -Wextra
        -Werror
    )
endforeach()

# Поиск clang-format
find_program(CLANG_FORMAT "clang-format")
if(CLANG_FORMAT)
    # Цель для проверки форматирования (clang-format-check)
    add_custom_target(clang-format-check
        COMMAND ${CLANG_FORMAT} --style=Google -n --verbose ${LIB_SOURCE_FILES} ${TEST_SOURCE_FILES}
        COMMENT "Checking code formatting with clang-format (Google Style)"
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    )

    # Цель для форматирования кода (clang-format)
    add_custom_target(clang-format
        COMMAND ${CLANG_FORMAT} --style=Google -i ${LIB_SOURCE_FILES} ${TEST_SOURCE_FILES}
        COMMENT "Formatting code with clang-format (Google Style)"
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    )
else()
    message(WARNING "clang-format not found. clang-format-check and clang-format targets will not be available.")
endif()
