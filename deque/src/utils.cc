#include "../include/deque.h"

template <typename T> void s21::Deque<T>::MemAlc() {
  _chunk_map = new<T> *[chunk_qty];
  for (int i = 0; i < chunk_qty; i++) {
    chunks[i] = <T>[_chunk_size];

    // проверка на выделение памяти

    // также наверное можно сделать заполнение полей значениями при
    // инициализации
  }
}

/** @brief Функция нахождения необходимого пространства для Шаблонного
 * типа(далее ШТ)
 */
template <typename T>
void s21::Deque<T>::GetChunkCapacity(size_t &chunk_capacity) {
  /* Если размер ШТ меньше чем стандартный размер чанка, то вычисляем какое
   * количество их можно вместить (по сути если размер ШТ больше половины, то он
   * занимает минимум один чанк) в одном чанке
   * ↓*/
  chunk_capacity =
      sizeof(T) < _chunk_size ? size_t(_chunk_size / sizeof(T)) : size_t(1);
  /* Если размер ШБ больше размер чанка, то вычисляем количество чанков, которое
   * будет достаточно для записи экземпляра шаблонного типа без потерь
   * ↓*/
  chunk_capacity = sizeof(T) > _chunk_size ? size_t(sizeof(T) / _chunk_size) + 1
                                           : chunk_capacity;
}

template <typename T> void s21::Deque<T>::GetChunksQtyForMalloc() {
  size_t &chunk_capacity = nullptr;
  GetChunkCapacity(chunk_capacity);

  /*И дальше соотвественно вычисляем количество чанков, которое следует выделить
   * для */
}

template <typename T> int s21::Deque<T>::BlocksFill(int value) {
  for (int i = 0; i < chunk_qty; i++) {
    for (int j = 0; j < block_size; j++) {
      _chunks[i][j] = value;
    }
  }
}