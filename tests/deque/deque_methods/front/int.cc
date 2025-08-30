#include "../../test_main.h"

TEST(front_method, int_1) {
  s21::Deque<int> d1{1, 2, 3};

  EXPECT_EQ(d1.Front(), 1);
}

TEST(front_method, int_2) {
  s21::Deque<int> d1{1, 2, 3};
  d1.PushFront(5);
  EXPECT_EQ(d1.Front(), 5);
}