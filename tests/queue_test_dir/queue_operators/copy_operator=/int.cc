#include "../../test_main.h"

TEST(copy_assignment_operator_integer, integer_1) {
  s21::Queue<int> d1;
  s21::Queue<int> d2{5};
  d2 = d1;
  EXPECT_EQ(d2.Empty(), 1);
}

TEST(copy_assignment_operator_integer, integer_2) {
  s21::Queue<int> d1{1, 2, 3, 4, 5};
  s21::Queue<int> d2{5};
  d2 = d1;
  
  int j = 5;

  while (d2.Size()) {
    EXPECT_EQ(d2.Top(), j);
    d2.Pop();
    --j;
  }
}

TEST(copy_assignment_operator_integer, integer_3) {
  s21::Queue<int> d1{1, 2, 3, 4, 5};
  s21::Queue<int> d2;
  d2 = d1;

  int j = 5;

  while (d2.Size()) {
    EXPECT_EQ(d2.Top(), j);
    d2.Pop();
    --j;
  }
}

TEST(copy_assignment_operator_integer, integer_4) {
  s21::Queue<int> d1;
  s21::Queue<int> d2;
  d2 = d1;

  EXPECT_EQ(d2.Empty(), 1);
}