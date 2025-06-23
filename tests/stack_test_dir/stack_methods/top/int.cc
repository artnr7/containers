#include "../../test_main.h"

TEST(back_method, int_1) {
  s21::Stack<int> d1{1, 2, 3};

  EXPECT_EQ(d1.Back(), 3);
}

TEST(back_method, int_2) {
  s21::Stack<int> d1{1, 2, 3};
  d1.PushBack(5);
  EXPECT_EQ(d1.Back(), 5);
}