#include "../../test_main.h"
#include <deque>
#include <queue>
#define N 32

TEST(move_assignment_operator_long_double, long_double_1) {
  s21::Queue<long double> d1;
  s21::Queue<long double> d2{5.423};
  d2 = std::move(d1);
  EXPECT_EQ(d2.Empty(), 1);
}

TEST(move_assignment_operator_long_double, long_double_2) {
  s21::Queue<long double> d1{1.4324, 2.432634534643, 3.85678456, 4.53455754,
                             5.6343453};
  s21::Queue<long double> d2{5.423};

  std::deque<long double> init_deque{1.4324, 2.432634534643, 3.85678456,
                                     4.53455754, 5.6343453};

  std::queue<long double> d3{init_deque};

  d2 = std::move(d1);

  EXPECT_EQ(d2.Size(), 5);

  while (d2.Size()) {
    EXPECT_FLOAT_EQ(d2.Top(), d3.top());
    d2.Pop();
    d3.pop();
  }
}

TEST(move_assignment_operator_long_double, long_double_3) {
  s21::Queue<long double> d1{1.4324, 2.432634534643, 3.85678456, 4.53455754,
                             5.6343453};
  s21::Queue<long double> d2;

  std::deque<long double> init_deque{1.4324, 2.432634534643, 3.85678456,
                                     4.53455754, 5.6343453};

  std::queue<long double> d3{init_deque};

  d2 = std::move(d1);

  EXPECT_EQ(d2.Size(), 5);

  while (d2.Size()) {
    EXPECT_FLOAT_EQ(d2.Top(), d3.top());
    d2.Pop();
    d3.pop();
  }
}

TEST(move_assignment_operator_long_double, long_double_4) {
  s21::Queue<long double> d1;
  s21::Queue<long double> d2;
  d2 = std::move(d1);

  EXPECT_EQ(d2.Empty(), 1);
}