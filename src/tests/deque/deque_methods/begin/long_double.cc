#include "../../test_main.h"
#define N 32

TEST(begin_method, long_double_1) {
  s21::Deque<long double> d1{};

  EXPECT_EQ(d1.Begin() == d1.End(), 1);
}

TEST(begin_method, long_double_2) {
  s21::Deque<long double> d1{1.42343242234, 2.4234324324};

  auto itB = d1.Begin();
  ++itB;
  ++itB;

  auto itE = d1.End();

  EXPECT_EQ((itB == itE), 1);
}