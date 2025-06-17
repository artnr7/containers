#include "../../utils/BigData.h"
#include "../../test_main.h"
#define N 8

TEST(append_range_method, big_data_1) {
  s21::Deque<BigData<256>> d1{};
  d1.AppendRange(1, 2, 3);

  int j = 1;

  for (auto itB = d1.Begin(); itB != d1.End(); ++itB, ++j) {
    for (size_t i = 0; i < 256; ++i) {
      EXPECT_EQ((*itB).ValueProof(j), 1);
    }
  }
}

TEST(back_method, big_data_2) {
  s21::Deque<BigData<256>> d1{1, 2, 3};
  d1.AppendRange(4, 5, 6);

  int j = 1;

  for (auto itB = d1.Begin(); itB != d1.End(); ++itB, ++j) {
    for (size_t i = 0; i < 256; ++i) {
      EXPECT_EQ((*itB).ValueProof(j), 1);
    }
  }
}