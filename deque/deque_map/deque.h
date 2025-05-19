#ifndef __DEQUE__
#define __DEQUE__

#include <cmath>
#include <deque>
#include <iostream>

namespace s21 {
template <typename T> class Deque {
public:
  /*--------→ CONSTRUCTORS ←-------------*/
  Deque(const size_t Tp_qty); // explicit
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

  Iterator<T> Begin() noexcept;
  Iterator<T> End();

  template <typename T> class Iterator {
  public:
    /*--------→ CONSTRUCTORS ←-------------*/
    Iterator() noexcept : _cur_chunk(nullptr), _cur_elt(nullptr) {}
    Iterator(const T **cur_chunk, const T *cur_elt) noexcept
        : _cur_chunk(cur_chunk), _cur_elt(cur_elt) {}
    ~Iterator() { _cur_chunk(nullptr), _cur_elt(nullptr); }

    /*--------→ OPERATORS ←-------------*/
    T &operator*(const Iterator<T> it) const noexcept { return _cur_elt; }
    Iterator<T> operator++(Iterator<T> it) {
      size_t *chunk_capacity = nullptr;
      GetChunkCapacity(chunk_capacity);
      T *end_of_chunk = *_cur_chunk + chunk_capacity;
      -if (_cur_elt ==)
      // _cur_elt += sizeof(T);
    }

  private:
    T **_cur_chunk;
    T *_cur_elt;
  };

private:
  /*--------→  VARIATIONS ←-------------*/
  size_t _chunk_size; // deque chunk size
  T **_chunk_map;
  s21::Iterator<T> _start;  // iterator
  s21::Iterator<T> _finish; // iterator

  /*--------→ PRIVATE FUNCTIONS ←-------------*/
  /*-----→ utils ←-------*/
  void GetChunkCapacity(const size_t *chunk_capacity);
  void DeqInit(const size_t Tp_qty);
  void DeqInit(const std::initializer_list<T>.size());

  void MemFree();
  void BlocksFill(const T value);
  void BlocksFill(const std::initializer_list<T> values);
  /*--------→ no_name ←-------------*/
};

} // namespace s21

#endif