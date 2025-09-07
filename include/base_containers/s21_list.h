#ifndef S21_LIST_H_
#define S21_LIST_H_

#include <cstddef>

namespace s21 {

template <typename T>
class list {
 private:
  struct BaseNode {
    BaseNode *prev;
    BaseNode *next;
  };
  struct Node : BaseNode {
    T value;
    Node(const T &data) { value = data; }
  };

  BaseNode fakeNode;  // нода которая содержит ссылки на начало и конец списка
  size_t sizing;      // счетчик длины листа

 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  class ListIterator {
   private:
    BaseNode *current_node;

   public:
    using difference_type = std::ptrdiff_t;
    using value_type = T;

    ListIterator() : current_node(nullptr) {}
    ListIterator(BaseNode *node) : current_node(node) {}
    T &operator*() const { return static_cast<Node *>(current_node)->value; }
    T *operator->() const {
      return &(static_cast<Node *>(current_node)->value);
    }
    //++it
    ListIterator &operator++() {
      current_node = current_node->next;
      return *this;
    };
    // it++
    ListIterator operator++(int) {
      ListIterator temp = current_node;
      current_node = current_node->next;
      return temp;
    }

    ListIterator &operator--() {
      current_node = current_node->prev;
      return *this;
    };

    ListIterator operator--(int) {
      ListIterator temp = current_node;
      current_node = current_node->prev;
      return temp;
    }

    bool operator==(const ListIterator &other) const {
      return current_node == other.current_node;
    }
    bool operator!=(const ListIterator &other) const {
      return current_node != other.current_node;
    }

    BaseNode *get_node() const { return current_node; }
  };

  using iterator = ListIterator;

  ListIterator begin() { return ListIterator(fakeNode.next); }
  ListIterator end() { return ListIterator(&fakeNode); }

  list()
      : fakeNode{&fakeNode, &fakeNode},
        sizing(0) {}  // конструктор по умолчанию, создает пустой список

  list(size_type n) : list() {
    for (size_type i = 0; i < n; i++) push_back(T());
  }  // параметризованный конструктор, создает список размера n

  list(std::initializer_list<value_type> const &items) : list() {
    for (typename std::initializer_list<value_type>::iterator it =
             items.begin();
         it != items.end(); it++) {
      const T &item = *it;
      push_back(item);
    }
  }  // Конструктор списка инициализаторов, создает список, инициализированный с

  list(const list &l) : list() {
    for (Node *current = static_cast<Node *>(l.fakeNode.next);
         current != &l.fakeNode; current = static_cast<Node *>(current->next)) {
      push_back(current->value);
    }
  }  // конструктор копирования

  list &operator=(const list &l) {
    if (this != &l) {
      clear();
      for (Node *current = static_cast<Node *>(l.fakeNode.next);
           current != &l.fakeNode;
           current = static_cast<Node *>(current->next)) {
        push_back(current->value);
      }
    }
    return *this;
  }

  //  Работает с {}, fakeNode(&fakeNode, &fakeNode); // Ошибка: нет конструктора
  list(list &&l) noexcept : fakeNode{&fakeNode, &fakeNode}, sizing(l.sizing) {
    fakeNode.next = l.fakeNode.next;
    fakeNode.prev = l.fakeNode.prev;
    fakeNode.next->prev = &fakeNode;
    fakeNode.prev->next = &fakeNode;
    l.fakeNode.next = &l.fakeNode;
    l.fakeNode.prev = &l.fakeNode;
    l.sizing = 0;
  }  // конструктор перемещений

  void clear() {
    BaseNode *current = fakeNode.next;
    while (current != &fakeNode) {
      BaseNode *next = current->next;
      delete static_cast<Node *>(current);
      current = next;
    }
    fakeNode.prev = &fakeNode;
    fakeNode.next = &fakeNode;
    sizing = 0;
  }  // чистит лист

  list &operator=(list &&l) {
    if (this != &l) {
      clear();
      fakeNode.next = l.fakeNode.next;
      fakeNode.prev = l.fakeNode.prev;
      fakeNode.next->prev = &fakeNode;
      fakeNode.prev->next = &fakeNode;
      sizing = l.sizing;
      l.fakeNode.next = &l.fakeNode;
      l.fakeNode.prev = &l.fakeNode;
      l.sizing = 0;
    }
    return *this;
  }  // перегрузка оператора присваивания для перемещения объекта

  ~list() { clear(); }

  const_reference front() const {
    Node *first = static_cast<Node *>(fakeNode.next);
    return first->value;
  }  // доступ к первому элементу

  const_reference back() const {
    Node *last = static_cast<Node *>(fakeNode.prev);
    return last->value;
  }  // доступ к последнему элементу

  void push_back(const T &value) {
    Node *new_node = new Node(value);
    BaseNode *last = fakeNode.prev;
    last->next = new_node;
    new_node->prev = last;
    new_node->next = &fakeNode;
    fakeNode.prev = new_node;
    sizing++;
  }  // добавляет элемент в конец

  void push_front(const T &value) {
    Node *new_node = new Node(value);
    BaseNode *first = fakeNode.next;
    first->prev = new_node;
    new_node->next = first;
    new_node->prev = &fakeNode;
    fakeNode.next = new_node;
    sizing++;
  }  // добавляет элемент в заголовок

  void pop_front() {
    if (empty()) return;
    Node *first = static_cast<Node *>(fakeNode.next);
    BaseNode *new_first = first->next;
    new_first->prev = &fakeNode;
    fakeNode.next = new_first;
    sizing--;
    delete first;
  }  // удаляет первый элемент

