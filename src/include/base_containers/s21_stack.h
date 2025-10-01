#ifndef S21_STACK_H_
#define S21_STACK_H_

#include "./s21_deque.h"

namespace s21 {

template <typename T, typename Container = Deque<T>>
class Stack {
 public:
  using ValueType = Container::ValueType;
  using Reference = Container::Reference;
  using ConstReference = Container::ConstReference;
  using SizeType = Container::SizeType;

 protected:
  Container c;

 public:
  explicit Stack() : c() {}
  Stack(const std::initializer_list<ValueType> &values) : c{values} {}
  Stack(const Stack &s) = default;
  Stack(Stack &&s) = default;
  ~Stack() = default;

  Stack &operator=(Stack &s) = default;
  Stack &operator=(Stack &&s) = default;

  /*--------→ METHODS  ←-----------*/
  template <typename U>
  void Push(U &&value) {
    c.PushBack(value);
  }
  void Pop() { c.PopBack(); }
  void Swap(Stack &o) { std::swap(c, o.c); }

  template <typename... Args>
  void InsertManyBack(Args &&...args) {
    (c.PushBack(std::forward<Args>(args)), ...);
  }

  Reference Top() { return c.Back(); }
  ConstReference Top() const { return c.Back(); }

  bool Empty() const { return c.Empty(); }
  SizeType Size() const { return c.Size(); }
};
}  // namespace s21

#endif  // S21_STACK_H
