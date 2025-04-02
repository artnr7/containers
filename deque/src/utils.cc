#include "../include/deque.h"

template <typename T> void s21::Deque<T>::MemAlc() {
  mem_blocks_ = new<T> *[mem_blocks_qty];
  for (int i = 0; i < mem_blocks_qty; i++) {
    mem_blocks_[i] = <T>[block_size_];

    // проверка на выделение памяти

    // также наверное можно сделать заполнение полей значениями при
    // инициализации
  }
}

template <typename T> void s21::Deque<T>::MemBlocksQty(int nums_qty) {
  return ceil(nums_qty / block_size);
}

template <typename T> int s21::Deque<T>::BlocksFill(int value) {
  for (int i = 0; i < mem_blocks_qty; i++) {
    for (int j = 0; j < block_size; j++) {
      mem_blocks_[i][j] = value;
    }
  }
}