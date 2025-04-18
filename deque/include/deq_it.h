#ifndef __DEQUE_ITERATOR__
#define __DEQUE_ITERATOR__

namespace s21 {
template <typename T> class Iterator {
public:
  Iterator() noexcept : _cur_chunk(nullptr), _cur_elt(nullptr) {}
  Iterator(const T **cur_chunk, const T *cur_elt) noexcept
      : _cur_chunk(cur_chunk), _cur_elt(cur_elt) {}
  ~Iterator() { _cur_chunk(nullptr), _cur_elt(nullptr); }

  T &operator*(const T &ptr) const noexcept {
    if (_cur_elt) {
      return *_cur_elt;
    }
  }

  Iterator<T> operator++(Iterator<T> it) {
    if (_cur_elt)
    // _cur_elt += sizeof(T);
  }

private:
  T **_cur_chunk;
  T *_cur_elt;
};
} // namespace s21

#endif
