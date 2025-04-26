#ifndef S21_MAP_H
#define S21_MAP_H

#include <functional>
#include <memory>

namespace s21 {

/*
 * @class map
 * @brief Реализация контейнера map аналогичного std::map
 */
template <typename Key_, typename Value_, typename Compare_ = std::less<Key_>,
          typename Alloc_ = std::allocator<std::pair<const Key_, Value_>>>
class map {};

}  // namespace s21

#endif  // S21_MAP_H
