#ifndef S21_LIST_H
#define S21_LIST_H

#include <iostream>
#include <array>

std::array<int> a;

namespace s21 {

template <typename T>
class list {
  struct BaseNode {
    BaseNode* prev;
    BaseNode* next;
  };
  struct Node : BaseNode {
    T value;

    Node(const T& data) {
      value = data;
      // this->prev=nullptr;
      // this->next=nullptr;
    }
  };
  BaseNode fakeNode;  // нода которая содержит ссылки на начало и конец списка
  size_t sz;

 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  // using const_ListIterator =
  using size_type = size_t;

  class ListIterator {
   private:
    BaseNode* current_node;

   public:
    using difference_type = std::ptrdiff_t;
    using value_type = T;

    ListIterator(BaseNode* node) : current_node(node) {}

    // разыменование получаем ссылку на значение, чтобы могли менять *it=7
    // const тк итератор не изменяется при разыменовании но то что внутри модно
    // менять
    T& operator*() const { return static_cast<Node*>(current_node)->value; }
    // возвращаем указатель,
    T* operator->() const { return &(static_cast<Node*>(current_node)->value); }
    //++it
    ListIterator& operator++() {
      current_node = current_node->next;
      return *this;
    }
    // it++
    ListIterator operator++(int) {
      ListIterator tmp = current_node;
      current_node = current_node->next;
      return tmp;
    }

    ListIterator& operator--() {
      current_node = current_node->prev;
      return *this;
    }
    ListIterator operator--(int) {
      ListIterator tmp = current_node;
      current_node = current_node->prev;
      return tmp;
    }

    ListIterator begin() { return ListIterator(fakeNode.next); }
    ListIterator end() { return ListIterator(&fakeNode); }

    // указывают ли они на один и тот же элемент в контейнере,
    // а не равны ли значения этих элементов
    // it!=l1.end(); end возвращает rvalue временный объект и чтобы его можно
    // было передавать нужно делать const
    bool operator==(const ListIterator& other) const {
      return current_node == other.current_node;
    }
    bool operator!=(const ListIterator& other) const {
      return current_node != other.current_node;
    }

    BaseNode* get_node() { return current_node; }
  };

  using iterator = ListIterator;

  list() : fakeNode{&fakeNode, &fakeNode}, sz(0) {}

  // explicit в начале зачем
  list(size_type n) : list() {
    for (size_type i = 0; i < n; i++) {
      push_back(T());  // T()создает объект с нулевым значением по умолчанию
    }
  }
  list(std::initializer_list<value_type> const& items) : list() {
    // auto it
    // auto item:items
    // const T& item : items
    for (typename std::initializer_list<value_type>::iterator it =
             items.begin();
         it != items.end(); it++) {
      const T& item = *it;
      push_back(item);
      // push_back(*it);
    }
  }

  list(const list& l) : list() {
    // current!=&l.fakeNode потому что его прев указывает на преддущий, а сам он
    // последний
    for (Node* current = static_cast<Node*>(l.fakeNode.next);
         current != &l.fakeNode; current = static_cast<Node*>(current->next)) {
      push_back(current->value);
    }
  }

  // noexcept не генерирует никаких исключений
  //  Работает с {}, fakeNode(&fakeNode, &fakeNode); // Ошибка: нет конструктора
  list(list&& l) noexcept : fakeNode{&fakeNode, &fakeNode}, sz(l.sz) {
    //*this = std::move(l);

    fakeNode.next = l.fakeNode.next;
    fakeNode.prev = l.fakeNode.prev;

    fakeNode.next->prev = &fakeNode;
    fakeNode.prev->next = &fakeNode;

    l.fakeNode.next = &l.fakeNode;
    l.fakeNode.prev = &l.fakeNode;

    l.sz = 0;
  }
  list& operator=(list&& l) {
    if (this != &l) {
      // очищаем то что было до этого
      clear();

      fakeNode.next = l.fakeNode.next;
      fakeNode.prev = l.fakeNode.prev;

      fakeNode.next->prev = &fakeNode;
      fakeNode.prev->next = &fakeNode;

      sz = l.sz;

      // очищаем исходные
      l.fakeNode.next = &l.fakeNode;
      l.fakeNode.prev = &l.fakeNode;
      l.sz = 0;
    }

    return *this;
  }

  ~list() { clear(); }

  // нужно ли выбрасывать исключение если список пуст
  const_reference front() const {
    Node* node = static_cast<Node*>(fakeNode.next);
    return node->value;
  }

  // нужно ли выбрасывать исключение если список пуст
  const_reference back() const {
    Node* node = static_cast<Node*>(fakeNode.prev);
    return node->value;
  }

  void clear() {
    BaseNode* current_node = fakeNode.next;
    while (current_node != &fakeNode) {
      BaseNode* next_node = current_node->next;
      delete static_cast<Node*>(current_node);
      current_node = next_node;
    }
    // нужно ли current_bode=nullptr

    // разворачиваем фейкноду саму на себя
    fakeNode.prev = &fakeNode;
    fakeNode.next = &fakeNode;
    sz = 0;
  }

