#ifndef S21_MAP_H
#define S21_MAP_H

#include <cstddef>
#include <memory>
#include <new>
#include <type_traits>

namespace s21 {

/*
 * @class RBTree @brief Реализация красно-черного дерева
 */

enum class RBTreeColor : bool { kRed = false, kBlack = true };
/*
 * @struct RBTreeNodeBase @brief базовый узел
 */
template <typename Ptr_>
struct RBTreeNodeBase {
  using BasePtr_ =
      typename std::pointer_traits<Ptr_>::template rebind<RBTreeNodeBase>;

  BasePtr_ parent_;
  BasePtr_ left_;
  BasePtr_ right_;

  RBTreeColor color_;

  static BasePtr_ minimum(BasePtr_ tree) noexcept;
  static BasePtr_ maximum(BasePtr_ tree) noexcept;
  BasePtr_ base_ptr() const noexcept;
};

/*
 * @struct RBTreeHeader @brief неизвестно
 */
template <typename NodeBase_>
struct RBTreeHeader {
 private:
  using BasePtr_ = typename NodeBase_::BasePtr_;

 public:
  NodeBase_ header_;
  size_t node_count_;

  RBTreeHeader() noexcept;
  RBTreeHeader(RBTreeHeader&& other) noexcept;

  void reset() noexcept;
  void move_data(RBTreeHeader& other) noexcept;
};

/*
 * @struct RBTreeNode @brief хранит в себе значение
 */
template <typename ValPtr_>
struct RBTreeNode
    : public RBTreeNodeBase<
          typename std::pointer_traits<ValPtr_>::template rebind<void>> {
  using ValueType = typename std::pointer_traits<ValPtr_>::element_type;
  ValueType value_;
  const ValPtr_* valptr() const noexcept;
  ValPtr_* valptr() noexcept;
  RBTreeNode<ValPtr_>* node_ptr() noexcept;
  const RBTreeNode<ValPtr_>* node_ptr() const noexcept;
};

template <typename KeyCompare_>
struct RBTreeKeyCompare {
  KeyCompare_ key_compare_;

  RBTreeKeyCompare() noexcept(
      std::is_nothrow_default_constructible_v<KeyCompare_>);
  RBTreeKeyCompare(const RBTreeKeyCompare& other) = default;
  RBTreeKeyCompare(RBTreeKeyCompare&& other) noexcept(
      std::is_nothrow_default_constructible_v<KeyCompare_>);
};

template <typename Key, typename Value, typename Compare = std::less<Key>>
class RBTree {
  using Node = RBTreeNode<Value*>;
  using NodeBase = RBTreeNodeBase<void*>;
  using NodePtr = Node*;

  using Allocator = std::allocator<Node>;
  using AllocTraits = std::allocator_traits<Allocator>;

 private:
  RBTreeHeader<NodeBase> header_;
  RBTreeKeyCompare<Compare> key_comp_;
  Allocator alloc_;

  NodePtr create_node(const Value& value) {
    NodePtr node = alloc_.allocate(1);
    AllocTraits::construct(alloc_, node);
    node->value_ = value;
    return node;
  }

  void destroy_node(NodePtr node) {
    AllocTraits::destroy(alloc_, node);
    alloc_.deallocate(node, 1);
  }

  

  void rotate_left(NodePtr x) {
    NodePtr y = static_cast<NodePtr>(x->right_);
    x->right_ = y->left_;
    if (y->left_ != nullptr) y->left_->parent_ = x;
    y->parent_ = x->parent_;
    if (x == header_.header_.parent_)
      header_.header_.parent_ = y;
    else if (x == x->parent_->left_)
      x->parent_->left_ = y;
    else
      x->parent_->right_ = y;
    y->left_ = x;
    x->parent_ = y;
  }

  // Вращение вправо вокруг узла x
  void rotate_right(NodePtr x) {
    NodePtr y = static_cast<NodePtr>(x->left_);
    x->left_ = y->right_;
    if (y->right_ != nullptr) y->right_->parent_ = x;
    y->parent_ = x->parent_;
    if (x == header_.header_.parent_)
      header_.header_.parent_ = y;
    else if (x == x->parent_->right_)
      x->parent_->right_ = y;
    else
      x->parent_->left_ = y;
    y->right_ = x;
    x->parent_ = y;
  }
  void fix_insertion(NodePtr node) {
    while (node != header_.header_.parent_ &&
           static_cast<NodePtr>(node->parent_)->color_ == RBTreeColor::kRed) {
      NodePtr parent = static_cast<NodePtr>(node->parent_);
      NodePtr grandparent = static_cast<NodePtr>(parent->parent_);

      if (parent == grandparent->left_) {
        NodePtr uncle = static_cast<NodePtr>(grandparent->right_);

        if (uncle && uncle->color_ == RBTreeColor::kRed) {
          parent->color_ = RBTreeColor::kBlack;
          uncle->color_ = RBTreeColor::kBlack;
          grandparent->color_ = RBTreeColor::kRed;
          node = grandparent;
        } else {
          if (node == parent->right_) {
            node = parent;
            rotate_left(node);
            parent = static_cast<NodePtr>(node->parent_);
          }
          parent->color_ = RBTreeColor::kBlack;
          grandparent->color_ = RBTreeColor::kRed;
          rotate_right(grandparent);
        }
      } else {
        NodePtr uncle = static_cast<NodePtr>(grandparent->left_);

        if (uncle && uncle->color_ == RBTreeColor::kRed) {
          parent->color_ = RBTreeColor::kBlack;
          uncle->color_ = RBTreeColor::kBlack;
          grandparent->color_ = RBTreeColor::kRed;
          node = grandparent;
        } else {
          if (node == parent->left_) {
            node = parent;
            rotate_right(node);
            parent = static_cast<NodePtr>(node->parent_);
          }
          parent->color_ = RBTreeColor::kBlack;
          grandparent->color_ = RBTreeColor::kRed;
          rotate_left(grandparent);
        }
      }
    }
    static_cast<NodePtr>(header_.header_.parent_)->color_ = RBTreeColor::kBlack;
  }

 public:
  NodePtr get_root() const {
    return static_cast<NodePtr>(header_.header_.parent_);
  }
  void insert(const Value& value) {
    NodePtr z = create_node(value);
    NodeBase* y = &header_.header_;
    NodeBase* x = header_.header_.parent_;

    while (x != nullptr) {
      y = x;
      Node* xn = static_cast<Node*>(x);
      if (key_comp_.key_compare_(value.first, xn->value_.first)) {
        x = x->left_;
      } else {
        x = x->right_;
      }
    }
    z->parent_ = static_cast<NodePtr>(y);
    if (y == &header_.header_) {
      header_.header_.parent_ = z;
      header_.header_.left_ = z;
      header_.header_.right_ = z;
    } else if (key_comp_.key_compare_(value.first,
                                      static_cast<Node*>(y)->value_.first)) {
      y->left_ = z;
      if (header_.header_.left_ == y) {
        header_.header_.left_ = z;
      } else {
        y->right_ = z;
        if (header_.header_.right_ == y) {header_.header_.right_ = z;}
      }
        z->left_ = nullptr;
        z->right_ = nullptr;
        z->color_ = RBTreeColor::kRed;

        fix_insertion(z);
        ++header_.node_count_;
      
    }
  }
};

}  // namespace s21

#include "s21_rb_tree.ipp"

#endif  // S21_MAP_H
