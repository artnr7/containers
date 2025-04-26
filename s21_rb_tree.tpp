#ifndef S21_RB_TREE_TPP
#define S21_RB_TREE_TPP

#include "s21_rb_tree.h"

namespace s21 {

RBTreeNodeBase::BasePtr_ RBTreeNodeBase::maximum(BasePtr_ tree) {
    while (tree->right_ != nullptr) {
        tree = tree->right_;
    }
    return tree;
}

RBTreeNodeBase::BasePtr_ RBTreeNodeBase::minimum(BasePtr_ tree) {
    while (tree->left_ != nullptr) {
        tree = tree->left_;
    }
    return tree;
}

}  // namespace s21

#endif  // S21_RB_TREE_TPP
