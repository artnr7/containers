#include "../../test_main.h"

TEST(pop_method, int_1) {
  s21::Stack<int> d1{1, 2, 3};

  d1.Pop();

  EXPECT_EQ(d1.Size(), 2);
  EXPECT_EQ(d1.Top(), 2);
}

TEST(pop_method, int_2) {
  s21::Stack<int> d1{1, 2, 3};

  d1.Pop();
  d1.Pop();

  EXPECT_EQ(d1.Size(), 1);
  EXPECT_EQ(d1.Top(), 1);
}