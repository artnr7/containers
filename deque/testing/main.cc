#include "../deque_map/deque.h"

int main() {
  s21::Deque<long double> d1{1, 2, 3, 4, 5};
  // auto itE = d1.End();
  // int i = 1;
  // for (auto itB = d1.Begin(); itB != itE; ++itB) {
  //   if (*itB == 0) {
  //     std::cout << i++ << " ";
  //   }
  // }

  s21::Deque<long double> d2(std::move(d1));
  for (auto itB2 = d2.Begin(); itB2 != d2.End(); ++itB2) {
    std::cout << *itB2 << std::endl;
  }
  return 0;
}