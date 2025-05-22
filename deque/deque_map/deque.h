#ifndef __DEQUE__
#define __DEQUE__

#include <cmath>
#include <deque>
#include <iostream>

namespace s21 {
template <typename T> class Deque {
public:
  class Iterator {
  public:
    /*--------→ CONSTRUCTORS ←-------------*/
    Iterator() noexcept : _cur_chunk(nullptr), _cur_elt(nullptr) {}
    Iterator(const T **cur_chunk, const T *cur_elt) noexcept
        : _cur_chunk(cur_chunk), _cur_elt(cur_elt) {}
    ~Iterator() { _cur_chunk = nullptr, _cur_elt = nullptr; }

    /*--------→ OPERATORS ←-------------*/
    // T &operator*(const Iterator<T> it) const noexcept { return _cur_elt; }
    // Iterator<T> operator++(Iterator<T> it) {
    //   size_t *chunk_capacity = nullptr;
    //   GetChunkCapacity(chunk_capacity);
    //   T *end_of_chunk = *_cur_chunk + chunk_capacity;
    //   -if (_cur_elt ==)
    //   // _cur_elt += sizeof(T);
    // }

  private:
    T **_cur_chunk;
    T *_cur_elt;
  };

  /*--------→ CONSTRUCTORS ←-------------*/
  explicit Deque(const size_t Tp_qty = 0)
      : _chunk_size(0), _chunk_map(nullptr), _start(nullptr), _finish(nullptr) {
    if (Tp_qty < 1) {
      return;
    }
    size_t *chunk_capacity = nullptr;
    GetChunkCapacity(chunk_capacity);
    DeqInit(Tp_qty);
    BlocksFill(0); // чем заполнять если тип может быть шаблонным, вопрос
  }

  Deque(const size_t Tp_qty, T value);
  Deque(const std::initializer_list<T> &values);

  Deque(const Deque &other);
  Deque(Deque &&other);
  ~Deque();

  /*--------→ OPERATORS ←-------------*/
  Deque &operator=(const Deque &other) noexcept;
  Deque &operator=(Deque &&other) noexcept;

  /*--------→ METHODS  ←-----------*/
  void PushBack(int value);
  size_t Size() noexcept;
  bool Empty() noexcept;

  Iterator Begin() noexcept;
  Iterator End();

private:
  /*--------→  VARIATIONS ←-------------*/
  size_t _chunk_size; // deque chunk size
  T **_chunk_map;
  Iterator _start;  // iterator
  Iterator _finish; // iterator

  /*--------→ PRIVATE FUNCTIONS ←-------------*/
  /*-----→ utils ←-------*/
  void GetChunkCapacity(size_t &chunk_capacity) noexcept;
  void DeqInit(const size_t Tp_qty, const size_t &chunk_capacity);

  void MemFree();
  void BlocksFill(const T value);
  void BlocksFill(const std::initializer_list<T> values);
  /*--------→ no_name ←-------------*/
};

} // namespace s21

#endif