# S21 Containers Project

## Содержание
1. [Сборка проекта](#сборка-проекта)
2. [Запуск тестов](#запуск-тестов)
3. [Статический анализ](#статический-анализ)
4. [Проверка памяти](#проверка-памяти)
5. [Форматирование кода](#форматирование-кода)
6. [Покрытие кода](#покрытие-кода)
7. [Git Hooks](#git-hooks)

## Сборка проекта

### Базовые команды
Создать директорию сборки и скомпилировать
```bash
cmake -B build -DCMAKE_BUILD_TYPE=Debug  # Или Release
cmake --build build --parallel $(nproc)
```

## Запуск тестов 
### Основные способы
Из любой директории
```bash
ctest --test-dir build --output-on-failure
```

Или перейдя в build-директорию
```bash
cd build && ctest --output-on-failure
```

### Фильтрация тестов 
Запуск тестов для конкретного контейнера
```bash
ctest --test-dir build -R название_контейнера 
```

Пропустить тест name 
```bash
ctest --test-dir build -E name 
```
### Параметры выполнения
Параллельный запуск
```bash
ctest --test-dir build --parallel 4
```

С подробным выводом
```bash
ctest --test-dir build -VV
```

С лимитом времени
```bash
ctest --test-dir build --timeout 10
```

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
### Общая проверка
```bash
cmake --build build --target valgrind-test
```

### Для конкретного теста
```bash
cmake --build build --target valgrind_s21_test_list
```

## Форматирование кода
### Проверка стиля
```bash
cmake --build build --target clang-format-test
```

### Автоисправление
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
### Запуск отдельных тестов
```bash
cmake --build build --target run_s21_test_vector
```
### Список всех целей
```bash
cmake --build build --target help
```
