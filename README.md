# S21 Containers Project

## Содержание
1. [Сборка проекта](#сборка-проекта)
2. [Запуск тестов (без valgrind)](#запуск-тестов-без-valgrind)
3. [Статический анализ](#статический-анализ)
4. [Проверка памяти](#проверка-памяти)
5. [Форматирование кода](#форматирование-кода)
6. [Покрытие кода](#покрытие-кода)

## Сборка проекта
Создать директорию сборки и скомпилировать
```bash
cmake -B build -DCMAKE_BUILD_TYPE=Debug  # Или Release
cmake --build build --parallel $(nproc)
```

## Запуск тестов (без valgrind)
Перекомпиляция тестов
```bash
cmake --build build --parallel $(nproc)
```

### Containers
```bash
ctest --test-dir build --parallel $(nproc) -R containers_simple_
```
### ContainersPlus
```bash
ctest --test-dir build --parallel $(nproc) -R containers_plus_
```
Из любой директории

### Запуск отдельных тестов
```bash
cmake --build build --target run_s21_test_vector 
```

--output-on-failure	Показывает вывод (stdout и stderr) только для упавших тестов. По умолчанию включено.  
-V (verbose) Показывает подробный вывод о процессе запуска тестов, включая имена тестов и их результат.  
-VV (extra verbose)	Подробный вывод, включая полный вывод всех тестов (успешных и упавших).

## Статический анализ
### clang-tidy
Проверяет соответствие кода гугл стилю
```bash
cmake --build build --target clang-tidy-test
```

### cppcheck 
```bash
cmake --build build --target cppcheck-test
```

## Проверка памяти
### Все тесты
```bash
cmake --build build --target valgrind-test
```

### Для конкретного теста
```bash
cmake --build build --target valgrind_s21_test_название_контейнера
```

## Форматирование кода
```bash
cmake --build build --target clang-format-fix
```

## Покрытие кода
### Генерация отчета
```bash
cmake --build build --target coverage_all
```
Отчет будет доступен в coverage/index.html

## Дополнительные цели

### Список всех целей
```bash
cmake --build build --target help
```
