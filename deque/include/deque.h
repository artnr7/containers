#ifndef __DEQUE__
#define __DEQUE__

#include "deq_it.h"

#include <cmath>
#include <deque>
#include <iostream>

// int gn() {
// std::deque<int> dq = {1, 2, 3};
// std::deque<int>::iterator it;
//   i
// }

namespace s21 {
template <typename T> class Deque {
public:
  /*--------→ CONSTRUCTORS ←-------------*/
  Deque();
  Deque(int Tp_qty);
  Deque(int Tp_qty, T value);
  Deque(const std::initializer_list<T> &values);

  Deque(Deque &deque_src);
  Deque(Deque &&deque_src);
  ~Deque();

  /*--------→ OPERATORS ←-------------*/
  operator=(Deque & deque_src);
  operator=(Deque && deque_src);

  /*--------→ METHODS  ←-----------*/
  void PushBack(int value);

private:
  /*--------→  VARIATIONS ←-------------*/
  size_t _chunk_size; // deque chunk size
  T **_chunk_map;
  Iterator _start;  // iterator
  Iterator _finish; // iterator

  /*--------→ PRIVATE FUNCTIONS ←-------------*/
  /*-----→ utils ←-------*/
  void MemAlc();
  void MemFree();
  int BlocksFill(int value);
  /*--------→ no_name ←-------------*/
  void GetChunkCapacity(size_t &chunk_capacity);
  void InitChunkSize(const size_t &chunk_capacity);
};

} // namespace s21

#endif