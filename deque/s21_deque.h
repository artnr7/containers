#include <cmath>
#include <iostream>
#include <cstdarg>

namespace s21 {
template <typename T> class Deque {
private:
  const int block_size_ = 8; // deque block size
  <T> **mem_blocks_;

  /* FUNCTIONS */
  void MemAlc();
  void BlocksFill(int value);
  int MemBlocksQty(int nums_qty);

public:
  Deque();
  Deque(int nums_qty);
  Deque(int nums_qty, int value);
  Deque(...);
  ~Deque();
  Deque(Deque &deque_src);
  Deque(Deque &&deque_src);
  operator=(Deque & deque_src);
  operator=(Deque && deque_src);
};
} // namespace s21