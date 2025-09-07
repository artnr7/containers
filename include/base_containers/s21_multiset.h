#ifndef S21_MULTISET_H_
#define S21_MULTISET_H_

#include <functional>
#include <memory>

#include "rb_tree/s21_rb_tree.h"

namespace s21 {

template <typename Key_, typename Compare_ = std::less<Key_>,
          typename Alloc_ = std::allocator<Key_>>
class Multiset {
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
  using OtherMultiset_ = Multiset<Key_, OtherCompare_, Alloc_>;

  template <typename, typename>
  friend struct RbTreeMergeHelper;

 public:
  Multiset() = default;
  Multiset(const Multiset&) = default;
  Multiset(Multiset&&) = default;
  ~Multiset() = default;

  Multiset(std::initializer_list<ValueType> const& items,
           const KeyCompare& compare = KeyCompare(),
           const AllocatorType& alloc = AllocatorType());

  Multiset& operator=(const Multiset&) = default;
  Multiset& operator=(Multiset&&) = default;

  Iterator Begin() noexcept;
  Iterator End() noexcept;

  ConstIterator Begin() const noexcept;
  ConstIterator End() const noexcept;

  bool Empty() const noexcept;
  SizeType Size() const noexcept;
  SizeType MaxSize() const noexcept;

  void Clear();
  Iterator Insert(const ValueType& value);
  void Erase(Iterator position);
  void Swap(Multiset& other);

  template <typename OtherCompare_>
  void Merge(OtherMultiset_<OtherCompare_>& other_set);

  SizeType Count(const KeyType& key) const;

  Iterator Find(const KeyType& key);
  ConstIterator Find(const KeyType& key) const;

  bool Contains(const KeyType& key) const;

  std::pair<Iterator, Iterator> EqualRange(const KeyType& key);
  std::pair<ConstIterator, ConstIterator> EqualRange(
      const KeyType& key) const;

  Iterator LowerBound(const KeyType& key);
  Iterator UpperBound(const KeyType& key);

  ConstIterator LowerBound(const KeyType& key) const;
  ConstIterator UpperBound(const KeyType& key) const;

  template <typename... Args>
  vector<std::pair<Iterator, bool>> InsertMany(Args&&... args);
};

template <typename Key_, typename Compare_, typename Alloc_,
          typename OtherCompare_>
struct RbTreeMergeHelper<Multiset<Key_, Compare_, Alloc_>, OtherCompare_> {
 private:
  friend class Multiset<Key_, OtherCompare_, Alloc_>;

