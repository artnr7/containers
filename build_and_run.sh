#!/bin/bash

# Проверяем, установлен ли CMake и make
if ! command -v cmake &> /dev/null; then
    echo "Ошибка: CMake не установлен. Установите его сначала."
    exit 1
fi
if ! command -v make &> /dev/null; then
    echo "Ошибка: make не установлен. Установите его сначала."
    exit 1
fi

# Папка сборки (может быть изменена)
BUILD_DIR="build"
mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR" || exit

# Запускаем CMake
echo "🔧 Запуск CMake..."
cmake .. || { echo "❌ Ошибка CMake"; exit 1; }

# Собираем проект
echo "🔨 Сборка проекта..."
make -j$(nproc) || { echo "❌ Ошибка сборки"; exit 1; }

# Возвращаемся в корень проекта
cd ..

# Запускаем тесты (если они есть в bin/tests)
TEST_DIR="bin/tests"
if [ -d "$TEST_DIR" ]; then
    echo "🚀 Запуск тестов из $TEST_DIR..."
    for test_file in "$TEST_DIR"/s21_test_*; do
        if [ -f "$test_file" ]; then
            echo "🔍 Тест: $(basename "$test_file")"
            "$test_file" || echo "❌ Тест завершился с ошибкой"
        fi
    done
else
    echo "⚠ Папка $TEST_DIR не найдена. Тесты не запущены."
fi

echo "✅ Готово!"
