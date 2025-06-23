#include "../../utils/BigData.h"
#include "../../test_main.h"
#define N 8

TEST(pop_back_method, big_data_1) {
  s21::Stack<BigData<256>> d1{1, 2, 3};

  d1.Pop();

  EXPECT_EQ(d1.Size(), 2);
  EXPECT_EQ((d1.Top()).ValueProof(2), 1);
}

TEST(pop_back_method, big_data_2) {
  s21::Stack<BigData<256>> d1{1, 2, 3};

  d1.Pop();
  d1.Pop();

  EXPECT_EQ(d1.Size(), 1);

  EXPECT_EQ((d1.Top()).ValueProof(1), 1);
}