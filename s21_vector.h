#ifndef S21_VECTOR_H
#define S21_VECTOR_H

#include <iostream>
#include <limits>

namespace s21 {

/*
 * @class vector
 * @brief Реализация контейнера vector аналогичного std::vector
 */
template <typename T, typename Alloc = std::allocator<T>>
class vector {
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

  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using iterator = VectorIterator;
  using const_iterator = VectorIteratorConst;
  using size_type = size_t;
  using traits = std::allocator_traits<Alloc>;

  explicit vector() : data_(nullptr), size_(0), capacity_(0) {}

  explicit vector(size_type n) : data_(nullptr), size_(n), capacity_(n) {
    data_ = traits::allocate(alloc, capacity_);
    try {
      for (size_type i = 0; i < size_; ++i) {
        traits::construct(alloc, data_ + i);
      }
    } catch (...) {
      for (size_type j = 0; j < size_; ++j) {
        traits::destroy(alloc, data_ + j);
      }
      traits::deallocate(alloc, data_, capacity_);
      throw;
    }
  }

  vector(std::initializer_list<value_type> const& items)
      : data_(nullptr), size_(items.size()), capacity_(items.size()) {
    data_ = traits::allocate(alloc, capacity_);
    size_type index = 0;
    try {
      auto iterItem = items.begin();
      for (; iterItem != items.end(); ++index) {
        traits::construct(alloc, data_ + index, *iterItem);
        ++iterItem;
      }
    } catch (...) {
      for (size_type j = 0; j < index; ++j) {
        traits::destroy(alloc, data_ + j);
      }
      traits::deallocate(alloc, data_, capacity_);
      throw;
    }
  }

  vector(const vector& other)
      : data_(nullptr), size_(other.size_), capacity_(other.size_) {
    data_ = traits::allocate(alloc, capacity_);
    size_type index = 0;
    try {
      for (; index < size_; ++index) {
        traits::construct(alloc, data_ + index, other.data_[index]);
      }
    } catch (...) {
      for (size_type j = 0; j < index; ++j) {
        traits::destroy(alloc, data_ + j);
      }
      traits::deallocate(alloc, data_, capacity_);
      throw;
    }
  }

  vector(vector&& other) noexcept
      : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
    other.data_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
  }

  ~vector() {
    for (size_type i = 0; i < size_; ++i) {
      traits::destroy(alloc, data_ + i);
    }

    if (data_) {
      traits::deallocate(alloc, data_, capacity_);
    }
  }

  vector& operator=(vector&& other) noexcept {
    if (this != &other) {
      for (size_type i = 0; i < size_; ++i) {
        traits::destroy(alloc, data_ + i);
      }

      if (data_) {
        traits::deallocate(alloc, data_, capacity_);
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

  reference at(size_type pos) {
    if (size_ <= pos) {
      throw std::out_of_range("Index out of range");
    }
    return data_[pos];
  }

  [[nodiscard]] reference at(size_type pos) const {
    if (size_ <= pos) {
      throw std::out_of_range("Index out of range");
    }
    return data_[pos];
  }

  reference operator[](size_type pos) { return data_[pos]; }

  const_reference operator[](size_type pos) const { return data_[pos]; }

  const_reference front() { return data_[0]; }

  const_reference back() { return data_[size_ - 1]; }

  T* data() { return data_; }

  iterator begin() { return iterator(data_); }

  iterator end() { return iterator(data_ + size_); }

  [[nodiscard]] const_iterator cbegin() const { return const_iterator(data_); }

  [[nodiscard]] const_iterator cend() const {
    return const_iterator(data_ + size_);
  }

  [[nodiscard]] bool empty() const { return size_ == 0; }

  [[nodiscard]] size_type size() const { return size_; }

  [[nodiscard]] size_type max_size() const {
    return std::numeric_limits<size_type>::max() / sizeof(T);
  }

  void reserve(size_type capacity) {
    if (capacity > capacity_) {
      T* newdata = traits::allocate(alloc, capacity);
      try {
        for (size_type i = 0; i < size_; ++i) {
          traits::construct(alloc, newdata + i, data_[i]);
        }
      } catch (...) {
        traits::deallocate(alloc, newdata, capacity);
        throw;
      }

      for (size_type i = 0; i < size_; ++i) {
        traits::destroy(alloc, data_ + i);
      }
      traits::deallocate(alloc, data_, capacity_);
      data_ = newdata;
      capacity_ = capacity;
    }
  }

  size_type capacity() { return capacity_; }

  void shrink_to_fit() {
    if (size_ != capacity_) {
      T* newData = traits::allocate(alloc, size_);
      for (size_type i = 0; i < size_; ++i) {
        traits::construct(alloc, newData + i, std::move(data_[i]));
        traits::destroy(alloc, data_ + i);
      }

      if (data_) {
        traits::deallocate(alloc, data_, capacity_);
      }

      data_ = newData;
      capacity_ = size_;
    }
  }

  void clear() {
    for (size_type i = 0; i < size_; ++i) {
      traits::destroy(alloc, data_ + i);
    }
    size_ = 0;
  }

  void push_back(const_reference value) {
    if (size_ == capacity_) {
      reserve(capacity_ == 0 ? 1 : capacity_ * 2);
    }
    traits::construct(alloc, data_ + size_, value);
    size_++;
  }

  void pop_back() {
    if (size_ == 0) {
      throw std::out_of_range("OUT OF RANGE");
    }
    traits::destroy(alloc, data_ + size_ - 1);
    size_--;
  }

  iterator insert(iterator pos, const_reference value) {
    size_type index = pos - begin();

    if (size_ == capacity_) {
      reserve(capacity_ == 0 ? 1 : capacity_ * 2);
    }

    size_type position = size_;
    try {
      for (; position > index; --position) {
        traits::construct(alloc, data_ + position, data_[position - 1]);
      }
      traits::construct(alloc, data_ + index, value);
    } catch (...) {
      for (size_type j = size_; j > position; --j) {
        traits::destroy(alloc, data_ + j);
      }
      throw;
    }

    size_++;
    return iterator(data_ + index);
  }
  // вопрос на что ориентироваться!!! по разному возвращаемые значения
  void erase(iterator pos) {
    size_type index = pos - begin();

    traits::destroy(alloc, data_ + index);

    for (size_type i = index; i < size_ - 1; ++i) {
      traits::construct(alloc, data_ + i, std::move(data_[i + 1]));
      traits::destroy(alloc, data_ + i + 1);
    }

    size_--;
  }

  void swap(vector& other) noexcept {
    using std::swap;
    swap(data_, other.data_);
    swap(size_, other.size_);
    swap(capacity_, other.capacity_);
    swap(alloc, other.alloc);
  }

 private:
  T* data_;
  size_type size_;
  size_type capacity_;
  Alloc alloc;
};

}  // namespace s21

#endif  // S21_VECTOR_H
