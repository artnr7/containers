#include <iostream>
#include <deque>

int main (){

  std::deque num = {1,2};
  int& a = num[1];
  num.push_back(3);
  std::cout << a;
  return 0;
}