#ifndef S21_RB_TREE_INL
#define S21_RB_TREE_INL

#include "s21_rb_tree.h"

namespace s21 {

template <typename Ptr_>
RBTreeNodeBase<Ptr_>::BasePtr_ RBTreeNodeBase<Ptr_>::maximum(BasePtr_ tree) noexcept {
  while (tree->right_ != nullptr) {
    tree = tree->right_;
  }
  return tree;
}

template <typename Ptr_>
RBTreeNodeBase<Ptr_>::BasePtr_ RBTreeNodeBase<Ptr_>::minimum(BasePtr_ tree) noexcept {
  while (tree->left_ != nullptr) {
    tree = tree->left_;
  }
  return tree;
}

template <typename Ptr_>
RBTreeNodeBase<Ptr_>::BasePtr_ RBTreeNodeBase<Ptr_>::base_ptr() const noexcept {
  return const_cast<BasePtr_>(this);
}

template <typename NodeBase_>
RBTreeHeader<NodeBase_>::RBTreeHeader() noexcept {
  header_.color_ = RBTreeColor::kRed;    
  reset();
}

template <typename NodeBase_>
RBTreeHeader<NodeBase_>::RBTreeHeader(RBTreeHeader&& other) noexcept {
  if (other.header_.parent_ != nullptr) {
    move_data(other);
  } else {
    header_.color_ = RBTreeColor::kRed;
    reset();
  }
}

template <typename NodeBase_>
void RBTreeHeader<NodeBase_>::reset() noexcept {
 header_.parent_  = nullptr;
 header_.left_ = &header_;
 header_.right_ = &header_;
 node_count_ = 0;
}

template <typename NodeBase_>
void RBTreeHeader<NodeBase_>::move_data(RBTreeHeader& other) noexcept {
  header_ = other.header_;
  header_.parent_->parent_  = &header_;
  node_count_ = other.node_count_;
  other.reset();
}

template <typename KeyCompare_>
RBTreeKeyCompare<KeyCompare_>::RBTreeKeyCompare()
  noexcept(std::is_nothrow_default_constructible_v<KeyCompare_>)
  : key_compare_()
  {}
  
template <typename KeyCompare_>
RBTreeKeyCompare<KeyCompare_>::RBTreeKeyCompare(RBTreeKeyCompare&& other)
  noexcept(std::is_nothrow_default_constructible_v<KeyCompare_>)
  : key_compare_(other.key_compare_) 
  {}


template <typename Val_>
[[nodiscard]] 
Val_* RBTreeNode<Val_>::valptr() noexcept {
  return std::launder(reinterpret_cast<Val_*>(storage_));
}

template <typename Val_>
[[nodiscard]]
const Val_* RBTreeNode<Val_>::valptr() const noexcept {
  return std::launder(reinterpret_cast<const Val_*>(storage_));
}

template <typename Val_>
[[nodiscard]]
RBTreeNode<Val_>* RBTreeNode<Val_>::node_ptr() noexcept {
  return this; 
}

template <typename Val_>
[[nodiscard]]
const RBTreeNode<Val_>* RBTreeNode<Val_>::node_ptr() const noexcept {
  return this; 
}

}  // namespace s21


#endif  // S21_RB_TREE_INL
