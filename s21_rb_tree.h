#ifndef S21_MAP_H
#define S21_MAP_H

#include <type_traits>

namespace s21 {

#define CHECK_NOEXCEPT(COND) noexcept(COND)

/*
 * @class RBTree
 * @brief Реализация красно-черного дерева
 */
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

template <typename KeyCompare_>
struct RBTreeKeyCompare {
  RBTreeKeyCompare() noexcept(std::is_nothrow_default_constructible_v<KeyCompare_>) = default;
};

}  // namespace s21

#include "s21_rb_tree.tpp"

#endif  // S21_MAP_H
