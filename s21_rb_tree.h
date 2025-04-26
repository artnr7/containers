#ifndef S21_MAP_H
#define S21_MAP_H

namespace s21 {

enum class RBTreeColor : bool { kRed = false, kBlack = true };

struct RBTreeNodeBase {
  using BasePtr_ = RBTreeNodeBase*;

  BasePtr_ parent_;
  BasePtr_ left_;
  BasePtr_ right_;

  RBTreeColor color_;

  static BasePtr_ minimum(BasePtr_ tree);
  static BasePtr_ maximum(BasePtr_ tree);
};

struct RBTreeHeader : RBTreeNodeBase {

};

template <typename Value_>
struct RBTreeNode : RBTreeNodeBase {
  
};

}  // namespace s21

#include "s21_rb_tree.tpp"

#endif  // S21_MAP_H
