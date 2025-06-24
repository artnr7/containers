#include "../../test_main.h"
#define N 32

TEST(front_method, long_double_1) {
  s21::Queue<long double> d1{1.655345, 2, 3.43543};

  EXPECT_FLOAT_EQ(d1.Front(), 3.43543);
}

TEST(front_method, long_double_2) {
  s21::Queue<long double> d1{1, 2, 3};
  d1.Push(5.645645);
  EXPECT_FLOAT_EQ(d1.Front(), 5.645645);
}