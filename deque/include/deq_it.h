#ifndef __DEQUE_ITERATOR__
#define __DEQUE_ITERATOR__

namespace s21 {
template <typename T> class Iterator {
public:
  Iterator() noexcept : _cur(nullptr) {}
  Iterator(const T &ptr) noexcept : _cur(ptr) {}
  ~Iterator() : _cur(nullptr) {}

  T &operator*(const T &ptr) const noexcept {
    if (_cur) {
      return *_cur;
    }
  }

private:
  T *_cur;
};
} // namespace s21

#endif

