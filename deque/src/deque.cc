#include "../include/deque.h"

template <typename T>
s21::Deque<T>::Deque() : elems_qty(0), mem_blocks_(nullptr) {}

template <typename T>
s21::Deque<T>::Deque(int nums_qty) : elems_qty_(nums_qty) {
  mem_blocks_qty = MemBlocksQty(elems_qty_);
  MemAlc();
  BlocksFill(0);
}

template <typename T> s21::Deque<T>::Deque(int nums_qty, int value) {
  mem_blocks_qty = MemBlocksQty(elems_qty_);

  MemAlc();
  BlocksFill(value);
}

template <typename T> s21::Deque<T>::Deque(std::initializer_list) {
  // выделяем 2 блока
  mem_blocks_qty = MemBlocksQty(block_size * 2);
  MemAlc();
  va_list args;
  va_start(args, usls);
  mem_blocks[]
}
