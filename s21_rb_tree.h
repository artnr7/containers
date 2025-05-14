#ifndef S21_MAP_H
#define S21_MAP_H

#include <type_traits>
#include <cstddef>
#include <new>

namespace s21 {

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

struct RBTreeHeader {
  RBTreeNodeBase header_;
  std::size_t node_count_{0};

  RBTreeHeader() noexcept;
  RBTreeHeader(RBTreeHeader&& other) noexcept;

  void reset() noexcept;
  void move_data(RBTreeHeader& other) noexcept;
};

template <typename Val_>
struct RBTreeNode : RBTreeNodeBase {
  std::byte storage_[sizeof(Val_)] alignas(Val_);

  [[nodiscard]] Val_* valptr() noexcept;
  [[nodiscard]] const Val_* valptr() const noexcept;

  [[nodiscard]] RBTreeNode* node_ptr() noexcept;
  [[nodiscard]] const RBTreeNode* node_ptr() const noexcept;
};

template <typename KeyCompare_>
struct RBTreeKeyCompare {
  KeyCompare_ key_compare_;

  RBTreeKeyCompare()
    noexcept(std::is_nothrow_default_constructible_v<KeyCompare_>);
  RBTreeKeyCompare(const RBTreeKeyCompare& other) = default;
  RBTreeKeyCompare(RBTreeKeyCompare&& other)
    noexcept(std::is_nothrow_default_constructible_v<KeyCompare_>);
};

}  // namespace s21

#include "s21_rb_tree.ipp"

#endif  // S21_MAP_H
