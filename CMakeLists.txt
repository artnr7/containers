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

