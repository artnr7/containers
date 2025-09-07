#ifndef S21_VECTOR_H_
#define S21_VECTOR_H_

#include <iostream>
#include <limits>

namespace s21 {

/*
 * @class vector
 * @brief Реализация контейнера vector аналогичного std::vector
 */
template <typename T, typename Alloc = std::allocator<T>>
class Vector {
 public:
  class VectorIterator {
   private:
    T* ptr;

   public:
    explicit VectorIterator(T* pointer) : ptr(pointer) {}

    T& operator*() { return *ptr; }

    VectorIterator& operator++() {
      ++ptr;
      return *this;
    }

    VectorIterator operator++(int) {
      VectorIterator tmp = *this;
      ++ptr;
      return tmp;
    }

    VectorIterator& operator--() {
      --ptr;
      return *this;
    }

    VectorIterator operator--(int) {
      VectorIterator tmp = *this;
      --ptr;
      return tmp;
    }

    bool operator==(const VectorIterator& other) const {
      return ptr == other.ptr;
    }
    bool operator!=(const VectorIterator& other) const {
      return ptr != other.ptr;
    }

    T& operator[](int index) { return *(ptr + index); }

    VectorIterator operator+(int n) const { return VectorIterator(ptr + n); }

    VectorIterator operator-(int n) const { return VectorIterator(ptr - n); }
    ptrdiff_t operator-(const VectorIterator& other) const {
      return ptr - other.ptr;
    }

    bool operator>(const VectorIterator& other) const {
      return ptr > other.ptr;
    }
    bool operator<(const VectorIterator& other) const {
      return ptr < other.ptr;
    }
    bool operator>=(const VectorIterator& other) const {
      return ptr >= other.ptr;
    }
    bool operator<=(const VectorIterator& other) const {
      return ptr <= other.ptr;
    }
  };

  class VectorIteratorConst {
   private:
    const T* ptr;

   public:
    explicit VectorIteratorConst(const T* pointer) : ptr(pointer) {}

    const T& operator*() { return *ptr; }

    VectorIteratorConst& operator++() {
      ++ptr;
      return *this;
    }

    VectorIteratorConst operator++(int) {
      VectorIteratorConst tmp = *this;
      ++ptr;
      return tmp;
    }

    VectorIteratorConst& operator--() {
      --ptr;
      return *this;
    }

    VectorIteratorConst operator--(int) {
      VectorIteratorConst tmp = *this;
      --ptr;
      return tmp;
    }

    bool operator==(const VectorIteratorConst& other) const {
      return ptr == other.ptr;
    }
    bool operator!=(const VectorIteratorConst& other) const {
      return ptr != other.ptr;
    }

    const T& operator[](int index) { return *(ptr + index); }

    VectorIteratorConst operator+(int n) const {
      return VectorIteratorConst(ptr + n);
    }

    VectorIteratorConst operator-(int n) const {
      return VectorIteratorConst(ptr - n);
    }
    ptrdiff_t operator-(const VectorIteratorConst& other) const {
      return ptr - other.ptr;
    }

    bool operator>(const VectorIteratorConst& other) const {
      return ptr > other.ptr;
    }
    bool operator<(const VectorIteratorConst& other) const {
      return ptr < other.ptr;
    }
    bool operator>=(const VectorIteratorConst& other) const {
      return ptr >= other.ptr;
    }
    bool operator<=(const VectorIteratorConst& other) const {
      return ptr <= other.ptr;
    }
  };

  using ValueType = T;
  using Reference = T&;
  using ConstReference = const T&;
  using Iterator = VectorIterator;
  using ConstIterator = VectorIteratorConst;
  using SizeType = size_t;
  using Traits = std::allocator_traits<Alloc>;

  explicit Vector() : data_(nullptr), size_(0), capacity_(0) {}

