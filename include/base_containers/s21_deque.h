#ifndef S21_DEQUE_
#define S21_DEQUE_

#include <algorithm>
namespace s21 {
template <typename T>
class Deque {
 public:
  using ValueType = T;
  using Reference = T &;
  using ConstReference = const T &;
  using SizeType = size_t;

  class Iterator {
   public:
    /*--------→ CONSTRUCTORS ←-------------*/
    Iterator() noexcept
        : _cur_chunk(nullptr),
          _cur_el(nullptr),
          _first_el(nullptr),
          _last_el(nullptr) {}
    // @todo не знаю как сделать с помощью const чтобы нельзя изменить что-то
    // внутри конструктора ↓
    Iterator(T **cur_chunk, T *cur_elt, T *first_el, T *last_el) noexcept
        : _cur_chunk(cur_chunk),
          _cur_el(cur_elt),
          _first_el(first_el),
          _last_el(last_el) {}

    Iterator(const Iterator &o)
        : _cur_chunk(o._cur_chunk),
          _cur_el(o._cur_el),
          _first_el(o._first_el),
          _last_el(o._last_el) {}

    Iterator(Iterator &&o) noexcept
        : _cur_chunk(std::move(o._cur_chunk)),
          _cur_el(std::move(o._cur_el)),
          _first_el(std::move(o._first_el)),
          _last_el(std::move(o._last_el)) {
      o._cur_chunk = nullptr;
      o._cur_el = nullptr;
      o._first_el = nullptr;
      o._last_el = nullptr;
    }
    ~Iterator() {
      _cur_chunk = nullptr, _cur_el = nullptr, _first_el = nullptr,
      _last_el = nullptr;
    }

    /*--------→ OPERATORS ←-------------*/
    Reference operator*() const noexcept { return *_cur_el; }

    Iterator &operator++() {
      ++_cur_el;
      if (_cur_el == _last_el) {
        ++_cur_chunk;
        _cur_el = *_cur_chunk;
        _first_el = *_cur_chunk;
        _last_el = *_cur_chunk + GetChunkCapacity();
      }
      return *this;
    }

    Iterator &operator--() {
      if (_cur_el == _first_el) {
        --_cur_chunk;
        _cur_el = *_cur_chunk + GetChunkCapacity() - 1;
        _first_el = *_cur_chunk;
        _last_el = *_cur_chunk + GetChunkCapacity();
      } else {
        --_cur_el;
      }
      return *this;
    }

    Iterator &operator=(const Iterator &o) {
      if (this == &o) {
        return *this;
      }
      _cur_chunk = o._cur_chunk;
      _cur_el = o._cur_el;
      _first_el = o._first_el;
      _last_el = o._last_el;

      return *this;
    }

    Iterator &operator=(Iterator &&o) noexcept {
      if (this == &o) {
        return *this;
      }
      _cur_chunk = o._cur_chunk;
      _cur_el = o._cur_el;
      _first_el = o._first_el;
      _last_el = o._last_el;

      o._cur_chunk = nullptr;
      o._cur_el = nullptr;
      o._first_el = nullptr;
      o._last_el = nullptr;

      return *this;
    }

    bool operator!=(const Iterator &o) {
      return (_cur_chunk != o._cur_chunk || _cur_el != o._cur_el ||
              _first_el != o._first_el || _last_el != o._last_el);
    }
    /** @todo сделать как отрицание operator!= */
    bool operator==(const Iterator &o) {
      return (_cur_chunk == o._cur_chunk && _cur_el == o._cur_el &&
              _first_el == o._first_el && _last_el == o._last_el);
    }

   private:
    friend class Deque<T>;

    T **_cur_chunk;
    T *_cur_el;
    T *_first_el;
    T *_last_el;
  };

  /*--------→ CONSTRUCTORS ←-------------*/
  /** @brief Конструктор по умолчанию, а также по кол-ву значений
   * @param value значение ШТ */
  explicit Deque(const size_t Tp_qty = 0)
      : _map_size(0), _map(nullptr), _start(), _finish() {
    HandleMaxSizeCtorEx(Tp_qty);
    if (!EqZero(Tp_qty)) {
      DeqInit(Tp_qty);
      BlocksFill();
    }
  }

