#include "../include/deque.h"

/*--------→ CONSTRUCTORS ←-------------*/
template <typename T>
s21::Deque<T>::Deque() : elems_qty(0), mem_blocks_(nullptr) {}

template <typename T> s21::Deque<T>::Deque(int Tp_qty) {
  size_t &chunks_qty_for_malloc = nullptr;
  GetChunksQtyForMalloc(Tp_qty, chunks_qty_for_malloc);

  MemAlc();
  BlocksFill(0);
}

template <typename T> s21::Deque<T>::Deque(int Tp_qty, <T> value) {
  chunks_qty = MemBlocksQty();

  MemAlc();
  BlocksFill(value);
}

// initializer list это штука которая
template <typename T>
s21::Deque<T>::Deque(const std::initializer_list<T> &values) {

  // выделяем 2 блока
  mem_blocks_qty = MemBlocksQty(block_size * 2);
  MemAlc();
  va_list args;
  va_start(args, usls);
  mem_blocks[]
}

template <typename T> s21::Deque<T>::~Deque() { delete }