  explicit Vector(SizeType n) : data_(nullptr), size_(n), capacity_(n) {
    data_ = Traits::allocate(alloc_, capacity_);
    try {
      for (SizeType i = 0; i < size_; ++i) {
        Traits::construct(alloc_, data_ + i);
      }
    } catch (...) {
      for (SizeType j = 0; j < size_; ++j) {
        Traits::destroy(alloc_, data_ + j);
      }
      Traits::deallocate(alloc_, data_, capacity_);
      throw;
    }
  }

  Vector(std::initializer_list<ValueType> const& items)
      : data_(nullptr), size_(items.size()), capacity_(items.size()) {
    data_ = Traits::allocate(alloc_, capacity_);
    SizeType index = 0;
    try {
      auto iterItem = items.begin();
      for (; iterItem != items.end(); ++index) {
        Traits::construct(alloc_, data_ + index, *iterItem);
        ++iterItem;
      }
    } catch (...) {
      for (SizeType j = 0; j < index; ++j) {
        Traits::destroy(alloc_, data_ + j);
      }
      Traits::deallocate(alloc_, data_, capacity_);
      throw;
    }
  }

  Vector(const Vector& other)
      : data_(nullptr), size_(other.size_), capacity_(other.size_) {
    data_ = Traits::allocate(alloc_, capacity_);
    SizeType index = 0;
    try {
      for (; index < size_; ++index) {
        Traits::construct(alloc_, data_ + index, other.data_[index]);
      }
    } catch (...) {
      for (SizeType j = 0; j < index; ++j) {
        Traits::destroy(alloc_, data_ + j);
      }
      Traits::deallocate(alloc_, data_, capacity_);
      throw;
    }
  }

  Vector(Vector&& other) noexcept
      : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
    other.data_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
  }

  ~Vector() {
    for (SizeType i = 0; i < size_; ++i) {
      Traits::destroy(alloc_, data_ + i);
    }

    if (data_) {
      Traits::deallocate(alloc_, data_, capacity_);
    }
  }

  Vector& operator=(Vector&& other) noexcept {
    if (this != &other) {
      for (SizeType i = 0; i < size_; ++i) {
        Traits::destroy(alloc_, data_ + i);
      }

      if (data_) {
        Traits::deallocate(alloc_, data_, capacity_);
      }

      data_ = other.data_;
      size_ = other.size_;
      capacity_ = other.capacity_;

      other.data_ = nullptr;
      other.size_ = 0;
      other.capacity_ = 0;
    }
    return *this;
  }

  Reference At(SizeType pos) {
    if (size_ <= pos) {
      throw std::out_of_range("Index out of range");
    }
    return data_[pos];
  }

  [[nodiscard]] Reference At(SizeType pos) const {
    if (size_ <= pos) {
      throw std::out_of_range("Index out of range");
    }
    return data_[pos];
  }

  Reference operator[](SizeType pos) { return data_[pos]; }

  ConstReference operator[](SizeType pos) const { return data_[pos]; }

  ConstReference Front() { return data_[0]; }

  ConstReference Back() { return data_[size_ - 1]; }

  T* Data() { return data_; }

  Iterator Begin() { return Iterator(data_); }

  Iterator End() { return Iterator(data_ + size_); }

  [[nodiscard]] ConstIterator Cbegin() const { return ConstIterator(data_); }

  [[nodiscard]] ConstIterator Cend() const {
    return ConstIterator(data_ + size_);
  }

  [[nodiscard]] bool Empty() const { return size_ == 0; }

  [[nodiscard]] SizeType Size() const { return size_; }

  [[nodiscard]] SizeType MaxSize() const {
    return std::numeric_limits<SizeType>::max() / sizeof(T);
  }

  void Reserve(SizeType capacity) {
    if (capacity > capacity_) {
      T* newdata = Traits::allocate(alloc_, capacity);
      try {
        for (SizeType i = 0; i < size_; ++i) {
          Traits::construct(alloc_, newdata + i, data_[i]);
        }
      } catch (...) {
        Traits::deallocate(alloc_, newdata, capacity);
        throw;
      }

      for (SizeType i = 0; i < size_; ++i) {
        Traits::destroy(alloc_, data_ + i);
      }
      Traits::deallocate(alloc_, data_, capacity_);
      data_ = newdata;
      capacity_ = capacity;
    }
  }

