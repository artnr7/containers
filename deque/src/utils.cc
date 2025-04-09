#include "../include/deque.h"

/** @note Определения
 * ШТ - Шаблонный тип */

/** @brief Функция выделения памяти, используется в конструкторах */
template <typename T> void s21::Deque<T>::MemAlc() {
  _chunk_map = new<T> *[chunks_qty_for_malloc];
  for (int i = 0; i < chunks_qty_for_malloc; i++) {
    chunks[i] = <T>[_chunk_size];
    _start = _chunk_map[0][0];
    // проверка на выделение памяти

    // также наверное можно сделать заполнение полей значениями при
    // инициализации
  }
}
/** @brief Функция выделения памяти, используется в конструкторах */
template <typename T> void s21::Deque<T>::MemFree() { delete[] _chunk_map; }

/** @brief Функция нахождения необходимого пространства для ШТ*/
template <typename T>
void s21::Deque<T>::GetChunkCapacity(size_t &chunk_capacity) {
  /* Если размер ШТ меньше чем стандартный размер чанка, то вычисляем какое
   * количество их можно вместить (по сути если размер ШТ больше половины, то он
   * занимает минимум один чанк) в одном чанке
   * ↓*/
  chunk_capacity =
      sizeof(T) < _chunk_size ? size_t(_chunk_size / sizeof(T)) : size_t(1);
}

/** @brief Функция вычисления в какое количество чанков вместится один ШТ */
template <typename T>
void s21::Deque<T>::GetChunkQtyToAccomTp(const size_t &chunk_capacity) {
  /* Если размер ШБ больше размер чанка, то вычисляем количество чанков, которое
   * будет достаточно для записи экземпляра шаблонного типа без потерь
   * ↓*/
  chunks_qty_to_accom_tp = sizeof(T) > _chunk_size
                               ? size_t(ceil(sizeof(T) / _chunk_size))
                               : size_t(0);
}

/** @brief Функция вычисления необходимого количества чанков при
 * инициализации _cnunk_map */
template <typename T>
void s21::Deque<T>::GetChunksQtyForMalloc(int Tp_qty,
                                          size_t &chunks_qty_for_malloc) {
  size_t &chunk_capacity = nullptr;
  GetChunkCapacity(chunk_capacity);

  /* Вычисляем количество чанков, которое следует выделить в _chunk_map */
  chunks_qty_for_malloc = Tp_qty * chunk_capacity;
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