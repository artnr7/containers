#include "../deque.h"

/*--------→ CONSTRUCTORS ←-------------*/
// template <typename T>
// s21::Deque<T>::Deque(const size_t Tp_qty)
//     : _chunk_size(0), _chunk_map(nullptr), _start(nullptr), _finish(nullptr)
//     {
//   if (Tp_qty < 1) {
//     return;
//   }
//   size_t *chunk_capacity = nullptr;
//   GetChunkCapacity(chunk_capacity);
//   DeqInit(Tp_qty);
//   BlocksFill(0); // чем заполнять если тип может быть шаблонным, вопрос
// }

template <typename T> s21::Deque<T>::Deque(const size_t Tp_qty, T value) {
  size_t chunk_capacity = 0;
  size_t &ref_chunk_capacity = chunk_capacity;
  GetChunkCapacity(chunk_capacity);
  DeqInit(Tp_qty, chunk_capacity);
  BlocksFill(value);
}

/** @brief
 * @param values initializer_list, которая передаёт данные в скобочках */
template <typename T>
s21::Deque<T>::Deque(const std::initializer_list<T> &values) {
  size_t *chunk_capacity = nullptr;
  GetChunkCapacity(chunk_capacity);
  DeqInit(values.size());
  BlocksFill(values);
}

template <typename T> s21::Deque<T>::~Deque() { MemFree(); }
