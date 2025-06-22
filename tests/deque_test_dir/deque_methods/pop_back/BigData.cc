#include "../../utils/BigData.h"
#include "../../test_main.h"
#define N 8

TEST(pop_back_method, big_data_1) {
  s21::Deque<BigData<256>> d1{1, 2, 3};

  d1.PopBack();

  EXPECT_EQ(d1.Size(), 2);
    EXPECT_EQ((d1.Back()).ValueProof(2), 1);
}

TEST(pop_back_method, big_data_2) {
  s21::Deque<BigData<256>> d1{1, 2, 3};

  d1.PopBack();
  d1.PopBack();

  EXPECT_EQ(d1.Size(), 1);

    EXPECT_EQ((d1.Back()).ValueProof(1), 1);
}