#ifndef S21_QUEUE_H_
#define S21_QUEUE_H_

#include "./s21_deque.h"

namespace s21 {

template <typename T, typename Container = Deque<T>> class Queue {
public:
  using ValueType = Container::ValueType;
  using Reference = Container::Reference;
  using ConstReference = Container::ConstReference;
  using SizeType = Container::SizeType;

protected:
  Container c;

public:
  explicit Queue() : c() {}
  Queue(const std::initializer_list<ValueType> &values) : c{values} {}
  Queue(const Queue &q) = default;
  Queue(Queue &&q) = default;
  ~Queue() = default;

  Queue &operator=(Queue &q) = default;
  Queue &operator=(Queue &&q) = default;

  /*--------→ METHODS  ←-----------*/
  template <typename U> void Push(U &&value) { c.PushBack(value); }
  void Pop() { c.PopFront(); }
  void Swap(Queue &o) { std::swap(c, o.c); }

  template <typename... Args> void InsertManyBack(Args &&...args) {
    (c.PushBack(std::forward<Args>(args)), ...);
  }

  Reference Front() { return c.Front(); }
  ConstReference Front() const { return c.Front(); }

  Reference Back() { return c.Back(); }
  ConstReference Back() const { return c.Back(); }

  bool Empty() const { return c.Empty(); }
  SizeType Size() const { return c.Size(); }
};

} // namespace s21

#endif // S21_QUEUE_H
