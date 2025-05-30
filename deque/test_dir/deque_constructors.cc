#include "test_main.h"

TEST(constructors, default_constructor_1) {
  s21::Deque<int> d1(5);
  EXPECT_EQ(d1.Size(), 5);
  auto itE = d1.End();
  for (auto itB = d1.Begin(); itB != itE; ++itB) {
    EXPECT_EQ(*itB, 0);
  }
}

TEST(constructors, default_constructor_2) {
  s21::Deque<int> d1(0);
  EXPECT_EQ(d1.Size(), 0);
  auto itE = d1.End();
  for (auto itB = d1.Begin(); itB != itE; ++itB) {
    EXPECT_EQ(*itB, 0);
  }
}

TEST(constructors, default_constructor_3) {
  s21::Deque<int> d1;
  EXPECT_EQ(d1.Size(), 0);
  auto itE = d1.End();
  for (auto itB = d1.Begin(); itB != itE; ++itB) {
    EXPECT_EQ(*itB, 0);
  }
}

TEST(constructors, value_constructor_1) {
  s21::Deque<int> d1(5, 2);
  EXPECT_EQ(d1.Size(), 5);
  auto itE = d1.End();
  for (auto itB = d1.Begin(); itB != itE; ++itB) {
    EXPECT_EQ(*itB, 2);
  }
}

TEST(constructors, value_constructor_2) {
  EXPECT_THROW(s21::Deque<int> d1(0, 2), std::invalid_argument);
}