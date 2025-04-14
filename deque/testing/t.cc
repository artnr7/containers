#include <boost/pool/pool_alloc.hpp>
#include <deque>
#include <iostream>
#include <memory>

// #define BUF_SIZE 32768

// class BigData {
// private:
//   char _big_data[BUF_SIZE];
//   int _ch;

// public:
//   BigData(int chh) : _ch(chh) { fill(_ch); };
//   void fill(int ch) {
//     for (int i = 0; i < BUF_SIZE; i++) {
//       _big_data[i] = _ch;
//     }
//   }
//   void print() {
//     for (int i = 0; i < BUF_SIZE; i++) {
//       std::cout << _big_data[i] << " ";
//     }
//   }
// };

using namespace std;

int main() {

  // BigData data1{65};
  // BigData data2{65};
  // BigData data3{65};
  // BigData data4{66};

  // std::deque<BigData> deq1{data1, data2, data3};
  // deq1.push_back(data4);
  // deq1[3].print();

  // std::deque num = {1, 2};
  // int &a = num[1];
  // num.push_back(3);
  // std::cout << a;

  std::shared_ptr<int> sptr{new int{10}};

  cout << *sptr << "\n";

  std::deque<int, boost::pool<boost::default_user_allocator_new_delete>>
      boostdeq{1, 2, 3, 4};
}