#include "../../test_main.h"
#define N 32

TEST(back_method, long_double_1) {
  s21::Stack<long double> d1{1.655345, 2, 3.43543};

  EXPECT_FLOAT_EQ(d1.Back(), 3.43543);
}

TEST(back_method, long_double_2) {
  s21::Stack<long double> d1{1, 2, 3};
  d1.PushBack(5.645645);
  EXPECT_FLOAT_EQ(d1.Back(), 5.645645);
}