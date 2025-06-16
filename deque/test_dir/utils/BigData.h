#include <cmath>
#include <iostream>

template <size_t BIG_DATA_SIZE> class BigData {
public:
  BigData() : _data{} {}
  BigData(char ch) noexcept {
    for (size_t i = 0; i < BIG_DATA_SIZE; ++i) {
      _data[i] = ch;
    }
  }
  bool ValueProof(char ch ){
    bool thesame = true;
    for(size_t i = 0; i < BIG_DATA_SIZE && thesame == true; ++i){
      if (_data[i] != ch){
        thesame = false;
      }
    }
    return thesame;
  }
  ~BigData() noexcept {}
  size_t Size() noexcept { return sizeof(_data); }
  bool Empty() noexcept { return sizeof(_data); }

private:
  char _data[BIG_DATA_SIZE];
};