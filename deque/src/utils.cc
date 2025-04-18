#include "../include/deque.h"

/** @note Определения
 * ШТ - Шаблонный тип */

#define BUF_SIZE 512
/** @brief Нахождение максимально возможно количества вмещенных ШТ в BUF_SIZE*/
template <typename T>
void s21::Deque<T>::GetChunkCapacity(size_t &chunk_capacity) noexcept {
  /* Если размер ШТ < BUF_SIZE, то вычисляем какое кол-во их можно вместить  в
   * одном чанке
   * Если размер > (1/2 * BUF_SIZE), то кол-во ШТ в одном чанке будет равно 1 */
  chunk_capacity =
      sizeof(T) < BUF_SIZE ? size_t(BUF_SIZE / sizeof(T)) : size_t(1);
}

/** @brief Выделение памяти и инициализация итераторов */
template <typename T> void s21::Deque<T>::DeqInit(const size_t Tp_qty) {
  _chunk_size = Tp_qty / chunk_capacity + 1;
  size_t chunk_qty_to_malloc = std::max(8, _chunk_size + 2);

  // ↓ взятие остатка(то есть порядок внутри чанка)
  int fin_ptr_last_j = Tp_qty % chunk_capacity;

  _chunk_map = new<T> **[chunk_qty_to_malloc];
  // ↓ как тут работает сдвиг по памяти
  for (int i = 0; i < chunks_qty_for_malloc; i++) {
    _chunk_map[i] = new<T> *[chunk_capacity];
    // проверка на выделение памяти //

    // ↓ инициализация итераторов
    _finish = {_chunk_map[i], _chunk_map[i][fin_ptr_last_j]};
  }
  _start = {_chunk_map[0], _chunk_map[0][0]};
}

/** @brief Освобождение памяти, используется в конструкторах */
template <typename T> void s21::Deque<T>::MemFree() { delete[] _chunk_map; }

/** @brief Функция заполнения выделенной памяти стандартными или заданными
 * значениями */
template <typename T>
void s21::Deque<T>::BlocksFill(const std::initializer_list<T> values,
                               const size_t &chunk_capacity) {
  using s21::Iterator<T> = Iter;
  for (Iter it = Begin(); it != End(); it++;)
    std::for_each _chunk_map[i][j] = values[i * chunk_capacity + j];
}