  /** @brief Конструктор из пары (кол-во значений, значение)
   * @param value значение ШТ */
  Deque(const size_t Tp_qty, T value) {
    HandleZeroCtorEx(Tp_qty);
    HandleMaxSizeCtorEx(Tp_qty);

    DeqInit(Tp_qty);
    BlocksFill(value);
  }

  /** @brief Конструктор из initializer_list
   * @param values initializer_list, которая передаёт данные в скобочках */
  Deque(const std::initializer_list<T> &values)
      : _map_size(0), _map(nullptr), _start(), _finish() {
    HandleMaxSizeCtorEx(values.size());

    if (!EqZero(values.size())) {
      DeqInit(values.size());
      BlocksFill(values);
    }
  }

  /** @brief Конструктор копирования */
  Deque(const Deque &o)
      : _map_size(o._map_size),
        _map(o._map),
        _start(o._start),
        _finish(o._finish) {
    if (!EqZero(o.Size())) {
      Malloc(GetChunkCapacity(), o.Size() / GetChunkCapacity() + 1);
      auto thisitB = Begin();
      for (auto itB = o.Begin(); itB != o.End(); ++itB, ++thisitB) {
        *thisitB = *itB;
      }
    }
  }

  /** @brief Конструктор перемешщения */
  Deque(Deque &&o) noexcept
      : _map_size(std::move(o._map_size)),
        _map(std::move(o._map)),
        _start(std::move(o._start)),
        _finish(std::move(o._finish)) {
    o._map_size = 0;
    o._map = nullptr;
    o._start = Iterator();
    o._finish = Iterator();
  }

  /** @brief Деструктор */
  ~Deque() { Mdealloc(); }

  /*==================→ OPERATORS ←=====================*/
  /*--------→ ASSIGNMENT ←-------------*/
  Deque<T> &operator=(const Deque<T> &o) {
    if (this == &o) {
      return *this;
    }
    Mdealloc();

    _map_size = o._map_size;
    _start = o._start;
    _finish = o._finish;

    if (!EqZero(o.Size())) {
      /** @note типо надо через временные объекты выделять и всё такое */
      Malloc(GetChunkCapacity(), o.Size() / GetChunkCapacity() + 1);
      auto thisitB = Begin();
      for (auto itB = o.Begin(); itB != o.End(); ++itB, ++thisitB) {
        *thisitB = *itB;
      }
    } else {
      _map = o._map;
    }
    return *this;
  }

  Deque<T> &operator=(Deque<T> &&o) noexcept {
    if (this == &o) {
      return *this;
    }
    Mdealloc();

    _map_size = std::move(o._map_size);
    _start = std::move(o._start);
    _finish = std::move(o._finish);
    _map = std::move(o._map);

    o._map_size = 0;
    o._map = nullptr;
    o._start = Iterator();
    o._finish = Iterator();

    return *this;
  }

  /*--------→ METHODS  ←-----------*/
  Reference Front() { return *_start._cur_el; }
  ConstReference Front() const { return *_start._cur_el; }

  Reference Back() {
    Iterator tmp_finish(_finish);
    --tmp_finish;
    return *tmp_finish._cur_el;
  }
  ConstReference Back() const {
    Iterator tmp_finish(_finish);
    --tmp_finish;
    return *tmp_finish._cur_el;
  }

  void PopBack() {  // удаление последнего элемента
    if (Size()) {
      --_finish;
      *_finish._cur_el = T{};
    }
  }

  void PopFront() {  // удаление последнего элемента
    if (Size()) {
      *_start._cur_el = T{};
      ++_start;
    }
  }

  template <typename... Args>
  void AppendRange(Args &&...args) {
    (PushBack(std::forward<Args>(args)), ...);
  }

  template <typename U>
  void PushBack(U &&value) {
    const size_t &chunk_capacity = GetChunkCapacity();
    if (_map == nullptr) {
      DeqInit(1);
      *(_start._cur_el) = std::forward<U>(value);
    } else {
      ExpandMapDown(chunk_capacity);

      *(_finish._cur_el) = std::forward<U>(value);
      ++_finish;
    }
    ExpandMapsize(chunk_capacity);
  }

