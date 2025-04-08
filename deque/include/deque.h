#include <cmath>
#include <iostream>
#include <>

namespace s21 {
template <typename T> class Deque {
private:
  /*--------→  VARIATIONS ←-------------*/
  const int block_size_ = 8; // deque block size
  int elems_qty_;
  <T> **mem_blocks_;

  /*--------→  FUNCTIONS ←-------------*/
  void MemAlc();
  int BlocksFill(int value);
  void MemBlocksQty(int elems_qty);

public:
  /*--------→ CONSTRUCTORS ←-------------*/
  Deque();
  Deque(int nums_qty);
  Deque(int nums_qty, int value);
  Deque(std::initializer_list);
  Deque(Deque &deque_src);
  Deque(Deque &&deque_src);
  ~Deque();

  /*--------→ OPERATORS ←-------------*/
  operator=(Deque & deque_src);
  operator=(Deque && deque_src);

  /*--------→ METHODS  ←-----------*/
  void PushBack(int value);
};
} // namespace s21