  static auto& GetRbTree(
      Multiset<Key_, OtherCompare_, Alloc_>& other_multiset) {
    return other_multiset.rb_tree_;
  }
};

template <typename Key_, typename Compare_, typename Alloc_>
Multiset<Key_, Compare_, Alloc_>::Multiset(
    std::initializer_list<ValueType> const& items, const KeyCompare& compare,
    const AllocatorType& alloc)
    : rb_tree_(compare, alloc) {
  rb_tree_.InsertRangeEqual(items.begin(), items.end());
}

template <typename Key_, typename Compare_, typename Alloc_>
Multiset<Key_, Compare_, Alloc_>::Iterator
Multiset<Key_, Compare_, Alloc_>::Begin() noexcept {
  return rb_tree_.begin();
}

template <typename Key_, typename Compare_, typename Alloc_>
Multiset<Key_, Compare_, Alloc_>::Iterator
Multiset<Key_, Compare_, Alloc_>::End() noexcept {
  return rb_tree_.end();
}

template <typename Key_, typename Compare_, typename Alloc_>
Multiset<Key_, Compare_, Alloc_>::ConstIterator
Multiset<Key_, Compare_, Alloc_>::Begin() const noexcept {
  return rb_tree_.begin();
}

template <typename Key_, typename Compare_, typename Alloc_>
Multiset<Key_, Compare_, Alloc_>::ConstIterator
Multiset<Key_, Compare_, Alloc_>::End() const noexcept {
  return rb_tree_.end();
}

template <typename Key_, typename Compare_, typename Alloc_>
bool Multiset<Key_, Compare_, Alloc_>::Empty() const noexcept {
  return rb_tree_.Empty();
}

template <typename Key_, typename Compare_, typename Alloc_>
Multiset<Key_, Compare_, Alloc_>::SizeType
Multiset<Key_, Compare_, Alloc_>::Size() const noexcept {
  return rb_tree_.Size();
}

template <typename Key_, typename Compare_, typename Alloc_>
Multiset<Key_, Compare_, Alloc_>::SizeType
Multiset<Key_, Compare_, Alloc_>::MaxSize() const noexcept {
  return rb_tree_.MaxSize();
}

template <typename Key_, typename Compare_, typename Alloc_>
void Multiset<Key_, Compare_, Alloc_>::Clear() {
  rb_tree_.Clear();
}

template <typename Key_, typename Compare_, typename Alloc_>
Multiset<Key_, Compare_, Alloc_>::Iterator
Multiset<Key_, Compare_, Alloc_>::Insert(const ValueType& value) {
  return rb_tree_.InsertEqual(value);
}

template <typename Key_, typename Compare_, typename Alloc_>
void Multiset<Key_, Compare_, Alloc_>::Erase(Iterator position) {
  rb_tree_.Erase(position);
}

template <typename Key_, typename Compare_, typename Alloc_>
void Multiset<Key_, Compare_, Alloc_>::Swap(Multiset& other) {
  rb_tree_.Swap(other.rb_tree_);
}

template <typename Key_, typename Compare_, typename Alloc_>
template <typename OtherCompare_>
void Multiset<Key_, Compare_, Alloc_>::Merge(
    OtherMultiset_<OtherCompare_>& other) {
  rb_tree_.MergeEqual(
      RbTreeMergeHelper<Multiset, OtherCompare_>::GetRbTree(other));
}

template <typename Key_, typename Compare_, typename Alloc_>
Multiset<Key_, Compare_, Alloc_>::SizeType
Multiset<Key_, Compare_, Alloc_>::Count(const KeyType& key) const {
  return rb_tree_.Count(key);
}

template <typename Key_, typename Compare_, typename Alloc_>
Multiset<Key_, Compare_, Alloc_>::Iterator
Multiset<Key_, Compare_, Alloc_>::Find(const KeyType& key) {
  return rb_tree_.Find(key);
}

template <typename Key_, typename Compare_, typename Alloc_>
Multiset<Key_, Compare_, Alloc_>::ConstIterator
Multiset<Key_, Compare_, Alloc_>::Find(const KeyType& key) const {
  return rb_tree_.Find(key);
}

template <typename Key_, typename Compare_, typename Alloc_>
bool Multiset<Key_, Compare_, Alloc_>::Contains(const KeyType& key) const {
  return rb_tree_.Find(key) != rb_tree_.end();
}

template <typename Key_, typename Compare_, typename Alloc_>
std::pair<typename Multiset<Key_, Compare_, Alloc_>::Iterator,
          typename Multiset<Key_, Compare_, Alloc_>::Iterator>
Multiset<Key_, Compare_, Alloc_>::EqualRange(const KeyType& key) {
  return rb_tree_.EqualRange(key);
}

template <typename Key_, typename Compare_, typename Alloc_>
std::pair<typename Multiset<Key_, Compare_, Alloc_>::ConstIterator,
          typename Multiset<Key_, Compare_, Alloc_>::ConstIterator>
Multiset<Key_, Compare_, Alloc_>::EqualRange(const KeyType& key) const {
  return rb_tree_.EqualRange(key);
}

template <typename Key_, typename Compare_, typename Alloc_>
Multiset<Key_, Compare_, Alloc_>::Iterator
Multiset<Key_, Compare_, Alloc_>::LowerBound(const KeyType& key) {
  return rb_tree_.LowerBound(key);
}

template <typename Key_, typename Compare_, typename Alloc_>
Multiset<Key_, Compare_, Alloc_>::Iterator
Multiset<Key_, Compare_, Alloc_>::UpperBound(const KeyType& key) {
  return rb_tree_.UpperBound(key);
}

template <typename Key_, typename Compare_, typename Alloc_>
Multiset<Key_, Compare_, Alloc_>::ConstIterator
Multiset<Key_, Compare_, Alloc_>::LowerBound(const KeyType& key) const {
  return rb_tree_.LowerBound(key);
}

template <typename Key_, typename Compare_, typename Alloc_>
Multiset<Key_, Compare_, Alloc_>::ConstIterator
Multiset<Key_, Compare_, Alloc_>::UpperBound(const KeyType& key) const {
  return rb_tree_.UpperBound(key);
}

template <typename Key_, typename Compare_, typename Alloc_>
template <typename... Args>
vector<std::pair<typename Multiset<Key_, Compare_, Alloc_>::Iterator, bool>>
Multiset<Key_, Compare_, Alloc_>::InsertMany(Args&&... args) {
  return rb_tree_.InsertManyEqual(std::forward<Args>(args)...);
}

}  //  namespace s21

#endif  //  S21_MULTISET_H_
