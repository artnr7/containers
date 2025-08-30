#include "../../test_main.h"
#define N 32

TEST(pop_method, long_double_1) {
  s21::Queue<long double> d1{1.423432, 2.423432, 3.423423};

  d1.Pop();

  EXPECT_EQ(d1.Size(), 2);
  EXPECT_EQ(d1.Front(), 2.423432);
}

TEST(pop_method, long_double_2) {
  s21::Queue<long double> d1{1.534534, 2.534543, 3.534534};

  d1.Pop();
  d1.Pop();

  EXPECT_EQ(d1.Size(), 1);
  EXPECT_EQ(d1.Front(), 3.534534);
}