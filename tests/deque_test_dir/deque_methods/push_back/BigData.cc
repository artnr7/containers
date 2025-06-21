#include "../../utils/BigData.h"
#include "../../test_main.h"
#define N 8

/*---------→ COPY ←---------------*/
TEST(operators_push_back_big_data, empty_copy_1) {
  s21::Deque<BigData<256>> d1;
  for (int i = 1; i < N; ++i) {
    d1.PushBack(i);
  }
  int j = 1;

  for (auto itB = d1.Begin(); itB != d1.End(); ++itB, ++j) {
    for (size_t i = 0; i < 256; ++i) {
      EXPECT_EQ((*itB).ValueProof(j), 1);
    }
  }
}

TEST(operators_push_back_big_data, empty_copy_2) {
  s21::Deque<BigData<256>> d1;
  for (int i = 1; i < N * 3; ++i) {
    d1.PushBack(i);
  }
  int j = 1;

  for (auto itB = d1.Begin(); itB != d1.End(); ++itB, ++j) {
    for (size_t i = 0; i < 256; ++i) {
      EXPECT_EQ((*itB).ValueProof(j), 1);
    }
  }
}

TEST(operators_push_back_big_data, filled_copy_1) {
  s21::Deque<BigData<256>> d1{1, 2, 3, 4, 5, 6, 7, 8};

  for (int i = 9; i < N * 2; ++i) {
    d1.PushBack(i);
  }

  int j = 1;

  for (auto itB = d1.Begin(); itB != d1.End(); ++itB, ++j) {
    for (size_t i = 0; i < 256; ++i) {
      EXPECT_EQ((*itB).ValueProof(j), 1);
    }
  }
}

/*---------→ MOVE ←---------------*/
TEST(operators_push_back_big_data, empty_move_1) {
  s21::Deque<BigData<256>> d1;
  for (int i = 1; i < N; ++i) {
    d1.PushBack(std::move(i));
  }
  int j = 1;

  for (auto itB = d1.Begin(); itB != d1.End(); ++itB, ++j) {
    for (size_t i = 0; i < 256; ++i) {
      EXPECT_EQ((*itB).ValueProof(j), 1);
    }
  }
}

TEST(operators_push_back_big_data, empty_move_2) {
  s21::Deque<BigData<256>> d1;
  for (int i = 1; i < N * 3; ++i) {
    d1.PushBack(std::move(i));
  }
  int j = 1;

  for (auto itB = d1.Begin(); itB != d1.End(); ++itB, ++j) {
    for (size_t i = 0; i < 256; ++i) {
      EXPECT_EQ((*itB).ValueProof(j), 1);
    }
  }
}

TEST(operators_push_back_big_data, filled_move_1) {
  s21::Deque<BigData<256>> d1{1, 2, 3, 4, 5, 6, 7, 8};

  for (int i = 9; i < N * 2; ++i) {
    d1.PushBack(std::move(i));
  }

  int j = 1;

  for (auto itB = d1.Begin(); itB != d1.End(); ++itB, ++j) {
    for (size_t i = 0; i < 256; ++i) {
      EXPECT_EQ((*itB).ValueProof(j), 1);
    }
  }
}
