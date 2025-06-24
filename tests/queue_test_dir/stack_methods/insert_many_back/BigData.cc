#include "../../utils/BigData.h"
#include "../../test_main.h"
#define N 8

TEST(insert_many_back_method, big_data_1) {
  s21::Queue<BigData<256>> d1{};
  d1.InsertManyBack(1, 2, 3);

  int j = 3;

  size_t bd_deque_size = 0;

  while (d1.Size()) {
    bd_deque_size += (d1.Top()).Size();

    EXPECT_EQ((d1.Top()).ValueProof(j), 1);

    d1.Pop();
    --j;
  }
  EXPECT_EQ(bd_deque_size, 3 * 256);
}

TEST(insert_many_back_method, big_data_2) {
  s21::Queue<BigData<256>> d1{1, 2, 3};
  d1.InsertManyBack(4, 5, 6);

  int j = 6;

  size_t bd_deque_size = 0;

  while (d1.Size()) {
    bd_deque_size += (d1.Top()).Size();

    EXPECT_EQ((d1.Top()).ValueProof(j), 1);

    d1.Pop();
    --j;
  }
  EXPECT_EQ(bd_deque_size, 6 * 256);
}