  void pop_back() {
    if (empty()) return;
    Node *last = static_cast<Node *>(fakeNode.prev);
    BaseNode *new_last = last->prev;
    new_last->next = &fakeNode;
    fakeNode.prev = new_last;
    sizing--;
    delete last;
  }  // удаляет последний элемент

  size_type size() { return sizing; }  // возвращает количество элементов

  size_type max_size() {
    return std::numeric_limits<size_type>::max() / sizeof(Node);
  }  // возвращает максимально возможное количество элементов

  bool empty() { return sizing == 0; }  // проверяет, пуст ли контейнер

  void swap(list &other) {
    clear();
    if (other.empty()) return;
    for (Node *current = static_cast<Node *>(other.fakeNode.next);
         current != &other.fakeNode;
         current = static_cast<Node *>(current->next)) {
      push_back(current->value);
    }
  }  // меняет содержимое

  iterator insert(iterator pos, const_reference value) {
    BaseNode *node = pos.get_node();
    Node *new_node = new Node(value);
    new_node->next = node;
    new_node->prev = node->prev;
    node->prev->next = new_node;
    node->prev = new_node;
    sizing++;
    return iterator(new_node);
  }  // вставляет элемент в конкретную позицию и возвращает итератор,
     // указывающий на новый элемент

  template <typename... Args>
  iterator insert_many(iterator pos, Args &&...args) {  // CONST
    iterator it = pos;
    (void)std::initializer_list<int>{
        (it = insert(it, std::forward<Args>(args)), 0)...};
    return it;
  }

  template <typename... Args>
  void insert_many_back(Args &&...args) {
    (push_back(std::forward<Args>(args)), ...);
  }

  template <typename... Args>
  void insert_many_front(Args &&...args) {
    (push_front(std::forward<Args>(args)), ...);
  }

  void erase(iterator pos) {
    if (pos == end()) return;
    BaseNode *node = pos.get_node();
    node->next->prev = node->prev;
    node->prev->next = node->next;
    delete node;
    sizing--;
  }  // стирает элемент в позиции pos

  void reverse() {
    if (empty()) return;
    BaseNode *current = &fakeNode;
    do {
      BaseNode *temp = current->next;
      current->next = current->prev;
      current->prev = temp;
      current = temp;
    } while (current != &fakeNode);
  }  // меняет порядок элементов на противоположный

  void unique() {
    if (empty()) return;
    Node *current = static_cast<Node *>(fakeNode.next);
    while (current->next != &fakeNode) {
      Node *next_node = static_cast<Node *>(current->next);
      if (current->value == next_node->value) {
        current->next = next_node->next;
        next_node->next->prev = current;
        delete next_node;
        sizing--;
      } else {
        current = next_node;
      }
    }
  }  // удаляет последовательные повторяющиеся элементы

  void splice(iterator pos, list &other) {
    if (other.empty()) return;
    BaseNode *pos_node = pos.get_node();
    BaseNode *first = other.fakeNode.next;
    BaseNode *last = other.fakeNode.prev;

    pos_node->prev->next = first;
    first->prev = pos_node->prev;

    last->next = pos_node;
    pos_node->prev = last;

    other.fakeNode.next = &other.fakeNode;
    other.fakeNode.prev = &other.fakeNode;

    sizing += other.sizing;
    other.sizing = 0;
  }

  void merge(list &other) {
    if (this == &other || other.empty()) return;
    iterator this_it = begin();
    iterator other_it = other.begin();
    while (this_it != end() && other_it != other.end()) {
      if (*other_it < *this_it) {
        auto next_other = other_it;
        ++next_other;
        splice(this_it, other);
        other_it = next_other;
      } else {
        ++this_it;
      }
    }
    if (other_it != other.end()) {
      splice(end(), other);
    }
  }  // объединяет два отсортированных списка

 private:
  Node *split(Node *head) {
    Node *slow = head;
    Node *fast = head;
    while (fast->next != &fakeNode && fast->next->next != &fakeNode) {
      slow = static_cast<Node *>(slow->next);
      fast = static_cast<Node *>(fast->next->next);
    }
    Node *right = static_cast<Node *>(slow->next);
    slow->next = &fakeNode;
    fakeNode.prev = slow;
    right->prev = &fakeNode;

    return right;
  }  // функция для нахождения середины списка

  Node *unite(Node *left, Node *right) {
    if (left == &fakeNode) return right;
    if (right == &fakeNode) return left;

    if (left->value < right->value) {
      left->next = unite(static_cast<Node *>(left->next), right);
      left->next->prev = left;
      left->prev = &fakeNode;
      return left;
    } else {
      right->next = unite(left, static_cast<Node *>(right->next));
      right->next->prev = right;
      right->prev = &fakeNode;
      return right;
    }
  }

  Node *mergeSort(Node *head) {
    if (head == &fakeNode || head->next == &fakeNode) return head;

    Node *right = split(head);

    head = mergeSort(head);
    right = mergeSort(right);

    return unite(head, right);
  }

 public:
  void sort() {
    if (empty() || sizing < 2) return;
    fakeNode.next = mergeSort(static_cast<Node *>(fakeNode.next));
    Node *left = static_cast<Node *>(fakeNode.next);
    left->prev = &fakeNode;
    Node *current = left;
    while (current->next != &fakeNode)
      current = static_cast<Node *>(current->next);
    fakeNode.prev = current;
    current->next = &fakeNode;
  }
};

}  // namespace s21
#endif  // S21_LIST_H_
