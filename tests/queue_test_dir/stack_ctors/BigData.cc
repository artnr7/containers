#include "../utils/BigData.h"
#include "../test_main.h"

/*---------→ DEFAULT ←---------------*/
TEST(big_data_constructors, def_constructor_small_size_1) {
  s21::Queue<BigData<256>> d1;
  EXPECT_EQ(d1.Size(), 0);
}

/*---------→ INIT_LIST ←---------------*/
TEST(big_data_constructors, init_list_constructor_1) {
  s21::Queue<BigData<256>> d1{};
  EXPECT_EQ(d1.Size(), 0);
}

TEST(big_data_constructors, init_list_constructor_2) {
  const size_t bd_template_size = BUF_SIZE / 2;

  s21::Queue<BigData<bd_template_size>> d1{1, 2, 3, 4, 5};
  EXPECT_EQ(d1.Size(), 5);
  int j = 5;

  size_t bd_deque_size = 0;
  while (d1.Size()) {
    bd_deque_size += (d1.Top()).Size();
    EXPECT_EQ((d1.Top()).ValueProof(j), 1);
    d1.Pop();
    --j;
  }
  EXPECT_EQ(bd_deque_size, 5 * bd_template_size);
}

TEST(big_data_constructors, init_list_constructor_3) {
  const size_t bd_template_size = BUF_SIZE / 2 - 1;

  s21::Queue<BigData<bd_template_size>> d1{1, 2, 3, 4, 5};
  EXPECT_EQ(d1.Size(), 5);
  int j = 5;

  size_t bd_deque_size = 0;
  while (d1.Size()) {
    bd_deque_size += (d1.Top()).Size();

    EXPECT_EQ((d1.Top()).ValueProof(j), 1);

    d1.Pop();
    --j;
  }
  EXPECT_EQ(bd_deque_size, 5 * bd_template_size);
}

TEST(big_data_constructors, init_list_constructor_4) {
  const size_t bd_template_size = BUF_SIZE / 2 + 1;

  s21::Queue<BigData<bd_template_size>> d1{1, 2, 3, 4, 5};
  EXPECT_EQ(d1.Size(), 5);
  int j = 5;

  size_t bd_deque_size = 0;
  while (d1.Size()) {
    bd_deque_size += (d1.Top()).Size();
    EXPECT_EQ((d1.Top()).ValueProof(j), 1);

    d1.Pop();
    --j;
  }
  EXPECT_EQ(bd_deque_size, 5 * bd_template_size);
}

TEST(big_data_constructors, init_list_constructor_5) {
  const size_t bd_template_size = BUF_SIZE;

  s21::Queue<BigData<bd_template_size>> d1{1, 2, 3, 4, 5};
  EXPECT_EQ(d1.Size(), 5);
  int j = 5;

  size_t bd_deque_size = 0;
  while (d1.Size()) {
    bd_deque_size += (d1.Top()).Size();

    EXPECT_EQ((d1.Top()).ValueProof(j), 1);

    d1.Pop();
    --j;
  }
  EXPECT_EQ(bd_deque_size, 5 * bd_template_size);
}

TEST(big_data_constructors, init_list_constructor_6) {
  const size_t bd_template_size = BUF_SIZE - 1;

  s21::Queue<BigData<bd_template_size>> d1{1, 2, 3, 4, 5};
  EXPECT_EQ(d1.Size(), 5);
  int j = 5;

  size_t bd_deque_size = 0;
  while (d1.Size()) {
    bd_deque_size += (d1.Top()).Size();

    EXPECT_EQ((d1.Top()).ValueProof(j), 1);

    d1.Pop();
    --j;
  }
  EXPECT_EQ(bd_deque_size, 5 * bd_template_size);
}

TEST(big_data_constructors, init_list_constructor_7) {
  const size_t bd_template_size = BUF_SIZE + 1;

  s21::Queue<BigData<bd_template_size>> d1{1, 2, 3, 4, 5};
  EXPECT_EQ(d1.Size(), 5);

  int j = 5;

  size_t bd_deque_size = 0;
  while (d1.Size()) {
    bd_deque_size += (d1.Top()).Size();

    EXPECT_EQ((d1.Top()).ValueProof(j), 1);

    d1.Pop();
    --j;
  }
  EXPECT_EQ(bd_deque_size, 5 * bd_template_size);
}

/*---------→ COPY ←---------------*/
TEST(big_data_constructors, copy_1) {
  s21::Queue<BigData<256>> d1{};
  s21::Queue<BigData<256>> d2(d1);

  EXPECT_EQ(d2.Size(), 0);
}

TEST(big_data_constructors, copy_2) {
  s21::Queue<BigData<256>> d1{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  s21::Queue<BigData<256>> d2(d1);

  EXPECT_EQ(d2.Size(), 10);

  int j = 10;

  size_t bd_deque_size = 0;

  while (d2.Size()) {
    bd_deque_size += (d2.Top()).Size();

    EXPECT_EQ((d2.Top()).ValueProof(j), 1);

    d2.Pop();
    --j;
  }
  EXPECT_EQ(bd_deque_size, 10 * 256);
}

/*---------→ MOVE ←---------------*/
TEST(big_data_constructors, move_1) {
  s21::Queue<BigData<256>> d1{};
  s21::Queue<BigData<256>> d2(std::move(d1));

  EXPECT_EQ(d2.Size(), 0);
}

TEST(big_data_constructors, move_2) {
  s21::Queue<BigData<256>> d1{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  s21::Queue<BigData<256>> d2(std::move(d1));

  EXPECT_EQ(d2.Size(), 10);

  int j = 10;

  size_t bd_deque_size = 0;

  while (d2.Size()) {
    bd_deque_size += (d2.Top()).Size();

    EXPECT_EQ((d2.Top()).ValueProof(j), 1);

    d2.Pop();
    --j;
  }
  EXPECT_EQ(bd_deque_size, 10 * 256);
}
