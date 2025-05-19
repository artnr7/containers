#include "../deque.h"

template <typename T> void s21::Deque<T>::PushBack(int value) {
  int mem_blocks_qty = MemBlocksQty(elems_qty_);
}

/** @brief Вычисляет размер deque */
template <typename T> size_t s21::Deque<T>::Size() noexcept {
  size_t size = 0;
  for (s21::Deque<T>::Iterator it = Begin(); it != End(); it++) {
    size++;
  }
  return size;
}

/** @brief Узнаёт является ли deque пустым */
template <typename T> bool s21::Deque<T>::Empty() noexcept { return !Size(); }

template <typename T> bool s21::Deque<T>::PushBack(const T &value) noexcept {
  T *end_of_chunk = *_cur_chunk + (chunk_capacity - 1);
  if (_finish)
    *(++_finish) = value;
}

template <typename T> bool s21::Deque<T>::PushFront() noexcept {}

template <typename T> s21::Iterator<T> s21::Deque<T>::Begin() { return _start; }

template <typename T> s21::Iterator<T> s21::Deque<T>::End() {
  return _finish + 1;
}