#include "../include/deque.h"

/** @note Определения
 * ШТ - Шаблонный тип */

/** @brief Функция выделения памяти, используется в конструкторах */
template <typename T> void s21::Deque<T>::MemAlc() {
  size_t chunk_qty_to_malloc = Tp_qty / chunk_capacity + 1;
  chunk_qty_to_malloc = std::max(8, chunk_qty_to_malloc + 2);

  _chunk_map = new<T> *[chunk_qty_to_malloc];
  for (int i = 0; i < chunks_qty_for_malloc; i++) {
    chunks[i] = new<T> *[_chunk_size];
    // проверка на выделение памяти

    // также наверное можно сделать заполнение полей значениями при
    // инициализации
    
    
    // взятие остатка(то есть порядок внутри чанка)
    int fin_ptr_last_j = Tp_qty % chunk_capacity;
    _finish = _chunk_map[i][fin_ptr_last_j];
  }
  _start = _chunk_map[0][0];
}
/** @brief Функция освобождения памяти, используется в конструкторах */
template <typename T> void s21::Deque<T>::MemFree() { delete[] _chunk_map; }

#define BUF_SIZE 512
/** @brief Функция нахождения максимально возможно количества вмещенных в
 * BUF_SIZE ШТ*/
template <typename T>
void s21::Deque<T>::GetChunkCapacity(size_t &chunk_capacity) {
  /* Если размер ШТ меньше чем BUF_SIZE, то вычисляем какое
   * количество их можно вместить (по сути если размер ШТ больше половины, то он
   * занимает минимум один чанк) в одном чанке
   * Если размер больше половины BUF_SIZE, то количество ШТ в одном чанке будет
   * равно 1
   * ↓*/
  chunk_capacity =
      sizeof(T) < BUF_SIZE ? size_t(BUF_SIZE / sizeof(T)) : size_t(1);
}

/** @brief
 * @todo написать бриф
 */
template <typename T>
void s21::Deque<T>::InitChunkSize(const size_t &chunk_capacity) {
  _chunk_size = chunk_capacity * sizeof(T);
}

/** @brief Функция заполнения выделенной памяти стандартными или заданными
 * значениями */
template <typename T> int s21::Deque<T>::BlocksFill(int value) {
  for (int i = 0; i < chunks_qty_for_malloc; i++) {
    for (int j = 0; j < block_size; j++) {
      _chunk_map[i][j] = value;
    }
  }
}