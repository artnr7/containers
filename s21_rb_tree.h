#ifndef S21_MAP_H
#define S21_MAP_H

#include <type_traits>
#include <cstddef>
#include <memory>
#include <new>

namespace s21 {

/*
 * @class RBTree @brief Реализация красно-черного дерева
 */
enum class RBTreeColor : bool { kRed = false, kBlack = true };

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

template <typename ValPtr_>
struct RBTreeNode : public RBTreeNodeBase<
    typename std::pointer_traits<ValPtr_>:: template rebind<void>
  > {

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
