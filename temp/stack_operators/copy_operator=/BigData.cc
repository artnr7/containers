#include "../../utils/BigData.h"
#include "../../test_main.h"

TEST(copy_assignment_operator_big_data, big_data_1) {
  s21::Deque<BigData<256>> d1;
  s21::Deque<BigData<256>> d2{5};
  d2 = d1;
  EXPECT_EQ(d2.Empty(), 1);
}

TEST(copy_assignment_operator_big_data, big_data_2) {
  s21::Deque<BigData<256>> d1{1, 2, 3, 4, 5};
  s21::Deque<BigData<256>> d2{5};
  d2 = d1;
  int i = 1;
  for (auto itB = d2.Begin(); itB != d2.End(); ++itB, ++i) {
    EXPECT_EQ((*itB).ValueProof(i), 1);
  }
}

TEST(copy_assignment_operator_big_data, big_data_3) {
  s21::Deque<BigData<256>> d1{1, 2, 3, 4, 5};
  s21::Deque<BigData<256>> d2;
  d2 = d1;
  int i = 1;
  for (auto itB = d2.Begin(); itB != d2.End(); ++itB, ++i) {
    EXPECT_EQ((*itB).ValueProof(i), 1);
  }
}

TEST(copy_assignment_operator_big_data, big_data_4) {
  s21::Deque<BigData<256>> d1;
  s21::Deque<BigData<256>> d2;
  d2 = d1;

  EXPECT_EQ(d2.Empty(), 1);
}