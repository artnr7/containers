#include "../../test_main.h"

TEST(operators_push_back, push_back_copy_1) {
  s21::Deque<int> d1;
  d1.PushBack(5);
  EXPECT_EQ(*(d1.Begin()), 5);
}
