#include "../../deque/deque_map/deque.h"
namespace s21 {
template <typename T, typename Container = Deque<T>> class Stack {
public:
  using value_type = Container::value_type;
  using reference = Container::reference;
  using const_reference = Container::const_reference;
  using size_type = Container::size_type;

protected:
  Container c;

public:
  explicit Stack() : c() {}
  Stack(const std::initializer_list<value_type> &values) : c{values} {}


  /*--------→ METHODS  ←-----------*/
  template <typename U> void Push(U &&value) { c.PushBack(value); }
  void Pop() { c.PopBack(); }
  void Swap(Stack &o) { std::swap(c, o.c); }

  reference Top() { return c.Back(); }
  const_reference Top() const { return c.Back(); }

  bool Empty() const { return c.Empty(); }
  size_type Size() const { return c.Size(); }
};
} // namespace s21

// stack() = default;
