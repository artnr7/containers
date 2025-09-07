#include "../../test_main.h"

TEST(end_method, int_1) {
  s21::Deque<int> d1{};

  EXPECT_EQ(d1.Begin() == d1.End(), 1);
}

TEST(end_method, int_2) {
  s21::Deque<int> d1{1, 2};

  auto itB = d1.Begin();
  ++itB;
  ++itB;

  auto itE = d1.End();

  EXPECT_EQ((itB == itE), 1);
}