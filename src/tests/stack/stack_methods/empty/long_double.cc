#include "../../test_main.h"
#define N 32

TEST(empty_method, long_double_1) {
  s21::Stack<long double> d1{};
  EXPECT_EQ(d1.Empty(), 1);
}

TEST(empty_method, long_double_2) {
  s21::Stack<long double> d1{};
  d1.Push(1);
  EXPECT_EQ(d1.Empty(), 0);
}

TEST(empty_method, long_double_3) {
  s21::Stack<long double> d1{};
  d1.Push(1);
  EXPECT_EQ(d1.Empty(), 0);
}

TEST(empty_method, long_double_4) {
  s21::Stack<long double> d1{
      1.159,     2.2610,    3.3711,    4.4812,    5.5913,    6.61014,
      7.71115,   8.81216,   9.91317,   10.101418, 11.111519, 12.121620,
      13.131721, 14.141822, 15.151923, 16.162024, 17.172125, 18.182226,
      19.192327, 20.202428, 21.212529, 22.222630, 23.232731, 24.242832,
      25.252933, 26.263034, 27.273135, 28.283236, 29.293337, 30.303438,
      31.313539, 32.323640};

  for (int i = 33; i < N * 32 + 1; ++i) {
    d1.Push(i);
  }

  EXPECT_EQ(d1.Empty(), 0);
}

TEST(empty_method, long_double_5) {
  s21::Stack<long double> d1{
      1.159,     2.2610,    3.3711,    4.4812,    5.5913,    6.61014,
      7.71115,   8.81216,   9.91317,   10.101418, 11.111519, 12.121620,
      13.131721, 14.141822, 15.151923, 16.162024, 17.172125, 18.182226,
      19.192327, 20.202428, 21.212529, 22.222630, 23.232731, 24.242832,
      25.252933, 26.263034, 27.273135, 28.283236, 29.293337, 30.303438,
      31.313539, 32.323640};

  for (int i = 0; i < N; ++i) {
    d1.Pop();
  }

  EXPECT_EQ(d1.Empty(), 1);
}