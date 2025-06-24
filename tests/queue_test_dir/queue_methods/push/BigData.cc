#include "../../utils/BigData.h"
#include "../../test_main.h"
#define N 8

/*---------→ COPY ←---------------*/
TEST(operators_push_big_data, empty_copy_1) {
  s21::Queue<BigData<256>> d1;
  for (int i = 1; i < N; ++i) {
    d1.Push(i);
  }

  int j = N - 1;

  size_t bd_deque_size = 0;

  while (d1.Size()) {
    bd_deque_size += (d1.Top()).Size();

    EXPECT_EQ((d1.Top()).ValueProof(j), 1);

    d1.Pop();
    --j;
  }
  EXPECT_EQ(bd_deque_size, (N - 1) * 256);
}

TEST(operators_push_big_data, empty_copy_2) {
  s21::Queue<BigData<256>> d1;
  for (int i = 1; i < N * 3; ++i) {
    d1.Push(i);
  }

  int j = N * 3 - 1;

  size_t bd_deque_size = 0;

  while (d1.Size()) {
    bd_deque_size += (d1.Top()).Size();

    EXPECT_EQ((d1.Top()).ValueProof(j), 1);

    d1.Pop();
    --j;
  }
  EXPECT_EQ(bd_deque_size, (N * 3 - 1) * 256);
}

TEST(operators_push_big_data, filled_copy_1) {
  s21::Queue<BigData<256>> d1{1, 2, 3, 4, 5, 6, 7, 8};

  for (int i = 9; i < N * 2; ++i) {
    d1.Push(i);
  }

  int j = N * 2 - 1;

  size_t bd_deque_size = 0;

  while (d1.Size()) {
    bd_deque_size += (d1.Top()).Size();

    EXPECT_EQ((d1.Top()).ValueProof(j), 1);

    d1.Pop();
    --j;
  }
  EXPECT_EQ(bd_deque_size, (N * 2 - 1) * 256);
}

/*---------→ MOVE ←---------------*/
TEST(operators_push_big_data, empty_move_1) {
  s21::Queue<BigData<256>> d1;
  for (int i = 1; i < N; ++i) {
    d1.Push(std::move(i));
  }

  int j = N - 1;

  size_t bd_deque_size = 0;

  while (d1.Size()) {
    bd_deque_size += (d1.Top()).Size();

    EXPECT_EQ((d1.Top()).ValueProof(j), 1);

    d1.Pop();
    --j;
  }
  EXPECT_EQ(bd_deque_size, (N - 1) * 256);
}

TEST(operators_push_big_data, empty_move_2) {
  s21::Queue<BigData<256>> d1;
  for (int i = 1; i < N * 3; ++i) {
    d1.Push(std::move(i));
  }

  int j = N * 3 - 1;

  size_t bd_deque_size = 0;

  while (d1.Size()) {
    bd_deque_size += (d1.Top()).Size();

    EXPECT_EQ((d1.Top()).ValueProof(j), 1);

    d1.Pop();
    --j;
  }
  EXPECT_EQ(bd_deque_size, (N * 3 - 1) * 256);
}

TEST(operators_push_big_data, filled_move_1) {
  s21::Queue<BigData<256>> d1{1, 2, 3, 4, 5, 6, 7, 8};

  for (int i = 9; i < N * 2; ++i) {
    d1.Push(std::move(i));
  }

  int j = N * 2 - 1;

  size_t bd_deque_size = 0;

  while (d1.Size()) {
    bd_deque_size += (d1.Top()).Size();

    EXPECT_EQ((d1.Top()).ValueProof(j), 1);

    d1.Pop();
    --j;
  }
  EXPECT_EQ(bd_deque_size, (N * 2 - 1) * 256);
}
