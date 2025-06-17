#include "../../utils/BigData.h"
#include "../../test_main.h"
#define N 8

TEST(pop_front_method, big_data_1) {
  s21::Deque<BigData<256>> d1{1, 2, 3};

  d1.PopFront();

  EXPECT_EQ(d1.Size(), 2);

  for (size_t i = 0; i < 256; ++i) {
    EXPECT_EQ((d1.Front()).ValueProof(2), 1);
  }
}

TEST(pop_front_method, big_data_2) {
  s21::Deque<BigData<256>> d1{1, 2, 3};

  d1.PopFront();
  d1.PopFront();

  EXPECT_EQ(d1.Size(), 1);

  for (size_t i = 0; i < 256; ++i) {
    EXPECT_EQ((d1.Front()).ValueProof(3), 1);
  }
}