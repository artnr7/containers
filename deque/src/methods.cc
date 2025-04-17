#include "../include/deque.h"

template <typename T> void s21::Deque<T>::PushBack(int value) {
  int mem_blocks_qty = MemBlocksQty(elems_qty_);
}

// template <typename T> size_t s21::Deque<T>::Size() {
//  size_t chunk_capacity =
// }

template <typename T> s21::Iterator<T> s21::Deque<T>::Begin() { return _start; }

template <typename T> s21::Iterator<T> s21::Deque<T>::End() {
  return _finish + sizeof(T);
}