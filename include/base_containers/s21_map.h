#ifndef S21_MAP_H_
#define S21_MAP_H_

#include <functional>
#include <memory>

#include "rb_tree/s21_rb_tree.h"

namespace s21 {

template <typename Key_, typename T_, typename Compare_ = std::less<Key_>,
          typename Alloc_ = std::allocator<std::pair<const Key_, T_>>>
class Map {
 public:
  using KeyType = Key_;
  using MapType = T_;
  using KeyCompare = Compare_;
  using AllocatorType = Alloc_;
  using ValueType = std::pair<const Key_, T_>;

 private:
  using PairAlloc_ =
      std::allocator_traits<AllocatorType>::template rebind_alloc<ValueType>;
  using RbTree_ = RbTree<KeyType, ValueType, rb_tree::SelectFirst<ValueType>,
                         KeyCompare, PairAlloc_>;

  using AllocTraits_ = std::allocator_traits<PairAlloc_>;

  template <typename OtherCompare_>
  using OtherMap_ = Map<Key_, T_, OtherCompare_, Alloc_>;

  template <typename, typename>
  friend struct RbTreeMergeHelper;

  RbTree_ rb_tree_;

 public:
  using Reference = ValueType&;
  using ConstReference = const ValueType&;

  using Iterator = RbTree_::Iterator;
  using ConstIterator = RbTree_::ConstIterator;

  using SizeType = RbTree_::SizeType;

  Map() = default;
  Map(const Map&) = default;
  Map(Map&&) = default;
  ~Map() = default;

  Map(std::initializer_list<ValueType> const& items,
      const KeyCompare& compare = KeyCompare(),
      const AllocatorType& alloc = AllocatorType());

  Map& operator=(Map&) = default;
  Map& operator=(Map&&) = default;

  MapType& At(const KeyType& key);
  MapType& operator[](const KeyType& key);

  Iterator Begin() noexcept;
  Iterator End() noexcept;

  ConstIterator Begin() const noexcept;
  ConstIterator End() const noexcept;

  bool Empty() const noexcept;
  SizeType Size() const noexcept;
  SizeType MaxSize() const noexcept;

  void Clear();
  std::pair<Iterator, bool> Insert(const ValueType& pair);
  std::pair<Iterator, bool> Insert(const KeyType& key, const MapType& value);
  std::pair<Iterator, bool> InsertOrAssign(const KeyType& key,
                                           const MapType& value);

  void Erase(Iterator pos);
  void Swap(Map& other);

  template <typename OtherCompare_>
  void Merge(OtherMap_<OtherCompare_>& other);

  bool Contains(const KeyType& key) const;

  template <typename... Args>
  Vector<std::pair<Iterator, bool>> InsertMany(Args&&... args);
};

template <typename Key_, typename Val_, typename Compare_, typename Alloc_,
          typename OtherCompare_>
struct RbTreeMergeHelper<Map<Key_, Val_, Compare_, Alloc_>, OtherCompare_> {
 private:
  friend class Map<Key_, Val_, Compare_, Alloc_>;

