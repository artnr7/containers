#include "../../test_main.h"

TEST(pop_front_method, int_1) {
  s21::Deque<int> d1{1, 2, 3};

  d1.PopFront();

  EXPECT_EQ(d1.Size(), 2);
  EXPECT_EQ(d1.Front(), 2);
}

TEST(pop_front_method, int_2) {
  s21::Deque<int> d1{1, 2, 3};

  d1.PopFront();
  d1.PopFront();

  EXPECT_EQ(d1.Size(), 1);
  EXPECT_EQ(d1.Front(), 3);
}