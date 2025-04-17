#ifndef __DEQUE__
#define __DEQUE__

#include "deq_it.h"

#include <cmath>
#include <deque>
#include <iostream>

// int gn() {
std::deque<int> dq = {1, 2, 3};
// std::deque<int>::iterator it;
//   i
// }

namespace s21 {
template <typename T> class Deque {
public:
  /*--------→ CONSTRUCTORS ←-------------*/
  Deque();
  Deque(const size_t Tp_qty);
  Deque(const size_t Tp_qty, T value);
  Deque(const std::initializer_list<T> &values);

  Deque(Deque &deque_src);
  Deque(Deque &&deque_src);
  ~Deque();

  /*--------→ OPERATORS ←-------------*/
  operator=(Deque & deque_src);
  operator=(Deque && deque_src);

  /*--------→ METHODS  ←-----------*/
  void PushBack(int value);
  size_t Size();

  s21::Iterator<T> Begin();
  s21::Iterator<T> End();

private:
  /*--------→  VARIATIONS ←-------------*/
  size_t _chunk_size; // deque chunk size
  T **_chunk_map;
  s21::Iterator<T> _start;  // iterator
  s21::Iterator<T> _finish; // iterator

  /*--------→ PRIVATE FUNCTIONS ←-------------*/
  /*-----→ utils ←-------*/
  void GetChunkCapacity(size_t &chunk_capacity);
  void DeqInit(const size_t Tp_qty);
  void DeqInit(const std::initializer_list<T>.size());

  void MemFree();
  void BlocksFill(const T value, const size_t &chunk_capacity);
  void BlocksFill(const std::initializer_list<T> values,
                  const size_t &chunk_capacity);
  /*--------→ no_name ←-------------*/
};

} // namespace s21

#endif