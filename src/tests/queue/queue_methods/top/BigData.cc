#include "../../utils/BigData.h"
#include "../../test_main.h"
#define N 8

TEST(top_method, big_data_1) {
  s21::Queue<BigData<256>> d1{1, 2, 3};
  EXPECT_EQ((d1.Back()).ValueProof(3), 1);
}

TEST(top_method, big_data_2) {
  s21::Queue<BigData<256>> d1{1, 2, 3};
  d1.Push(5);
  EXPECT_EQ((d1.Back()).ValueProof(5), 1);
}