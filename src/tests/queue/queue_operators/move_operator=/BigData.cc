#include "../../utils/BigData.h"

#include "../../test_main.h"

TEST(move_assignment_operator_big_data, big_data_1) {
  s21::Queue<BigData<256>> d1;
  s21::Queue<BigData<256>> d2{5};
  d2 = std::move(d1);
  EXPECT_EQ(d2.Empty(), 1);
}

TEST(move_assignment_operator_big_data, big_data_2) {
  s21::Queue<BigData<256>> d1{1, 2, 3, 4, 5};
  s21::Queue<BigData<256>> d2{5};
  d2 = std::move(d1);

  int j = 1;

  size_t bd_deque_size = 0;

  while (d2.Size()) {
    bd_deque_size += (d2.Front()).Size();

    EXPECT_EQ((d2.Front()).ValueProof(j), 1);

    d2.Pop();
    ++j;
  }
  EXPECT_EQ(bd_deque_size, 5 * 256);
}

TEST(move_assignment_operator_big_data, big_data_3) {
  s21::Queue<BigData<256>> d1{1, 2, 3, 4, 5};
  s21::Queue<BigData<256>> d2;
  d2 = std::move(d1);
  int j = 1;

  size_t bd_deque_size = 0;

  while (d2.Size()) {
    bd_deque_size += (d2.Front()).Size();

    EXPECT_EQ((d2.Front()).ValueProof(j), 1);

    d2.Pop();
    ++j;
  }
  EXPECT_EQ(bd_deque_size, 5 * 256);
}

TEST(move_assignment_operator_big_data, big_data_4) {
  s21::Queue<BigData<256>> d1;
  s21::Queue<BigData<256>> d2;
  d2 = std::move(d1);

  EXPECT_EQ(d2.Empty(), 1);
}