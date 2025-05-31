#ifndef __DEQUE__
#define __DEQUE__

#include <algorithm>
#include <cmath>
#include <deque>
#include <iostream>

namespace s21 {
template <typename T> class Deque {

public:
  class Iterator {
  public:
    /*--------→ CONSTRUCTORS ←-------------*/
    Iterator() noexcept : _cur_chunk(nullptr), _cur_elt(nullptr) {}
    Iterator(T **cur_chunk,
             T *cur_elt) noexcept // ← не знаю как сделать с помощью const чтобы
                                  // нельзя изменить что-то внутри конструктора
        : _cur_chunk(cur_chunk), _cur_elt(cur_elt) {}

    Iterator(const Iterator &o) {
      _cur_chunk = o._cur_chunk;
      _cur_elt = o._cur_elt;
    }

    Iterator(const Iterator &&o) {
      _cur_chunk = o._cur_chunk;
      _cur_elt = o._cur_elt;

      o._cur_chunk = nullptr;
      o._cur_elt = nullptr;
    }
    ~Iterator() { _cur_chunk = nullptr, _cur_elt = nullptr; }

    /*--------→ OPERATORS ←-------------*/
    T &operator*() const noexcept { return *_cur_elt; }

    Iterator &operator++() {
      size_t chunk_capacity = 0;
      size_t &ref_chunk_capacity = chunk_capacity;
      GetChunkCapacity(ref_chunk_capacity);
      T *end_of_chunk = *(_cur_chunk) + chunk_capacity;
      if (_cur_elt != end_of_chunk) {
        _cur_elt++;
      } else { //@todo тут надо создавать новый чанк если нет места
        _cur_chunk++;
        _cur_elt = *_cur_chunk;
      }
      return *this;
    }

    Iterator &operator=(Iterator &o) {
      if (this == &o) {
        return *this;
      }
      _cur_chunk = o._cur_chunk;
      _cur_elt = o._cur_elt;

      return *this;
    }

    Iterator &operator=(Iterator &&o) noexcept {
      if (this == &o) {
        return *this;
      }
      _cur_chunk = o._cur_chunk;
      _cur_elt = o._cur_elt;

      o._cur_chunk = nullptr;
      o._cur_elt = nullptr;

      return *this;
    }

    bool operator!=(const Iterator &o) {
      return (_cur_chunk != o._cur_chunk || _cur_elt != o._cur_elt);
    }

    bool operator==(const Iterator &o) {
      return (_cur_chunk == o._cur_chunk && _cur_elt == o._cur_elt);
    }

  private:
    T **_cur_chunk;
    T *_cur_elt;
  };

  /*--------→ CONSTRUCTORS ←-------------*/

  explicit Deque(const size_t Tp_qty = 0)
      : _chunk_size(0), _chunk_map(nullptr), _start(), _finish() {
    HandleDefCtorEx(Tp_qty);

    if (!EqZero(Tp_qty)) {
      size_t chunk_capacity = 0;
      size_t &ref_chunk_capacity = chunk_capacity;
      GetChunkCapacity(ref_chunk_capacity);
      DeqInit(Tp_qty, ref_chunk_capacity);
      BlocksFill();
    }
  }

  Deque(const size_t Tp_qty, T value)
      : _chunk_size(0), _chunk_map(nullptr), _start(), _finish() {
    HandleCtorEx(Tp_qty);

    size_t chunk_capacity = 0;
    size_t &ref_chunk_capacity = chunk_capacity;
    GetChunkCapacity(ref_chunk_capacity);
    DeqInit(Tp_qty, ref_chunk_capacity);
    BlocksFill(value);
  }

  /** @brief
   * @param values initializer_list, которая передаёт данные в скобочках */
  Deque(const std::initializer_list<T> &values)
      : _chunk_size(0), _chunk_map(nullptr), _start(), _finish() {
    HandleCtorEx(values.size());

    size_t chunk_capacity = 0;
    size_t &ref_chunk_capacity = chunk_capacity;
    GetChunkCapacity(ref_chunk_capacity);

    DeqInit(values.size(), ref_chunk_capacity);
    BlocksFill(values);
  }

  Deque(const Deque &other);
  Deque(Deque &&other);
  ~Deque() { MemFree(); }

  /*--------→ OPERATORS ←-------------*/
  Deque<T> &operator=(const Deque<T> &other) {
    if (this == &other) {
      return *this;
    }
  }

  Deque<T> &operator=(Deque<T> &&other) noexcept {
    if (this == &other) {
      return *this;
    }
  }

  /*--------→ METHODS  ←-----------*/
  // bool PushFront() noexcept {}
  // void PushBack(int value) { int mem_blocks_qty = MemBlocksQty(elems_qty_); }
  // bool PushBack(const T &value) noexcept {
  //   T *end_of_chunk = *_cur_chunk + (chunk_capacity - 1);
  //   if (_finish)
  //     *(++_finish) = value;
  // }

  /** @brief Вычисляет размер deque */
  size_t Size() noexcept {
    size_t size = 0;
    for (Iterator it = Begin(); it != End(); ++it) {
      size++;
    }
    return size;
  }

  /** @brief Узнаёт является ли deque пустым */
  bool Empty() noexcept { return !Size(); }

  Iterator Begin() noexcept { return _start; }

  Iterator End() noexcept { return _finish; }

#define CONTAINER_ELEM_MAX_QTY 4611686018427387903
  constexpr size_t MaxSize() noexcept { return CONTAINER_ELEM_MAX_QTY; }

private:
  friend class Iterator;
  /*--------→  VARIABLES ←-------------*/
  size_t _chunk_size; // deque chunk size
  T **_chunk_map;
  Iterator _start;  // iterator
  Iterator _finish; // iterator

  /*--------→ PRIVATE FUNCTIONS ←-------------*/
  /** @note Определения
   * ШТ - Шаблонный тип */

#define BUF_SIZE 512 // ← в байтах
  /** @brief Нахождение максимально возможно количества вмещенных ШТ в
   * BUF_SIZE*/

  static void GetChunkCapacity(size_t &chunk_capacity) noexcept {
    /* Если размер ШТ < BUF_SIZE, то вычисляем какое кол-во их можно вместить  в
     * одном чанке
     * Если размер > (1/2 * BUF_SIZE), то кол-во ШТ в одном чанке будет равно 1
     */
    chunk_capacity =
        sizeof(T) < BUF_SIZE ? size_t(BUF_SIZE / sizeof(T)) : size_t(1);
  }

  /** @brief Выделение памяти и инициализация итераторов */

  void DeqInit(const size_t Tp_qty, const size_t &chunk_capacity) {
    _chunk_size = Tp_qty / chunk_capacity + 1;

    _chunk_map = new T *[_chunk_size];
    for (size_t i = 0; i < _chunk_size; i++) {
      _chunk_map[i] = new T[chunk_capacity];
      // @todo проверка на выделение памяти //
    }
    _start = Iterator(&_chunk_map[0], &_chunk_map[0][0]);

    _finish = Iterator(
        &_chunk_map[_chunk_size - 1],
        &_chunk_map[_chunk_size - 1][(Tp_qty - 1) % chunk_capacity] + 1);
    // взятие остатка(то есть порядок внутри чанка) ↑
  }

  /** @brief Освобождение памяти, используется в конструкторах */
  void MemFree() {
    for (size_t i = 0; i < _chunk_size; i++) {
      delete[] _chunk_map[i];
      _chunk_map[i] = nullptr;
    }
    delete[] _chunk_map;

    _chunk_map = nullptr;
  }

  /** @brief Функция заполнения выделенной памяти стандартными значениями */
  void BlocksFill() {
    T default_value = T{};
    std::fill(Begin(), End(), default_value);
  }

  /** @brief Функция заполнения выделенной памяти заданными значениями */
  void BlocksFill(const T value) { // @todo сделать const T& value
    std::fill(Begin(), End(), value);
  }
  /** @brief Функция заполнения выделенной памяти заданными значениями из
   * initializer_list */
  void BlocksFill(const std::initializer_list<T> values) {

    size_t val_i = 0;
    std::fill(Begin(), End(), values[val_i++]);
  }

  /*-----→ utils ←-------*/
  /** @brief Равен ли объект типа нулю **/
  bool EqZero(const size_t &sizet) { return sizet == 0; }

  /** @brief Если объект типа равен нулю, то выбрасывается исключение
   * недопустимого значения **/
  void TpqtyEqZeroEx(const size_t &Tp_qty) {
    if (EqZero(Tp_qty)) {
      throw std::invalid_argument(
          "To use this constructor Tp_qty must be greater than 0");
    }
  }

  /** @brief Если объект типа больше чем CONTAINER_ELEM_MAX_QTY, то
   * выбрасывается исключение недопустимого значения **/
  void TpqtyBiggerMaxSizeEx(const size_t &Tp_qty) {
    if (Tp_qty > MaxSize()) {
      throw std::invalid_argument(
          "To use this constructor Tp_qty must be less than MaxSize()");
    }
  }

  /** @brief Обработчик исключений конструктора по умолчанию**/
  void HandleDefCtorEx(const size_t &Tp_qty) {
    try {
      TpqtyBiggerMaxSizeEx(Tp_qty);
    } catch (const std::invalid_argument &e) {
      std::cerr << e.what() << std::endl;
      std::terminate();
    }
  }

  /** @brief Обработчик исключений конструктора с парой (кол-во эл-тов, значение)**/
  void HandleCtorEx(const size_t &Tp_qty) {
    try {
      TpqtyBiggerMaxSizeEx(Tp_qty);
      TpqtyEqZeroEx(Tp_qty);
    } catch (const std::invalid_argument &e) {
      std::cerr << e.what() << std::endl;
      std::terminate();
    }
  }
};

} // namespace s21

#endif