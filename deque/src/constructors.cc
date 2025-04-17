#include "../include/deque.h"

/*--------→ CONSTRUCTORS ←-------------*/

template <typename T>
s21::Deque<T>::Deque()
    : _chunk_size(0), _chunk_map(nullptr), _start(nullptr), _finish(nullptr) {}

template <typename T> s21::Deque<T>::Deque(size_t Tp_qty) {
  size_t &chunk_capacity = nullptr;
  GetChunkCapacity(chunk_capacity);
  DeqInit(Tp_qty);
  BlocksFill(0); // чем заполнять если тип может быть шаблонным, вопрос
}

template <typename T> s21::Deque<T>::Deque(size_t Tp_qty, T value) {
  size_t &chunk_capacity = nullptr;
  GetChunkCapacity(chunk_capacity);
  DeqInit(Tp_qty);
  BlocksFill(value, chunk_capacity);
}

/** @brief
 * @param values это экземпляр типа initializer_list, которая передаёт данные в
 * скобочках */
template <typename T>
s21::Deque<T>::Deque(const std::initializer_list<T> &values) {
  size_t &chunk_capacity = nullptr;
  GetChunkCapacity(chunk_capacity);
  DeqInit(const values.size());
  BlocksFill(values, chunk_capacity);
}

template <typename T> s21::Deque<T>::~Deque() { MemFree(); }
