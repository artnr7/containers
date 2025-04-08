#include <cmath>
#include <iostream>

// int gn() { std::deque<int> dq = {1, 2, 3}; }

namespace s21 {
template <typename T> class Deque {
private:
  /*--------→  VARIATIONS ←-------------*/
  const int _chunk_size = 512; // deque chunk size, at least 8 bytes.
  <T> **_chunk_map;

  /*--------→ PRIVATE FUNCTIONS ←-------------*/
  void MemAlc();
  int BlocksFill(int value);
  void GetChunkCapacity(size_t &chunk_capacity);
  void GetChunksQtyForMalloc(int Tp_qty, size_t &chunks_qty_for_malloc);

public:
  /*--------→ CONSTRUCTORS ←-------------*/
  Deque();
  Deque(int Tp_qty);
  Deque(int Tp_qty, <T> value);
  Deque(const std::initializer_list<T> &values);

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