#include "s21_deque.h"

template <typename T> s21::Deque<T>::Deque() : mem_blocks_(nullptr) {}

template <typename T> s21::Deque<T>::MemAlc() {
  mem_blocks_ = new<T> *[mem_blocks_qty];
  for (int i = 0; i < mem_blocks_qty; i++) {
    mem_blocks_[i] = <T>[block_size_];

    // проверка на выделение памяти

    // также наверное можно сделать заполнение полей значениями при
    // инициализации
  }
}

template <typename T> s21::Deque<T>::Resize() {
  realcd_mem_blocks_qty = mem_blocks_qty * 2; // увеличение очереди в 2 раза
  <T> **realcd_mem_blocks = new<T> *[realcd_mem_blocks_qty];
  for (int i = 0; i < mem_blocks_qty; i++) {
    realcd_mem_blocks[i] = &(mem_blocks[i][0]); // одна половина заполняется старыми блоками
  }
  for (int i = mem_blocks_qty; i<realcd_mem_blocks_qty; i++){ // вторая новыми
    realcd_mem_blocks[i] = <T>[block_size]
  }
}

template <typename T> s21::Deque<T>::MemBlocksQty(int nums_qty) {
  return ceil(nums_qty / block_size);
}

template <typename T> s21::Deque<T>::BlocksFill(int value) {
  for (int i = 0; i < mem_blocks_qty; i++) {
    for (int j = 0; j < block_size; j++) {
      mem_blocks_[i][j] = value;
    }
  }
}

template <typename T> s21::Deque<T>::Deque(int nums_qty) : {
  mem_blocks_qty = MemBlocksQty(nums_qty);
  MemAlc();
  BlocksFill(0);
}

template <typename T> s21::Deque<T>::Deque(int nums_qty, int value) {
  mem_blocks_qty = MemBlocksQty(nums_qty);
  MemAlc();
  BlocksFill(value);
}

template <typename T> s21::Deque<T>::Deque(int nums_qty, int value) {
  mem_blocks_qty = MemBlocksQty(2); // выделяем 2 блока
  MemAlc();
  BlocksFill(value);
}