  void push_back(const T& value) {
    Node* new_node = new Node(value);
    BaseNode* last = fakeNode.prev;

    last->next = new_node;
    new_node->prev = last;

    new_node->next = &fakeNode;
    fakeNode.prev = new_node;

    sz++;
  }
  void push_front(const T& value) {
    Node* new_node = new Node(value);
    BaseNode* first = fakeNode.next;

    new_node->next = first;
    new_node->prev = &fakeNode;

    first->prev = new_node;
    fakeNode.next = new_node;

    sz++;
  }

  // что должно возвращаться если список пуст
  void pop_front() {
    if (empty()) return;

    Node* first_node = static_cast<Node*>(fakeNode.next);
    BaseNode* new_first_node = first_node->next;

    new_first_node->prev = &fakeNode;
    fakeNode.next = new_first_node;

    delete first_node;
  }

  void pop_back() {
    if (empty()) return;

    Node* last_node = static_cast<Node*>(fakeNode.prev);
    BaseNode* new_last_node = last_node->prev;

    new_last_node->next = &fakeNode;
    fakeNode.prev = new_last_node;

    delete last_node;

    sz--;
  }

  size_type GetSize() { return sz; }

  bool empty() { return sz == 0; }

  ListIterator begin() { return ListIterator(fakeNode.next); }
  ListIterator end() { return ListIterator(&fakeNode); }

  void swap(list& other) {
    std::swap(sz, other.sz);
    std::swap(fakeNode.next, other.fakeNode.next);
    std::swap(fakeNode.prev, other.fakeNode.prev);

    // есл текущий не пустойй то у первого предыдущий указыыает на отхер и
    // меняем на  текущий
    if (sz > 0) {
      fakeNode.next->prev = &fakeNode;
      fakeNode.prev->next = &fakeNode;
    }
    // если пуст то явно устанавливаем что пуст
    else {
      fakeNode.next = &fakeNode;
      fakeNode.prev = &fakeNode;
    }
    if (other.sz > 0) {
      other.fakeNode.next->prev = &other.fakeNode;
      other.fakeNode.prev->next = &other.fakeNode;
    }
    // если пуст то явно устанавливаем что пуст
    else {
      other.fakeNode.next = &other.fakeNode;
      other.fakeNode.prev = &other.fakeNode;
    }
  }

  iterator insert(iterator pos, const_reference value) {
    BaseNode* node = pos.get_node();
    Node* new_node = new Node(value);

    new_node->next = node;
    new_node->prev = node->prev;

    node->prev->next = new_node;
    node->prev = new_node;

    sz++;
    // компилятор неявно преобращует Node* в BaseNode* благодаря наследованию
    return iterator(new_node);
  }

  void erase(iterator pos) {
    if (pos == end()) return;

    Node* node_to_delete = static_cast<Node*>(pos.get_node());

    node_to_delete->prev->next = node_to_delete->next;
    node_to_delete->next->prev = node_to_delete->prev;

    delete node_to_delete;

    sz--;
  }

  void reverse() {
    if (sz <= 1) return;
    BaseNode* current_node = fakeNode.next;
    while (current_node != &fakeNode) {
      BaseNode* tmp = current_node->next;
      current_node->next = current_node->prev;
      current_node->prev = tmp;
      // идем в след ноду, но она теперь предыдущая
      current_node = current_node->prev;
    }
    BaseNode* tmp = fakeNode.prev;
    fakeNode.prev = fakeNode.next;
    fakeNode.next = tmp;
  }

  void unique() {
    if (sz <= 1) return;

    iterator it = begin();
    iterator next = it;
    // есть ли тту разница
    ++next;

    while (next != end()) {
      if (*it == *next) {
        iterator to_delete = next;
        ++next;
        erase(to_delete);
      } else {
        ++next;
        ++it;
      }
    }
  }
  // l1{7,4,3}
  // l2{9,0}
  // заменить на const_iteratos
  void splice(iterator pos, list& other) {
    if (other.empty()) return;

    BaseNode* current_node = pos.get_node();
    if (current_node == &fakeNode && sz == 0) {
      current_node->next = other.fakeNode.next;
      current_node->prev = other.fakeNode.prev;

      current_node->next->prev = current_node;
      current_node->prev->next = current_node;
    } else {
      other.fakeNode.prev->next = current_node;
      other.fakeNode.next->prev = current_node->prev;

      // Связываем текущий список с элементами other
      current_node->prev->next = other.fakeNode.next;
      current_node->prev = other.fakeNode.prev;

      // current_node->prev->next=other.fakeNode.next;
      // other.fakeNode.next->prev = current_node->prev;

      // other.fakeNode.next=current_node;
      // current_node->prev=&other.fakeNode;
    }
    other.fakeNode.next = &other.fakeNode;
    other.fakeNode.prev = &other.fakeNode;

    sz += other.sz;
    other.sz = 0;
  }
};

// /*
//  * @class list
//  * @brief Реализация контейнера list аналогичного std::list
//  */
// template <typename T>
// class list {
//   // Реализация контейнера list
// public:
//   list() {
//     std::cout << "A";
//   }
// };

}  // namespace s21

#endif  // S21_LIST_H
