#include "../../test_main.h"

TEST(pop_back_method, int_1) {
  s21::Deque<int> d1{1, 2, 3};

  d1.PopBack();

  EXPECT_EQ(d1.Size(), 2);
  EXPECT_EQ(d1.Back(), 2);
}

TEST(pop_back_method, int_2) {
  s21::Deque<int> d1{1, 2, 3};

  d1.PopBack();
  d1.PopBack();

  EXPECT_EQ(d1.Size(), 1);
  EXPECT_EQ(d1.Back(), 1);
}