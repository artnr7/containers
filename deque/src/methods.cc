#include "../include/deque.h"

template <typename T> void s21::Deque<T>::PushBack(int value) {
  int mem_blocks_qty = MemBlocksQty(elems_qty_);
}

template <typename T> void s21::Deque<T>::Resize() {
  mem_blocks_qty *= 2; // увеличение очереди в 2 раза
  <T> **realcd_mem_blocks = new<T> *[mem_blocks_qty];
  for (int i = 0; i < mem_blocks_qty; i++) {
    realcd_mem_blocks[i] =
        &(mem_blocks[i][0]); // одна половина заполняется старыми блоками
  }
  for (int i = mem_blocks_qty; i < realcd_mem_blocks_qty;
       i++) { // вторая новыми
    realcd_mem_blocks[i] = <T>[block_size];
  }
}

template <typename T> void s21::Deque<T>::Size() {}