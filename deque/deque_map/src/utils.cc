#include "../deque.h"

/** @note Определения
 * ШТ - Шаблонный тип */

#define BUF_SIZE 512
/** @brief Нахождение максимально возможно количества вмещенных ШТ в BUF_SIZE*/
template <typename T>
void s21::Deque<T>::GetChunkCapacity(const size_t *chunk_capacity) noexcept {
  /* Если размер ШТ < BUF_SIZE, то вычисляем какое кол-во их можно вместить  в
   * одном чанке
   * Если размер > (1/2 * BUF_SIZE), то кол-во ШТ в одном чанке будет равно 1 */
  *chunk_capacity =
      sizeof(T) < BUF_SIZE ? size_t(BUF_SIZE / sizeof(T)) : size_t(1);
}

/** @brief Выделение памяти и инициализация итераторов */
template <typename T> void s21::Deque<T>::DeqInit(const size_t Tp_qty) {
  _chunk_size = Tp_qty / chunk_capacity + 1;

  // ↓ взятие остатка(то есть порядок внутри чанка)
  int fin_ptr_last_j = Tp_qty % chunk_capacity;

  _chunk_map = new<T> **[_chunk_size];
  // ↓ как тут работает сдвиг по памяти
  for (int i = 0; i < _chunk_size; i++) {
    _chunk_map[i] = new<T> *[chunk_capacity];
    // @todo проверка на выделение памяти //
  }
}

/** @brief Освобождение памяти, используется в конструкторах */
template <typename T> void s21::Deque<T>::MemFree() {
  for (int i = 0; i < _chunk_size; i++) {
    delete[] _chunk_map[i];
  }
  delete[] _chunk_map;
}

/** @brief Функция заполнения выделенной памяти стандартными или заданными
 * значениями */
template <typename T> void s21::Deque<T>::BlocksFill(const T value) {
  // ↓ инициализация итераторов
  _finish = {_chunk_map[i], _chunk_map[i][fin_ptr_last_j]};

  _start = {_chunk_map[0], _chunk_map[0][0]};

  // ↓ тут можно юзнуть лямбду для объединения
  size_t val_i = 0;

  using s21::Iterator<T> = Iter;
  for (Iter it = Begin(); it != End(); it++;)
    *it = value;
}

/** @brief Функция заполнения выделенной памяти стандартными или заданными
 * значениями из initializer_list */
template <typename T>
void s21::Deque<T>::BlocksFill(const std::initializer_list<T> values) {
  // ↓ тут можно юзнуть лямбду для объединения
  size_t val_i = 0;

  using s21::Iterator<T> = Iter;
  for (Iter it = Begin(); it != End(); it++;)
    *it = values[val_i];
}