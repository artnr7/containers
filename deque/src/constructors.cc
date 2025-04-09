#include "../include/deque.h"

/*--------→ CONSTRUCTORS ←-------------*/
template <typename T> s21::Deque<T>::Deque() : _chunk_map(nullptr), _start(nullptr), _finish(nullptr) {}

template <typename T> s21::Deque<T>::Deque(int Tp_qty) {
  size_t &chunks_qty_for_malloc = nullptr;
  GetChunksQtyForMalloc(Tp_qty, chunks_qty_for_malloc);


  MemAlc();
  BlocksFill(0);
}

template <typename T> s21::Deque<T>::Deque(int Tp_qty, <T> value) {
  size_t &chunks_qty_for_malloc = nullptr;
  size_t &chunks_qty_to_accom_tp = nullptr;
  GetChunksQtyForMalloc(Tp_qty, chunks_qty_for_malloc);

  MemAlc();
  BlocksFill(value);
}

/** @brief
 * @param values это экземпляр типа initializer_list, которая передаёт данные в
 * скобочках */
template <typename T>
s21::Deque<T>::Deque(const std::initializer_list<T> &values) {
  size_t &chunks_qty_for_malloc = nullptr;
  GetChunksQtyForMalloc(values.size(), chunks_qty_for_malloc);

  MemAlc();
  BlocksFill(value);
}

template <typename T> s21::Deque<T>::~Deque() { MemFree(); }
