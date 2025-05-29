#include "../deque_map/deque.h"

int main() {
  s21::Deque<int> d1(5);
  auto itE = d1.End();
  for (auto itB = d1.Begin(); itB != itE; itB++) {
    if (*itB == 0) {
      std::cout << "1";
    }
  }
  return 0;
}