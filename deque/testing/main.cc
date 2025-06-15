#include "../deque_map/deque.h"

int main() {
  // s21::Deque<long double> d1{1, 2, 3, 4, 5};
  // auto itE = d1.End();
  // int i = 1;
  // for (auto itB = d1.Begin(); itB != itE; ++itB) {
  //   if (*itB == 0) {
  //     std::cout << i++ << " ";
  //   }
  // }

  // s21::Deque<long double> d2(d1);
  // for (auto itB2 = d2.Begin(); itB2 != d2.End(); ++itB2) {
  //   std::cout << *itB2 << std::endl;
  // }

  // s21::Deque<long double> d1{1, 2, 3, 4, 5};
  s21::Deque<long double> d1;
  d1.PushBack(6);
  d1.PushBack(7);
  d1.PushBack(8);
  d1.PopFront();
  d1.PopFront();
  d1.PopFront();
  d1.PopFront();
  d1.PopFront();
  d1.PopFront();
  d1.PopFront();
  for (auto it = d1.Begin(); it != d1.End(); ++it) {
    std::cout << *it << std::endl;
  }
  return 0;
}