#include "../deque_map/deque.h"

int main() {
  s21::Deque<int> d1(0);
  auto itE = d1.End();
  int i = 1;
  for (auto itB = d1.Begin(); itB != itE; ++itB) {
    if (*itB == 0) {
      std::cout << i++ << " ";
    }
  }
  return 0;
}