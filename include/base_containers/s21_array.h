#ifndef S21_ARRAY_H
#define S21_ARRAY_H

#include <iostream>

namespace s21 {

/*
 * @class array
 * @brief Реализация контейнера array аналогичного std::array
 */
template <typename T, size_t N>
class Array {
 public:
  class ArrayIterator {
   private:
    T* ptr;

   public:
    explicit ArrayIterator(T* pointer) : ptr(pointer) {}

    T& operator*() { return *ptr; }

    ArrayIterator& operator++() {
      ++ptr;
      return *this;
    }

    ArrayIterator operator++(int) {
      ArrayIterator tmp = *this;
      ++ptr;
      return tmp;
    }

    ArrayIterator& operator--() {
      --ptr;
      return *this;
    }

    ArrayIterator operator--(int) {
      ArrayIterator tmp = *this;
      --ptr;
      return tmp;
    }

    bool operator==(const ArrayIterator& other) const {
      return ptr == other.ptr;
    }
    bool operator!=(const ArrayIterator& other) const {
      return ptr != other.ptr;
    }

    T& operator[](int index) { return *(ptr + index); }

    ArrayIterator operator+(int n) const { return ArrayIterator(ptr + n); }

    ArrayIterator operator-(int n) const { return ArrayIterator(ptr - n); }
    ptrdiff_t operator-(const ArrayIterator& other) const {
      return ptr - other.ptr;
    }

    bool operator>(const ArrayIterator& other) const {
      return ptr > other.ptr;
    }
    bool operator<(const ArrayIterator& other) const {
      return ptr < other.ptr;
    }
    bool operator>=(const ArrayIterator& other) const {
      return ptr >= other.ptr;
    }
    bool operator<=(const ArrayIterator& other) const {
      return ptr <= other.ptr;
    }
  };

  class ArrayIteratorConst {
   private:
    const T* ptr;

   public:
    explicit ArrayIteratorConst(const T* pointer) : ptr(pointer) {}

    const T& operator*() { return *ptr; }

    ArrayIteratorConst& operator++() {
      ++ptr;
      return *this;
    }

    ArrayIteratorConst operator++(int) {
      ArrayIteratorConst tmp = *this;
      ++ptr;
      return tmp;
    }

    ArrayIteratorConst& operator--() {
      --ptr;
      return *this;
    }

    ArrayIteratorConst operator--(int) {
      ArrayIteratorConst tmp = *this;
      --ptr;
      return tmp;
    }

    bool operator==(const ArrayIteratorConst& other) const {
      return ptr == other.ptr;
    }
    bool operator!=(const ArrayIteratorConst& other) const {
      return ptr != other.ptr;
    }

    const T& operator[](int index) { return *(ptr + index); }

    ArrayIteratorConst operator+(int n) const {
      return ArrayIteratorConst(ptr + n);
    }

    ArrayIteratorConst operator-(int n) const {
      return ArrayIteratorConst(ptr - n);
    }
    ptrdiff_t operator-(const ArrayIteratorConst& other) const {
      return ptr - other.ptr;
    }

    bool operator>(const ArrayIteratorConst& other) const {
      return ptr > other.ptr;
    }
    bool operator<(const ArrayIteratorConst& other) const {
      return ptr < other.ptr;
    }
    bool operator>=(const ArrayIteratorConst& other) const {
      return ptr >= other.ptr;
    }
    bool operator<=(const ArrayIteratorConst& other) const {
      return ptr <= other.ptr;
    }
  };

  using ValueType = T;
  using Reference = T &;
  using ConstReference = const T &;
  using Iterator = ArrayIterator;
  using ConstIterator = ArrayIteratorConst;
  using SizeType = size_t;

  Array() = default;

  Array(std::initializer_list<ValueType> const &items) {
    if (items.size() > N) {
      throw std::out_of_range("OUT OF THE RANGE");
    }
    SizeType index = 0;
    for (auto it = items.begin(); it != items.end(); ++it, ++index) {
      data_[index] = *it;
    }
  }

  

  Array(const Array &other) {
    for (SizeType i = 0; i < N; ++i) {
      data_[i] = other.data_[i];
    }
  }

  Array(Array &&other) noexcept {
    for (SizeType i = 0; i < N; ++i) {
      data_[i] = std::move(other.data_[i]);
    }
  }

  ~Array() {
  }

  Array &operator=(Array &&other) noexcept {
    if (this != &other) {
      for (SizeType i = 0; i < N; ++i) {
        data_[i] = std::move(other.data_[i]);
      }
    }

    return *this;
  }

  Reference At(SizeType pos) {
    if (pos >= N) {
      throw std::out_of_range("OUT OF THE RANGE");
    }
    return data_[pos];
  }

  ConstReference At(SizeType pos) const {
    if (pos >= N) {
      throw std::out_of_range("OUT OF THE RANGE");
    }
    return data_[pos];
  }

  Reference operator[](SizeType pos) { return data_[pos]; }

  ConstReference operator[](SizeType pos) const { return data_[pos]; }

  Reference Front() { return data_[0]; }

  Reference Back() { return data_[N - 1]; }

  [[nodiscard]] ConstReference Front() const { return data_[0]; }

  [[nodiscard]] ConstReference Back() const { return data_[N - 1]; }

  Iterator Data() { return Iterator(data_); }

  [[nodiscard]] ConstIterator Data() const { return ConstIterator(data_); }

Iterator Begin() { return Iterator(data_); }

Iterator End() { return Iterator(data_ + N); }

[[nodiscard]] ConstIterator Cbegin() const { return ConstIterator(data_); }

[[nodiscard]] ConstIterator Cend() const { return ConstIterator(data_ + N); }

[[nodiscard]] ConstIterator Begin() const { return ConstIterator(data_); }

[[nodiscard]] ConstIterator End() const { return ConstIterator(data_ + N); }

  bool Empty() { return N == 0; }

  SizeType Size() { return N; }

  SizeType MaxSize() { return N; }

  [[nodiscard]] bool Empty() const { return N == 0; }

  [[nodiscard]] SizeType Size() const { return N; }

  [[nodiscard]] SizeType MaxSize() const { return N; }

  void Swap(Array &other) noexcept {
    for (SizeType i = 0; i < N; ++i) {
      std::swap(data_[i], other.data_[i]);
    }
  }

  void Fill(ConstReference value) {
    for (SizeType i = 0; i < N; ++i) {
      data_[i] = value;
    }
  }

 private:
  ValueType data_[N]{};
};

}  // namespace s21

#endif  // S21_ARRAY_H