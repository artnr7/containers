#ifndef S21_QUEUE_H_
#define S21_QUEUE_H_

#include "./s21_deque.h"

namespace s21 {

template <typename T, typename Container = Deque<T>>
class Queue {
 public:
  using value_type = Container::value_type;
  using reference = Container::reference;
  using const_reference = Container::const_reference;
  using size_type = Container::size_type;

 protected:
  Container c;

 public:
  explicit Queue() : c() {}
  Queue(const std::initializer_list<value_type> &values) : c{values} {}

  /*--------→ METHODS  ←-----------*/
  template <typename U>
  void Push(U &&value) {
    c.PushBack(value);
  }
  void Pop() { c.PopFront(); }
  void Swap(Queue &o) { std::swap(c, o.c); }

  template <typename... Args>
  void InsertManyBack(Args &&...args) {
    (c.PushBack(std::forward<Args>(args)), ...);
  }

  reference Front() { return c.Front(); }
  const_reference Front() const { return c.Front(); }

  reference Back() { return c.Back(); }
  const_reference Back() const { return c.Back(); }

  bool Empty() const { return c.Empty(); }
  size_type Size() const { return c.Size(); }
};

}  // namespace s21

#endif  // S21_QUEUE_H
