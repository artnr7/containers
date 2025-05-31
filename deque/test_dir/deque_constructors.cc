#include "test_main.h"

/* Q: Почему при вызове отрицательного значения число как-будто больше?
A: Потому что происходит неявное преобразование отрицательного в положительное,
2 в степени кол-ва битов занимаего типом(size_t) (2^64 = 18446744073709551616 - 1 18
квинтиллионов!)
*/

/*---------→ DEFAULT ←---------------*/
/*----→ INTEGER ←-------*/
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
  EXPECT_EQ(d1.Begin() == d1.End(), 1);
}

TEST(constructors, default_constructor_4) {
  EXPECT_DEATH(s21::Deque<int> d1(-2),
               "To use this constructor Tp_qty must be less than MaxSize()");
}

/*---------→ VALUE ←---------------*/
TEST(constructors, value_constructor_1) {
  s21::Deque<int> d1(5, 2);
  EXPECT_EQ(d1.Size(), 5);
  auto itE = d1.End();
  for (auto itB = d1.Begin(); itB != itE; ++itB) {
    EXPECT_EQ(*itB, 2);
  }
}

TEST(constructors, value_constructor_2) {
  EXPECT_DEATH(s21::Deque<int> d1(0, 2),
               "To use this constructor Tp_qty must be greater than 0");
}

TEST(constructors, value_constructor_3) {
  EXPECT_DEATH(s21::Deque<int> d1(-1, 2),
               "To use this constructor Tp_qty must be less than MaxSize()");
}

TEST(constructors, value_constructor_4) {
  EXPECT_DEATH(s21::Deque<int> d1(-2, 2),
               "To use this constructor Tp_qty must be less than MaxSize()");
}

TEST(constructors, value_constructor_5) {
  EXPECT_DEATH(s21::Deque<int> d1(-2222, 2),
               "To use this constructor Tp_qty must be less than MaxSize()");
}