  template <typename U>
  void PushFront(U &&value) {
    const size_t &chunk_capacity = GetChunkCapacity();
    if (_map == nullptr) {
      DeqInit(1);
    } else {
      ExpandMapUp(chunk_capacity);
      --_start;
    }
    *(_start._cur_el) = std::forward<U>(value);
    ExpandMapsize(chunk_capacity);
  }

  /** @brief Вычисляет количество элементов, содержащихся в deque */
  size_t Size() const noexcept {
    size_t size = 0;
    if (_map != nullptr) {
      for (Iterator it = Begin(); it != End(); ++it) {
        ++size;
      }
    }
    return size;
  }

  /** @brief Является ли deque пустым */
  bool Empty() const noexcept { return !Size(); }

  Iterator Begin() const noexcept { return _start; }

  Iterator End() const noexcept { return _finish; }

#define CONTAINER_ELEM_MAX_QTY 4611686018427387903  // ← в элементах 2^62
  constexpr size_t MaxSize() noexcept { return CONTAINER_ELEM_MAX_QTY; }

 private:
  friend class Iterator;

  /*--------→  VARIABLES ←-------------*/
  // ↓ кол-во указателей, которые доступны, а не кол-во чанков под данные
  size_t _map_size;
  T **_map;
  Iterator _start;
  Iterator _finish;

  /*--------→ PRIVATE FUNCTIONS ←-------------*/
  /** @note Определения
   * ШТ - Шаблонный тип */

#define BUF_SIZE 512  // ← в байтах
  /** @brief Нахождение максимально возможно количества вмещенных ШТ в
   * BUF_SIZE*/
  constexpr static size_t GetChunkCapacity() noexcept {
    /* Если размер ШТ < BUF_SIZE, то вычисляем какое кол-во их можно
     * вместить  в одном чанке Если размер > (1/2 * BUF_SIZE), то кол-во ШТ
     * в одном чанке будет равно 1
     */
    return sizeof(T) < BUF_SIZE ? size_t(BUF_SIZE / sizeof(T)) : size_t(1);
  }

#define RESERVE_SHIFT 1  // ← кол-во запасных указателей, != 0
  /** @brief Выделение памяти и инициализация итераторов */
  void DeqInit(const size_t Tp_qty) {
    const size_t &chunk_capacity = GetChunkCapacity();
    const size_t &chunks_qty = Tp_qty / chunk_capacity + 1;
    _map_size = chunks_qty + 2 * RESERVE_SHIFT;
    Malloc(chunk_capacity, chunks_qty);

    _start._cur_chunk = _map + RESERVE_SHIFT;
    _start._cur_el = _map[RESERVE_SHIFT];
    _start._first_el = _map[RESERVE_SHIFT];
    _start._last_el = _map[RESERVE_SHIFT] + chunk_capacity;

    size_t finish_i = RESERVE_SHIFT + chunks_qty - 1;
    _finish._cur_chunk = _map + finish_i;
    // взятие остатка(то есть порядок внутри чанка)↓
    _finish._cur_el = _map[finish_i] + Tp_qty % chunk_capacity;
    _finish._first_el = _map[finish_i];
    _finish._last_el = _map[finish_i] + chunk_capacity;
  }

  void Malloc(const size_t &chunk_capacity, const size_t &chunks_qty) {
    try {
      _map = new T *[_map_size] {};
      for (size_t i = 0; i < chunks_qty; ++i) {
        _map[i + RESERVE_SHIFT] = new T[chunk_capacity]{};
      }

    } catch (const std::bad_alloc &e) {
      std::cerr << e.what() << std::endl;
      std::terminate();
    }
  }

  /** @brief Освобождение памяти, используется в конструкторах */
  void Mdealloc() noexcept {
    if (_map != nullptr) {
      for (size_t i = 0; i < _map_size; ++i) {
        delete[] _map[i];
        _map[i] = nullptr;
      }
      delete[] _map;
      _map = nullptr;
    }
  }

  void ExpandMapDown(const size_t &chunk_capacity) {
    Iterator tmp_finish(_finish);
    ++tmp_finish;
    // если след.чанк == nullptr, а не указывает на выделенную память ↓
    if (*(tmp_finish._cur_chunk) == nullptr) {
      ++_finish._cur_chunk;
      *(_finish._cur_chunk) = new T[chunk_capacity];
      --_finish._cur_chunk;
    }
  }

