#include "../../test_main.h"
#include <deque>

TEST(copy_assignment_operator_long_double, long_double_1) {
  s21::Deque<long double> d1;
  s21::Deque<long double> d2{5.423};
  d2 = std::move(d1);
  EXPECT_EQ(d2.Empty(), 1);
}

TEST(copy_assignment_operator_long_double, long_double_2) {
  s21::Deque<long double> d1{1.4324, 2.432634534643, 3.85678456, 4.53455754,
                             5.6343453};
  s21::Deque<long double> d2{5.423};
  std::deque<long double> d3{1.4324, 2.432634534643, 3.85678456, 4.53455754,
                             5.6343453};
  auto d3B = d3.begin();

  d2 = std::move(d1);

  for (auto itB = d2.Begin(); itB != d2.End(); ++itB, ++d3B) {
    EXPECT_FLOAT_EQ(*itB, *d3B);
  }
}

TEST(copy_assignment_operator_long_double, long_double_3) {
  s21::Deque<long double> d1{1.4324, 2.432634534643, 3.85678456, 4.53455754,
                             5.6343453};
  s21::Deque<long double> d2;
  std::deque<long double> d3{1.4324, 2.432634534643, 3.85678456, 4.53455754,
                             5.6343453};
  auto d3B = d3.begin();

  d2 = std::move(d1);

  for (auto itB = d2.Begin(); itB != d2.End(); ++itB, ++d3B) {
    EXPECT_FLOAT_EQ(*itB, *d3B);
  }
}

TEST(copy_assignment_operator_long_double, long_double_4) {
  s21::Deque<long double> d1;
  s21::Deque<long double> d2;
  d2 = std::move(d1);

  EXPECT_EQ(d2.Empty(), 1);
}