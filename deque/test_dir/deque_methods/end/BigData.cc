#include "../../utils/BigData.h"
#include "../../test_main.h"
#define N 8

TEST(end_method, big_data_1) {
  s21::Deque<BigData<256>> d1{};

  EXPECT_EQ(d1.Begin() == d1.End(), 1);
}

TEST(end_method, big_data_2) {
  s21::Deque<BigData<256>> d1{1, 2};

  auto itB = d1.Begin();
  ++itB;
  ++itB;

  auto itE = d1.End();

  EXPECT_EQ((itB == itE), 1);
}