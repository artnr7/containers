#include <gtest/gtest.h>

#include "./../s21_rb_tree.h"

namespace s21 {

TEST(RBTreeNodeBase, Minimum) {
  // NOLINTNEXTLINE(readability-isolate-declaration)
  RBTreeNodeBase node1, node2, node3, node4;

  node1.left_ = node1.right_ = nullptr;
  node3.left_ = node3.right_ = nullptr;
  node4.left_ = &node3;
  node4.right_ = nullptr;
  node2.left_ = &node1;
  node2.right_ = &node4;

  node1.parent_ = &node2;
  node3.parent_ = &node4;
  node4.parent_ = &node2;

  EXPECT_EQ(RBTreeNodeBase::minimum(&node2),
            &node1);  // Минимум всего дерева = node1
  EXPECT_EQ(RBTreeNodeBase::minimum(&node4),
            &node3);  // Минимум в поддереве node4 = node3
  EXPECT_EQ(RBTreeNodeBase::minimum(&node1),
            &node1);  // Минимум в листе = сам лист (на всякий случай)
}

TEST(RBTreeNodeBase, Maximum) {
  // NOLINTNEXTLINE(readability-isolate-declaration)
  RBTreeNodeBase node1, node2, node3, node4;

  node1.left_ = node1.right_ = nullptr;
  node2.left_ = &node1;
  node2.right_ = &node4;
  node3.left_ = node3.right_ = nullptr;
  node4.left_ = &node3;
  node4.right_ = nullptr;

  node1.parent_ = &node2;
  node3.parent_ = &node4;
  node4.parent_ = &node2;

  EXPECT_EQ(RBTreeNodeBase::maximum(&node2), &node4);
  EXPECT_EQ(RBTreeNodeBase::maximum(&node1), &node1);
}

}  // namespace s21
