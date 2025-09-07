#ifndef S21_LIST_H_
#define S21_LIST_H_
#include <iostream>

namespace s21 {

template <typename T>
class List{
 private:
  struct BaseNode {
    BaseNode *prev;
    BaseNode *next;
  };
  struct Node : BaseNode {
    T value;
    Node(const T &data) { value = data; }
  };

  BaseNode fake_node_;
  size_t sizing_;

 public:
  using ValueType = T;
  using Reference = T &;
  using ConstReference = const T &;
  using SizeType = size_t;

  class ListIterator {
   private:
    BaseNode *current_node_;

   public:
    using DifferenceType = std::ptrdiff_t;
    using ValueType = T;

    ListIterator() : current_node_(nullptr) {}
    ListIterator(BaseNode *node) : current_node_(node) {}
    T &operator*() const { return static_cast<Node *>(current_node_)->value; }
    T *operator->() const {
      return &(static_cast<Node *>(current_node_)->value);
    }

    ListIterator &operator++() {
      current_node_ = current_node_->next;
      return *this;
    };

    ListIterator operator++(int) {
      ListIterator temp = current_node_;
      current_node_ = current_node_->next;
      return temp;
    }

    ListIterator &operator--() {
      current_node_ = current_node_->prev;
      return *this;
    };

    ListIterator operator--(int) {
      ListIterator temp = current_node_;
      current_node_ = current_node_->prev;
      return temp;
    }

    bool operator==(const ListIterator &other) const {
      return current_node_ == other.current_node_;
    }
    bool operator!=(const ListIterator &other) const {
      return current_node_ != other.current_node_;
    }

    BaseNode *GetNode() const { return current_node_; }
  };

  class ListConstIterator {
   private:
    const BaseNode *current_node_;

   public:
    ListConstIterator() : current_node_(nullptr) {}
    explicit ListConstIterator(const BaseNode *node) : current_node_(node) {}
    ListConstIterator(const ListIterator &it) : current_node_(it.GetNode()) {}

    const T &operator*() const {
      return static_cast<const Node *>(current_node_)->value;
    }
    const T *operator->() const {
      return &(static_cast<const Node *>(current_node_)->value);
    }

    ListConstIterator &operator++() {
      current_node_ = current_node_->next;
      return *this;
    }

    ListConstIterator operator++(int) {
      ListConstIterator temp = *this;
      current_node_ = current_node_->next;
      return temp;
    }

    ListConstIterator &operator--() {
      current_node_ = current_node_->prev;
      return *this;
    }

    ListConstIterator operator--(int) {
      ListConstIterator temp = *this;
      current_node_ = current_node_->prev;
      return temp;
    }

    bool operator==(const ListConstIterator &other) const {
      return current_node_ == other.current_node_;
    }
    bool operator!=(const ListConstIterator &other) const {
      return current_node_ != other.current_node_;
    }

    const BaseNode *GetNode() const { return current_node_; }
  };

  using Iterator = ListIterator;

  Iterator Begin() { return Iterator(fake_node_.next); }
  Iterator End() { return Iterator(&fake_node_); }

  using ConstIterator = ListConstIterator;

  ConstIterator Begin() const { return ConstIterator(fake_node_.next); }
  ConstIterator End() const { return ConstIterator(&fake_node_); }

  List() : fake_node_{&fake_node_, &fake_node_}, sizing_(0) {}

  List(SizeType n) : List() {
    for (SizeType i = 0; i < n; i++) PushBack(T());
  }

  List(std::initializer_list<ValueType> const &items) : List() {
    for (typename std::initializer_list<ValueType>::iterator it =
             items.begin();
         it != items.end(); it++) {
      const T &item = *it;
      PushBack(item);
    }
  }

  List(const List&l) : List() {
    for (Node *current = static_cast<Node *>(l.fake_node_.next);
         current != &l.fake_node_; current = static_cast<Node *>(current->next)) {
      PushBack(current->value);
    }
  }