  void ExpandMapUp(const size_t &chunk_capacity) {
    Iterator tmp_start(_start);
    --tmp_start;
    if (*(tmp_start._cur_chunk) == nullptr) {
      --_start._cur_chunk;
      *(_start._cur_chunk) = new T[chunk_capacity];
      ++_start._cur_chunk;
    }
  }

  /** @brief Функция увеличения размера _map_size в два раза, и перенос
   * старого массива указателей в середину нового
   * @test здесь надо будет тестировать те случаи, где выделяются блоки
   памяти,
   * кол-во которых будет нечетное, например 1,2,3,4,5(какие-нибудь
   * простые числа)*/
  // функция, которая проверяет, если энд находится в последней ячейке
  // последнего выделенного чанка и при этом указатель тоже последний надо
  // увеличивать мап в два раза,  лучше делать это заранее, потому что смещение
  // адреса кур-чанк на + 1 может попасть в невалидную область
  void ExpandMapsize(const size_t &chunk_capacity) {
    // если это последний чанк и последний элемент
    // еще можно добавить условие, что если следующий курчанк не равен нуллптр
    if ((size_t(_finish._cur_chunk - _map) == _map_size - 1 &&
         _finish._cur_el == _finish._last_el - 1) ||
        (_start._cur_chunk == _map && _start._cur_el == *_map)) {
      size_t expanded_map_size = _map_size * 2, half_map_size = _map_size / 2,
             start_cur_el_i = _start._cur_el - _start._first_el,
             finish_cur_el_i = _finish._cur_el - _finish._first_el,
             start_i = half_map_size + (_start._cur_chunk - _map),
             finish_i = half_map_size + size_t(_finish._cur_chunk - _map);
      // порядок начала нового _map это _map_size / 2
      T **tmp_map = new T *[expanded_map_size] {};
      for (size_t i = 0; i < _map_size; ++i) {
        tmp_map[half_map_size + i] = _map[i];
      }
      delete[] _map;
      _map = tmp_map;

      _start._cur_chunk = _map + start_i;
      _start._cur_el = _map[start_i] + start_cur_el_i;
      _start._first_el = _map[start_i];
      _start._last_el = _map[start_i] + chunk_capacity;

      _finish._cur_chunk = _map + finish_i;
      _finish._cur_el = _map[finish_i] + finish_cur_el_i;
      _finish._first_el = _map[finish_i];
      _finish._last_el = _map[finish_i] + chunk_capacity;

      _map_size = expanded_map_size;
    }
  }

  /** @brief Функция заполнения выделенной памяти стандартными значениями */
  void BlocksFill() {
    T default_value = T{};
    std::fill(Begin(), End(), default_value);
  }

  /** @brief Функция заполнения выделенной памяти заданными значениями */
  void BlocksFill(const T value) {  // @todo сделать const T& value
    std::fill(Begin(), End(), value);
  }

  /** @brief Функция заполнения выделенной памяти заданными значениями из
   * initializer_list */
  void BlocksFill(const std::initializer_list<T> values) {
    auto values_it = values.begin();
    for (auto itB = Begin(); itB != End(); ++itB, ++values_it) {
      *itB = *values_it;
    }
  }

  /*---------------→ Exceptions ←------------------*/
  /** @brief Обработчик исключений конструктора по умолчанию и конструктора
   * по инит_листу**/
  void HandleMaxSizeCtorEx(const size_t &Tp_qty) {
    try {
      TpqtyBiggerMaxSizeEx(Tp_qty);
    } catch (const std::invalid_argument &e) {
      std::cerr << e.what() << std::endl;
      std::terminate();
    }
  }

  /** @brief Обработчик исключений конструктора с парой (кол-во эл-тов,
   * значение)**/
  void HandleZeroCtorEx(const size_t &Tp_qty) {
    try {
      TpqtyEqZeroEx(Tp_qty);
    } catch (const std::invalid_argument &e) {
      std::cerr << e.what() << std::endl;
      std::terminate();
    }
  }

  /*---------------→ Utils ←------------------*/
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
};

}  // namespace s21

#endif
