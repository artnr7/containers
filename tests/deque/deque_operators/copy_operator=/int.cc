#include "../../test_main.h"

TEST(copy_assignment_operator_integer, integer_1) {
  s21::Deque<int> d1;
  s21::Deque<int> d2{5};
  d2 = d1;
  EXPECT_EQ(d2.Empty(), 1);
}

TEST(copy_assignment_operator_integer, integer_2) {
  s21::Deque<int> d1{1, 2, 3, 4, 5};
  s21::Deque<int> d2{5};
  d2 = d1;
  int i = 1;
  for (auto itB = d2.Begin(); itB != d2.End(); ++itB, ++i) {
    EXPECT_EQ(*itB, i);
  }
}

TEST(copy_assignment_operator_integer, integer_3) {
  s21::Deque<int> d1{1, 2, 3, 4, 5};
  s21::Deque<int> d2;
  d2 = d1;
  int i = 1;
  for (auto itB = d2.Begin(); itB != d2.End(); ++itB, ++i) {
    EXPECT_EQ(*itB, i);
  }
}

TEST(copy_assignment_operator_integer, integer_4) {
  s21::Deque<int> d1;
  s21::Deque<int> d2;
  d2 = d1;

  EXPECT_EQ(d2.Empty(), 1);
}