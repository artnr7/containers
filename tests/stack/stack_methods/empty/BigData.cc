#include "../../utils/BigData.h"
#include "../../test_main.h"
#define N 8

TEST(empty_method, big_data_1) {
  s21::Stack<BigData<256>> d1{};
  EXPECT_EQ(d1.Empty(), 1);
}

TEST(empty_method, big_data_2) {
  s21::Stack<BigData<256>> d1{};
  d1.Push(1);
  EXPECT_EQ(d1.Empty(), 0);
}

TEST(empty_method, big_data_3) {
  s21::Stack<BigData<256>> d1{};
  d1.Push(1);
  EXPECT_EQ(d1.Empty(), 0);
}

TEST(empty_method, big_data_4) {
  s21::Stack<BigData<256>> d1{1, 2, 3, 4, 5, 6, 7, 8};

  for (int i = 9; i < N * 2; ++i) {
    d1.Push(i);
  }
  EXPECT_EQ(d1.Empty(), 0);
}

TEST(empty_method, big_data_5) {
  s21::Stack<BigData<256>> d1{1, 2, 3, 4, 5, 6, 7, 8};

  for (int i = 0; i < N; ++i) {
    d1.Pop();
  }

  EXPECT_EQ(d1.Empty(), 1);
}