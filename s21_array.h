#ifndef S21_ARRAY_H
#define S21_ARRAY_H

#include <iostream>
// #include <cstddef>

namespace s21 {

/*
 * @class array
 * @brief Реализация контейнера array аналогичного std::array
 */
template <typename T, size_t N>
class array {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

  array() = default;

  array(std::initializer_list<value_type> const &items) {
    if (items.size() > N) {
      throw std::out_of_range("OUT OF THE RANGE");
    }
    size_type index = 0;
    for (auto it = items.begin(); it != items.end(); ++it, ++index) {
      data_[index] = *it;
    }
  }

  array(const array &other) = default;
  array(array &&other) = default;
  ~array() = default;

  array &operator=(array &&other) noexcept {
    if (this != &other) {
      for (size_type i = 0; i < N; ++i) {
        data_[i] = std::move(other.data_[i]);
      }
    }

    return *this;
  }

  reference at(size_type pos) {
    if (pos >= N) {
      throw std::out_of_range("OUT OF THE RANGE");
    }
    return data_[pos];
  }

  const_reference at(size_type pos) const {
    if (pos >= N) {
      throw std::out_of_range("OUT OF THE RANGE");
    }
    return data_[pos];
  }

  reference operator[](size_type pos) { return data_[pos]; }

  const_reference operator[](size_type pos) const { return data_[pos]; }

  reference front() { return data_[0]; }

  reference back() { return data_[N - 1]; }

  [[nodiscard]] const_reference front() const { return data_[0]; }

  [[nodiscard]] const_reference back() const { return data_[N - 1]; }

  iterator data() { return data_; }

  [[nodiscard]] const_iterator data() const { return data_; }

  iterator begin() { return data_; }

  iterator end() { return data_ + N; }

  [[nodiscard]] const_iterator begin() const { return data_; }

  [[nodiscard]] const_iterator end() const { return data_ + N; }

  bool empty() { return N == 0; }

  size_type size() { return N; }

  size_type max_size() { return N; }

  [[nodiscard]] bool empty() const { return N == 0; }

  [[nodiscard]] size_type size() const { return N; }

  [[nodiscard]] size_type max_size() const { return N; }

  void swap(array &other) noexcept {
    for (size_type i = 0; i < N; ++i) {
      std::swap(data_[i], other.data_[i]);
    }
  }

  void fill(const_reference value) {
    for (size_type i = 0; i < N; ++i) {
      data_[i] = value;
    }
  }

 private:
  value_type data_[N]{};
};

}  // namespace s21

#endif  // S21_ARRAY_H
