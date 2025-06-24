cmake_minimum_required(VERSION 3.28)
project(S21Containers LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

# ###################################### ГЛАВНАЯ ЧАСТЬ

set(SUNDAEKA_CONTAINERS deque queue stack)
set(FINCHRYZ_CONTAINERS list)
set(AUSTINMA_CONTAINERS vector array)
set(NONAME_CONTAINERS map set multiset rb_tree)

# Список тестируемых контейнеров
set(ALL_CONTAINERS ${AUSTINMA_CONTAINERS} ${FINCHRYZ_CONTAINERS}
                   ${NONAME_CONTAINERS} ${SUNDAEKA_CONTAINERS})

# Основная часть задания
set(CONTAINERS ${SUNDAEKA_CONTAINERS} ${FINCHRYZ_CONTAINERS} vector map set
               rb_tree)

# Дополнительная часть задания
set(CONTAINERS_PLUS array multiset)

# Список тестовых файлов
file(GLOB_RECURSE TEST_SOURCE_FILES "${CMAKE_SOURCE_DIR}/tests/*.cc")

# Список файлов библиотеки
file(GLOB_RECURSE LIB_SOURCE_FILES "${CMAKE_SOURCE_DIR}/*.h")

include(cmake/SundaekaCmake.cmake)

enable_testing()

include(cmake/Containers.cmake)

include(cmake/ContainersPlus.cmake)

include(cmake/ClangTidy.cmake)

include(cmake/Cppcheck.cmake)

include(cmake/Valgrind.cmake)

include(cmake/ClangFormat.cmake)

# include(cmake/Coverage.cmake)

# include(cmake/Hook.cmake)