  static auto& GetRbTree(Map<Key_, Val_, OtherCompare_, Alloc_>& other_map) {
    return other_map.rb_tree_;
  }
};

template <typename Key_, typename T_, typename Compare_, typename Alloc_>
Map<Key_, T_, Compare_, Alloc_>::Map(
    std::initializer_list<ValueType> const& items, const KeyCompare& compare,
    const AllocatorType& alloc)
    : rb_tree_(compare, alloc) {
  rb_tree_.InsertRangeUnique(items.begin(), items.end());
}

template <typename Key_, typename T_, typename Compare_, typename Alloc_>
Map<Key_, T_, Compare_, Alloc_>::MapType& Map<Key_, T_, Compare_, Alloc_>::At(
    const KeyType& key) {
  auto it = rb_tree_.LowerBound(key);
  if (it == rb_tree_.end() || KeyCompare()(key, it->first)) {
    throw std::out_of_range("Map::at: key not found");
  }
  return it->second;
}

template <typename Key_, typename T_, typename Compare_, typename Alloc_>
Map<Key_, T_, Compare_, Alloc_>::MapType&
Map<Key_, T_, Compare_, Alloc_>::operator[](const KeyType& key) {
  auto it = rb_tree_.LowerBound(key);
  if (it == rb_tree_.end() || KeyCompare()(key, it->first)) {
    it = rb_tree_.InsertHintUnique(it, key);
  }
  return it->second;
}

template <typename Key_, typename T_, typename Compare_, typename Alloc_>
Map<Key_, T_, Compare_, Alloc_>::Iterator
Map<Key_, T_, Compare_, Alloc_>::Begin() noexcept {
  return rb_tree_.begin();
}

template <typename Key_, typename T_, typename Compare_, typename Alloc_>
Map<Key_, T_, Compare_, Alloc_>::Iterator
Map<Key_, T_, Compare_, Alloc_>::End() noexcept {
  return rb_tree_.end();
}

template <typename Key_, typename T_, typename Compare_, typename Alloc_>
Map<Key_, T_, Compare_, Alloc_>::ConstIterator
Map<Key_, T_, Compare_, Alloc_>::Begin() const noexcept {
  return rb_tree_.begin();
}

template <typename Key_, typename T_, typename Compare_, typename Alloc_>
Map<Key_, T_, Compare_, Alloc_>::ConstIterator
Map<Key_, T_, Compare_, Alloc_>::End() const noexcept {
  return rb_tree_.end();
}

template <typename Key_, typename T_, typename Compare_, typename Alloc_>
bool Map<Key_, T_, Compare_, Alloc_>::Empty() const noexcept {
  return rb_tree_.Empty();
}

template <typename Key_, typename T_, typename Compare_, typename Alloc_>
Map<Key_, T_, Compare_, Alloc_>::SizeType
Map<Key_, T_, Compare_, Alloc_>::Size() const noexcept {
  return rb_tree_.Size();
}

template <typename Key_, typename T_, typename Compare_, typename Alloc_>
Map<Key_, T_, Compare_, Alloc_>::SizeType
Map<Key_, T_, Compare_, Alloc_>::MaxSize() const noexcept {
  return rb_tree_.MaxSize();
}

template <typename Key_, typename T_, typename Compare_, typename Alloc_>
void Map<Key_, T_, Compare_, Alloc_>::Clear() {
  rb_tree_.Clear();
}

template <typename Key_, typename T_, typename Compare_, typename Alloc_>
std::pair<typename Map<Key_, T_, Compare_, Alloc_>::Iterator, bool>
Map<Key_, T_, Compare_, Alloc_>::Insert(const ValueType& pair) {
  return rb_tree_.InsertUnique(pair);
}

template <typename Key_, typename T_, typename Compare_, typename Alloc_>
std::pair<typename Map<Key_, T_, Compare_, Alloc_>::Iterator, bool>
Map<Key_, T_, Compare_, Alloc_>::Insert(const KeyType& key,
                                        const MapType& value) {
  return rb_tree_.InsertUnique(std::make_pair(key, value));
}

template <typename Key_, typename T_, typename Compare_, typename Alloc_>
std::pair<typename Map<Key_, T_, Compare_, Alloc_>::Iterator, bool>
Map<Key_, T_, Compare_, Alloc_>::InsertOrAssign(const KeyType& key,
                                                const MapType& value) {
  auto it = rb_tree_.LowerBound(key);
  bool inserted = false;

  if (it == rb_tree_.end() || KeyCompare()(key, it->first)) {
    auto insert_result = rb_tree_.InsertUnique(std::make_pair(key, value));
    it = insert_result.first;
    inserted = insert_result.second;
  } else {
    it->second = value;
  }

  return {it, inserted};
}

template <typename Key_, typename T_, typename Compare_, typename Alloc_>
void Map<Key_, T_, Compare_, Alloc_>::Erase(Iterator position) {
  rb_tree_.Erase(position);
}

template <typename Key_, typename T_, typename Compare_, typename Alloc_>
void Map<Key_, T_, Compare_, Alloc_>::Swap(Map& other) {
  rb_tree_.Swap(other.rb_tree_);
}

template <typename Key_, typename T_, typename Compare_, typename Alloc_>
template <typename OtherCompare_>
void Map<Key_, T_, Compare_, Alloc_>::Merge(OtherMap_<OtherCompare_>& other) {
  rb_tree_.MergeUnique(RbTreeMergeHelper<Map, OtherCompare_>::GetRbTree(other));
}

template <typename Key_, typename T_, typename Compare_, typename Alloc_>
bool Map<Key_, T_, Compare_, Alloc_>::Contains(const KeyType& key) const {
  return rb_tree_.Find(key) != rb_tree_.end();
}

template <typename Key_, typename T_, typename Compare_, typename Alloc_>
template <typename... Args>
Vector<std::pair<typename Map<Key_, T_, Compare_, Alloc_>::Iterator, bool>>
Map<Key_, T_, Compare_, Alloc_>::InsertMany(Args&&... args) {
  return rb_tree_.InsertManyUnique(std::forward<Args>(args)...);
}

}  //  namespace s21
#endif  //  S21_MAP_H_
