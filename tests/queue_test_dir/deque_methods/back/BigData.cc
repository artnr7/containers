#include "../../utils/BigData.h"
#include "../../test_main.h"
#define N 8

TEST(back_method, big_data_1) {
  s21::Deque<BigData<256>> d1{1, 2, 3};

  for (size_t i = 0; i < 256; ++i) {
    EXPECT_EQ((d1.Back()).ValueProof(3), 1);
  }
}

TEST(back_method, big_data_2) {
  s21::Deque<BigData<256>> d1{1, 2, 3};
  d1.PushBack(5);
  for (size_t i = 0; i < 256; ++i) {
    EXPECT_EQ((d1.Back()).ValueProof(5), 1);
  }
}