  List&operator=(const List&l) {
    if (this != &l) {
      Clear();
      for (Node *current = static_cast<Node *>(l.fake_node_.next);
           current != &l.fake_node_;
           current = static_cast<Node *>(current->next)) {
        PushBack(current->value);
      }
    }
    return *this;
  }

  List(List&&l) noexcept : fake_node_{&fake_node_, &fake_node_}, sizing_(l.sizing_) {
    fake_node_.next = l.fake_node_.next;
    fake_node_.prev = l.fake_node_.prev;
    fake_node_.next->prev = &fake_node_;
    fake_node_.prev->next = &fake_node_;
    l.fake_node_.next = &l.fake_node_;
    l.fake_node_.prev = &l.fake_node_;
    l.sizing_ = 0;
  }

  void Clear() {
    BaseNode *current = fake_node_.next;
    while (current != &fake_node_) {
      BaseNode *next = current->next;
      delete static_cast<Node *>(current);
      current = next;
    }
    fake_node_.prev = &fake_node_;
    fake_node_.next = &fake_node_;
    sizing_ = 0;
  }

  List&operator=(List&&l) {
    if (this != &l) {
      Clear();
      fake_node_.next = l.fake_node_.next;
      fake_node_.prev = l.fake_node_.prev;
      fake_node_.next->prev = &fake_node_;
      fake_node_.prev->next = &fake_node_;
      sizing_ = l.sizing_;
      l.fake_node_.next = &l.fake_node_;
      l.fake_node_.prev = &l.fake_node_;
      l.sizing_ = 0;
    }
    return *this;
  }

  ~List() { Clear(); }

  ConstReference Front() const {
    Node *first = static_cast<Node *>(fake_node_.next);
    return first->value;
  }

  ConstReference Back() const {
    Node *last = static_cast<Node *>(fake_node_.prev);
    return last->value;
  }

  void PushBack(const T &value) {
    Node *new_node = new Node(value);
    BaseNode *last = fake_node_.prev;
    last->next = new_node;
    new_node->prev = last;
    new_node->next = &fake_node_;
    fake_node_.prev = new_node;
    sizing_++;
  }

  void PushFront(const T &value) {
    Node *new_node = new Node(value);
    BaseNode *first = fake_node_.next;
    first->prev = new_node;
    new_node->next = first;
    new_node->prev = &fake_node_;
    fake_node_.next = new_node;
    sizing_++;
  }

  void PopFront() {
    if (Empty()) return;
    Node *first = static_cast<Node *>(fake_node_.next);
    BaseNode *new_first = first->next;
    new_first->prev = &fake_node_;
    fake_node_.next = new_first;
    sizing_--;
    delete first;
  }

  void PopBack() {
    if (Empty()) return;
    Node *last = static_cast<Node *>(fake_node_.prev);
    BaseNode *new_last = last->prev;
    new_last->next = &fake_node_;
    fake_node_.prev = new_last;
    sizing_--;
    delete last;
  }

  SizeType Size() { return sizing_; }

  SizeType MaxSize() {
    return std::numeric_limits<SizeType>::max() / sizeof(Node);
  }

  bool Empty() { return sizing_ == 0; }

  void Swap(List&other) {
    Clear();
    if (other.Empty()) return;
    for (Node *current = static_cast<Node *>(other.fake_node_.next);
         current != &other.fake_node_;
         current = static_cast<Node *>(current->next)) {
      PushBack(current->value);
    }
  }

  Iterator Insert(Iterator pos, ConstReference value) {
    BaseNode *node = pos.GetNode();
    Node *new_node = new Node(value);
    new_node->next = node;
    new_node->prev = node->prev;
    node->prev->next = new_node;
    node->prev = new_node;
    sizing_++;
    return Iterator(new_node);
  }

  template <typename... Args>
  Iterator InsertMany(Iterator pos, Args &&...args) {
    Iterator it = pos;
    (void)std::initializer_list<int>{
        (it = Insert(it, std::forward<Args>(args)), 0)...};
    return it;
  }

