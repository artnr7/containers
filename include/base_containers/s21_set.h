#ifndef S21_SET_H_
#define S21_SET_H_

#include <functional>
#include <memory>

#include "rb_tree/s21_rb_tree.h"

namespace s21 {

template <typename Key_, typename Compare_ = std::less<Key_>,
          typename Alloc_ = std::allocator<Key_>>
class Set {
 public:
  using KeyType = Key_;
  using ValueType = Key_;
  using KeyCompare = Compare_;
  using AllocatorType = Alloc_;

 private:
  using KeyAlloc_ =
      std::allocator_traits<AllocatorType>::template rebind_alloc<ValueType>;
  using RbTree_ = RbTree<KeyType, ValueType, rb_tree::Identity<ValueType>,
                         KeyCompare, KeyAlloc_>;

  using AllocTraits_ = std::allocator_traits<KeyAlloc_>;

  RbTree_ rb_tree_;

  using Reference = ValueType&;
  using ConstReference = const ValueType&;

  using Iterator = RbTree_::Iterator;
  using ConstIterator = RbTree_::ConstIterator;

  using SizeType = RbTree_::SizeType;

  template <typename OtherCompare_>
  using OtherSet_ = Set<Key_, OtherCompare_, Alloc_>;

  template <typename, typename>
  friend struct RbTreeMergeHelper;

 public:
  Set() = default;
  Set(const Set&) = default;
  Set(Set&&) = default;
  ~Set() = default;

  Set(std::initializer_list<ValueType> const& items,
      const KeyCompare& compare = KeyCompare(),
      const AllocatorType& alloc = AllocatorType());

  Set& operator=(const Set& other) = default;
  Set& operator=(Set&& other) = default;

  Iterator Begin() noexcept;
  Iterator End() noexcept;

  ConstIterator Begin() const noexcept;
  ConstIterator End() const noexcept;

  bool Empty() const noexcept;
  SizeType Size() const noexcept;
  SizeType MaxSize() const noexcept;

  void Clear();
  std::pair<Iterator, bool> Insert(const ValueType& value);
  void Erase(Iterator position);
  void Swap(Set& other);

  template <typename OtherCompare_>
  void Merge(OtherSet_<OtherCompare_>& other_set);

  Iterator Find(const KeyType& key);
  ConstIterator Find(const KeyType& key) const;
  bool Contains(const KeyType& key) const;

  template <typename... Args>
  vector<std::pair<Iterator, bool>> InsertMany(Args&&... args);
};

template <typename Key_, typename Compare_, typename Alloc_,
          typename OtherCompare_>
struct RbTreeMergeHelper<Set<Key_, Compare_, Alloc_>, OtherCompare_> {
 private:
  friend class Set<Key_, Compare_, Alloc_>;

  static auto& GetRbTree(Set<Key_, OtherCompare_, Alloc_>& other_set) {
    return other_set.rb_tree_;
  }
};

template <typename Key_, typename Compare_, typename Alloc_>
Set<Key_, Compare_, Alloc_>::Set(std::initializer_list<ValueType> const& items,
                                 const KeyCompare& compare,
                                 const AllocatorType& alloc)
    : rb_tree_(compare, alloc) {
  rb_tree_.InsertRangeUnique(items.begin(), items.end());
}

template <typename Key_, typename Compare_, typename Alloc_>
Set<Key_, Compare_, Alloc_>::Iterator
Set<Key_, Compare_, Alloc_>::Begin() noexcept {
  return rb_tree_.begin();
}

template <typename Key_, typename Compare_, typename Alloc_>
Set<Key_, Compare_, Alloc_>::Iterator
Set<Key_, Compare_, Alloc_>::End() noexcept {
  return rb_tree_.end();
}

template <typename Key_, typename Compare_, typename Alloc_>
Set<Key_, Compare_, Alloc_>::ConstIterator Set<Key_, Compare_, Alloc_>::Begin()
    const noexcept {
  return rb_tree_.begin();
}

template <typename Key_, typename Compare_, typename Alloc_>
Set<Key_, Compare_, Alloc_>::ConstIterator Set<Key_, Compare_, Alloc_>::End()
    const noexcept {
  return rb_tree_.end();
}

template <typename Key_, typename Compare_, typename Alloc_>
bool Set<Key_, Compare_, Alloc_>::Empty() const noexcept {
  return rb_tree_.Empty();
}

template <typename Key_, typename Compare_, typename Alloc_>
Set<Key_, Compare_, Alloc_>::SizeType Set<Key_, Compare_, Alloc_>::Size()
    const noexcept {
  return rb_tree_.Size();
}

template <typename Key_, typename Compare_, typename Alloc_>
Set<Key_, Compare_, Alloc_>::SizeType Set<Key_, Compare_, Alloc_>::MaxSize()
    const noexcept {
  return rb_tree_.MaxSize();
}

template <typename Key_, typename Compare_, typename Alloc_>
void Set<Key_, Compare_, Alloc_>::Clear() {
  rb_tree_.Clear();
}

template <typename Key_, typename Compare_, typename Alloc_>
std::pair<typename Set<Key_, Compare_, Alloc_>::Iterator, bool>
Set<Key_, Compare_, Alloc_>::Insert(const ValueType& value) {
  return rb_tree_.InsertUnique(value);
}

template <typename Key_, typename Compare_, typename Alloc_>
void Set<Key_, Compare_, Alloc_>::Erase(Iterator position) {
  rb_tree_.Erase(position);
}

template <typename Key_, typename Compare_, typename Alloc_>
void Set<Key_, Compare_, Alloc_>::Swap(Set& other) {
  rb_tree_.Swap(other.rb_tree_);
}

template <typename Key_, typename Compare_, typename Alloc_>
template <typename OtherCompare_>
void Set<Key_, Compare_, Alloc_>::Merge(OtherSet_<OtherCompare_>& other) {
  rb_tree_.MergeUnique(RbTreeMergeHelper<Set, OtherCompare_>::GetRbTree(other));
}

template <typename Key_, typename Compare_, typename Alloc_>
Set<Key_, Compare_, Alloc_>::Iterator Set<Key_, Compare_, Alloc_>::Find(
    const KeyType& key) {
  return rb_tree_.Find(key);
}

template <typename Key_, typename Compare_, typename Alloc_>
Set<Key_, Compare_, Alloc_>::ConstIterator Set<Key_, Compare_, Alloc_>::Find(
    const KeyType& key) const {
  return rb_tree_.Find(key);
}

template <typename Key_, typename Compare_, typename Alloc_>
bool Set<Key_, Compare_, Alloc_>::Contains(const KeyType& key) const {
  return rb_tree_.Find(key) != rb_tree_.end();
}

template <typename Key_, typename Compare_, typename Alloc_>
template <typename... Args>
vector<std::pair<typename Set<Key_, Compare_, Alloc_>::Iterator, bool>>
Set<Key_, Compare_, Alloc_>::InsertMany(Args&&... args) {
  return rb_tree_.InsertManyUnique(std::forward<Args>(args)...);
}

}  //  namespace s21

#endif  //  S21_SET_H_
