#include <cmath>
#include <iostream>

#define EPS 0.000001
template <size_t BIG_DATA_SIZE, typename T> class BigData {
public:
  explicit BigData() noexcept : _data() {}
  BigData(T value) noexcept : _data() {
    for (size_t i = 0; i < BIG_DATA_SIZE; ++i) {
      _data[i] = value;
    }
  }
  ~BigData() noexcept {}
  size_t Size() noexcept { return sizeof(_data); }
  bool ValueProof(T value) {
    bool thesame = true;
    for (size_t i = 0; i < BIG_DATA_SIZE; ++i) {
      if (std::fabs(_data[i] - value) >= EPS) {

        thesame = false;
      }
    }
    return thesame;
  }

private:
  T _data[BIG_DATA_SIZE];
};