  template <typename... Args>
  void InsertManyBack(Args &&...args) {
    (PushBack(std::forward<Args>(args)), ...);
  }

  template <typename... Args>
  void InsertManyFront(Args &&...args) {
    (PushFront(std::forward<Args>(args)), ...);
  }

  void Erase(Iterator pos) {
    if (pos == End()) return;
    BaseNode *node = pos.GetNode();
    node->next->prev = node->prev;
    node->prev->next = node->next;
    delete node;
    sizing_--;
  }

  void Reverse() {
    if (Empty()) return;
    BaseNode *current = &fake_node_;
    do {
      BaseNode *temp = current->next;
      current->next = current->prev;
      current->prev = temp;
      current = temp;
    } while (current != &fake_node_);
  }

  void Unique() {
    if (Empty()) return;
    Node *current = static_cast<Node *>(fake_node_.next);
    while (current->next != &fake_node_) {
      Node *next_node = static_cast<Node *>(current->next);
      if (current->value == next_node->value) {
        current->next = next_node->next;
        next_node->next->prev = current;
        delete next_node;
        sizing_--;
      } else {
        current = next_node;
      }
    }
  }

  void Splice(Iterator pos, List&other) {
    if (other.Empty()) return;
    BaseNode *pos_node = pos.GetNode();
    BaseNode *first = other.fake_node_.next;
    BaseNode *last = other.fake_node_.prev;

    pos_node->prev->next = first;
    first->prev = pos_node->prev;

    last->next = pos_node;
    pos_node->prev = last;

    other.fake_node_.next = &other.fake_node_;
    other.fake_node_.prev = &other.fake_node_;

    sizing_ += other.sizing_;
    other.sizing_ = 0;
  }

  void Merge(List&other) {
    if (this == &other || other.Empty()) return;
    Iterator this_it = Begin();
    Iterator other_it = other.Begin();
    while (this_it != End() && other_it != other.End()) {
      if (*other_it < *this_it) {
        auto next_other = other_it;
        ++next_other;
        Splice(this_it, other);
        other_it = next_other;
      } else {
        ++this_it;
      }
    }
    if (other_it != other.End()) {
      Splice(End(), other);
    }
  }

 private:
  Node *Split(Node *head) {
    Node *slow = head;
    Node *fast = head;
    while (fast->next != &fake_node_ && fast->next->next != &fake_node_) {
      slow = static_cast<Node *>(slow->next);
      fast = static_cast<Node *>(fast->next->next);
    }
    Node *right = static_cast<Node *>(slow->next);
    slow->next = &fake_node_;
    fake_node_.prev = slow;
    right->prev = &fake_node_;

    return right;
  }

  Node *Unite(Node *left, Node *right) {
    if (left == &fake_node_) return right;
    if (right == &fake_node_) return left;

    if (left->value < right->value) {
      left->next = Unite(static_cast<Node *>(left->next), right);
      left->next->prev = left;
      left->prev = &fake_node_;
      return left;
    } else {
      right->next = Unite(left, static_cast<Node *>(right->next));
      right->next->prev = right;
      right->prev = &fake_node_;
      return right;
    }
  }

  Node *MergeSort(Node *head) {
    if (head == &fake_node_ || head->next == &fake_node_) return head;

    Node *right = Split(head);

    head = MergeSort(head);
    right = MergeSort(right);

    return Unite(head, right);
  }

 public:
  void Sort() {
    if (Empty() || sizing_ < 2) return;
    fake_node_.next = MergeSort(static_cast<Node *>(fake_node_.next));
    Node *left = static_cast<Node *>(fake_node_.next);
    left->prev = &fake_node_;
    Node *current = left;
    while (current->next != &fake_node_)
      current = static_cast<Node *>(current->next);
    fake_node_.prev = current;
    current->next = &fake_node_;
  }
};

}  // namespace s21
#endif  // S21_LIST_H_