  SizeType Capacity() { return capacity_; }

  void ShrinkToFit() {
    if (size_ != capacity_) {
      T* newData = Traits::allocate(alloc_, size_);
      for (SizeType i = 0; i < size_; ++i) {
        Traits::construct(alloc_, newData + i, std::move(data_[i]));
        Traits::destroy(alloc_, data_ + i);
      }

      if (data_) {
        Traits::deallocate(alloc_, data_, capacity_);
      }

      data_ = newData;
      capacity_ = size_;
    }
  }

  void Clear() {
    for (SizeType i = 0; i < size_; ++i) {
      Traits::destroy(alloc_, data_ + i);
    }
    size_ = 0;
  }

  void PushBack(ConstReference value) {
    if (size_ == capacity_) {
      Reserve(capacity_ == 0 ? 1 : capacity_ * 2);
    }
    Traits::construct(alloc_, data_ + size_, value);
    size_++;
  }

  void PopBack() {
    if (size_ == 0) {
      throw std::out_of_range("OUT OF RANGE");
    }
    Traits::destroy(alloc_, data_ + size_ - 1);
    size_--;
  }

  Iterator Insert(Iterator pos, ConstReference value) {
    SizeType index = pos - Begin();

    if (size_ == capacity_) {
      Reserve(capacity_ == 0 ? 1 : capacity_ * 2);
    }

    SizeType position = size_;
    try {
      for (; position > index; --position) {
        Traits::construct(alloc_, data_ + position, data_[position - 1]);
      }
      Traits::construct(alloc_, data_ + index, value);
    } catch (...) {
      for (SizeType j = size_; j > position; --j) {
        Traits::destroy(alloc_, data_ + j);
      }
      throw;
    }

    size_++;
    return Iterator(data_ + index);
  }

  void Erase(Iterator pos) {
    SizeType index = pos - Begin();

    Traits::destroy(alloc_, data_ + index);

    for (SizeType i = index; i < size_ - 1; ++i) {
      Traits::construct(alloc_, data_ + i, std::move(data_[i + 1]));
      Traits::destroy(alloc_, data_ + i + 1);
    }

    size_--;
  }

  void Swap(Vector& other) noexcept {
    using std::swap;
    swap(data_, other.data_);
    swap(size_, other.size_);
    swap(capacity_, other.capacity_);
    swap(alloc_, other.alloc_);
  }

  template <typename... Args>
  Iterator InsertMany(VectorIteratorConst pos, Args&&... args) {
    if constexpr (sizeof...(args) == 0) {
      return Begin() + (pos - Cbegin());
    }

    const SizeType index = pos - Cbegin();
    const SizeType n = sizeof...(args);

    if (size_ + n > capacity_) {
      Reserve(capacity_ == 0 ? std::max(n, SizeType(1))
                             : std::max(capacity_ * 2, size_ + n));
    }

    for (SizeType i = size_; i > index; --i) {
      Traits::construct(alloc_, data_ + i + n - 1, data_[i - 1]);
      Traits::destroy(alloc_, data_ + i - 1);
    }

    SizeType i = index;
    try {
      ((Traits::construct(alloc_, data_ + i++, std::forward<Args>(args))), ...);
    } catch (...) {
      for (SizeType j = index; j < i; ++j) {
        Traits::destroy(alloc_, data_ + j);
      }
      for (SizeType j = index + n; j < size_ + n; ++j) {
        Traits::construct(alloc_, data_ + j - n, data_[j]);
        Traits::destroy(alloc_, data_ + j);
      }
      throw;
    }
    size_ += n;
    return Iterator(data_ + index);
  }
  template <typename... Args>
  void InsertManyBack(Args&&... args) {
    (PushBack(std::forward<Args>(args)), ...);
  }

 private:
  T* data_;
  SizeType size_;
  SizeType capacity_;
  Alloc alloc_;
};

}  // namespace s21

#endif  // S21_VECTOR_H
