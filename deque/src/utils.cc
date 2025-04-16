#include "../include/deque.h"

/** @note Определения
 * ШТ - Шаблонный тип */

/** @brief Выделение памяти и инициализация итераторов */
template <typename T> void s21::Deque<T>::DeqInit(const size_t Tp_qty) {
  size_t &chunk_capacity = nullptr;
  GetChunkCapacity(chunk_capacity);

  _chunk_size = Tp_qty / chunk_capacity + 1;
  size_t chunk_qty_to_malloc = std::max(8, _chunk_size + 2);

  _chunk_map = new<T> *[chunk_qty_to_malloc];
  for (int i = 0; i < chunks_qty_for_malloc; i++) {
    chunks[i] = new<T> *[chunk_capacity];
    // проверка на выделение памяти

    // ↓ взятие остатка(то есть порядок внутри чанка)
    int fin_ptr_last_j = Tp_qty % chunk_capacity;

    // ↓ инициализация итераторов
    _finish = _chunk_map[i][fin_ptr_last_j];
  }
  _start = _chunk_map[0][0];
}

template <typename T> void s21::Deque<T>::DeqInit(const size_t Tp_qty) {
  size_t &chunk_capacity = nullptr;
  GetChunkCapacity(chunk_capacity);

  _chunk_size = Tp_qty / chunk_capacity + 1;
  size_t chunk_qty_to_malloc = std::max(8, _chunk_size + 2);

  _chunk_map = new<T> *[chunk_qty_to_malloc];
  for (int i = 0; i < chunks_qty_for_malloc; i++) {
    chunks[i] = new<T> *[chunk_capacity];
    // проверка на выделение памяти

    // ↓ взятие остатка(то есть порядок внутри чанка)
    int fin_ptr_last_j = Tp_qty % chunk_capacity;

    // ↓ инициализация итераторов
    _finish = _chunk_map[i][fin_ptr_last_j];
  }
  _start = _chunk_map[0][0];

}

/** @brief Освобождение памяти, используется в конструкторах */
template <typename T> void s21::Deque<T>::MemFree() { delete[] _chunk_map; }

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

/** @brief Функция заполнения выделенной памяти стандартными или заданными
 * значениями */
template <typename T>
void s21::Deque<T>::BlocksFill(const std::initializer_list<T> values) {
  for (int i = 0; i < _chunk_size; i++) {
    for (int j = 0; j < ; j++) {
      _chunk_map[i][j] = values[];
    }
  }
}