#include "../utils/BigData.h"
#include "../test_main.h"

/*---------→ DEFAULT ←---------------*/
TEST(big_data_constructors, def_ctor_normal_size_1) {
  const int deq_size = 5;
  const size_t bd_template_size = BUF_SIZE / 2 - 1;
  s21::Deque<BigData<bd_template_size, char>> d1(deq_size);
  EXPECT_EQ(d1.Size(), deq_size);
  size_t bd_deque_size = 0;
  for (auto itB = d1.Begin(); itB != d1.End(); ++itB) {
    bd_deque_size += (*itB).Size();
  }
  EXPECT_EQ(bd_deque_size, deq_size * bd_template_size);
}
TEST(big_data_constructors, def_ctor_normal_size_2) {
  const int deq_size = 5;
  const size_t bd_template_size = BUF_SIZE / 2;
  s21::Deque<BigData<bd_template_size, char>> d1(deq_size);
  EXPECT_EQ(d1.Size(), deq_size);
  size_t bd_deque_size = 0;
  for (auto itB = d1.Begin(); itB != d1.End(); ++itB) {
    bd_deque_size += (*itB).Size();
  }
  EXPECT_EQ(bd_deque_size, deq_size * bd_template_size);
}
TEST(big_data_constructors, def_ctor_normal_size_3) {
  const int deq_size = 5;
  const size_t bd_template_size = BUF_SIZE / 2 + 1;
  s21::Deque<BigData<bd_template_size, char>> d1(deq_size);
  EXPECT_EQ(d1.Size(), deq_size);
  size_t bd_deque_size = 0;
  for (auto itB = d1.Begin(); itB != d1.End(); ++itB) {
    bd_deque_size += (*itB).Size();
  }
  EXPECT_EQ(bd_deque_size, deq_size * bd_template_size);
}

TEST(big_data_constructors, def_ctor_normal_size_4) {
  const int deq_size = 5;
  const size_t bd_template_size = BUF_SIZE;
  s21::Deque<BigData<bd_template_size, char>> d1(deq_size);
  EXPECT_EQ(d1.Size(), deq_size);
  size_t bd_deque_size = 0;
  for (auto itB = d1.Begin(); itB != d1.End(); ++itB) {
    bd_deque_size += (*itB).Size();
  }
  EXPECT_EQ(bd_deque_size, deq_size * bd_template_size);
}
TEST(big_data_constructors, def_ctor_normal_size_5) {
  const int deq_size = 5;
  const size_t bd_template_size = BUF_SIZE - 1;
  s21::Deque<BigData<bd_template_size, char>> d1(deq_size);
  EXPECT_EQ(d1.Size(), deq_size);
  size_t bd_deque_size = 0;
  for (auto itB = d1.Begin(); itB != d1.End(); ++itB) {
    bd_deque_size += (*itB).Size();
  }
  EXPECT_EQ(bd_deque_size, deq_size * bd_template_size);
}
TEST(big_data_constructors, def_ctor_normal_size_6) {
  const int deq_size = 5;
  const size_t bd_template_size = BUF_SIZE + 1;
  s21::Deque<BigData<bd_template_size, char>> d1(deq_size);
  EXPECT_EQ(d1.Size(), deq_size);
  size_t bd_deque_size = 0;
  for (auto itB = d1.Begin(); itB != d1.End(); ++itB) {
    bd_deque_size += (*itB).Size();
  }
  EXPECT_EQ(bd_deque_size, deq_size * bd_template_size);
}

TEST(big_data_constructors, def_ctor_small_size_1) {
  s21::Deque<BigData<256, char>> d1(0);
  EXPECT_EQ(d1.Size(), 0);
  EXPECT_EQ(d1.Begin() == d1.End(), 1);
}

TEST(big_data_constructors, def_ctor_small_size_2) {
  s21::Deque<BigData<256, char>> d1;
  EXPECT_EQ(d1.Size(), 0);
  EXPECT_EQ(d1.Begin() == d1.End(), 1);
}

TEST(big_data_constructors, def_ctor_big_size_1) {
  using big_data = BigData<256, char>;
  s21::Deque<BigData<256, char>> test;
  size_t deq_max_size = test.MaxSize();
  EXPECT_DEATH(s21::Deque<big_data> d1(deq_max_size + 1),
               "To use this constructor Tp_qty must be less than MaxSize()");
}

TEST(big_data_constructors, def_ctor_big_size_2) {
  using big_data = BigData<256, char>;

  s21::Deque<BigData<256, char>> test;
  size_t deq_max_size = test.MaxSize();
  EXPECT_DEATH(s21::Deque<big_data> d1(deq_max_size),
               "std::bad_array_new_length");
}

TEST(big_data_constructors, def_ctor_big_size_3) {
  using big_data = BigData<256, char>;

  s21::Deque<BigData<256, char>> test;
  size_t deq_max_size = test.MaxSize();
  EXPECT_DEATH(s21::Deque<big_data> d1(deq_max_size - 1),
               "std::bad_array_new_length");
}

TEST(big_data_constructors, def_ctor_negative_size_1) {
  using big_data = BigData<256, char>;

  EXPECT_DEATH(s21::Deque<big_data> d1(-2),
               "To use this constructor Tp_qty must be less than MaxSize()");
}

/*---------→ VALUE ←---------------*/
TEST(big_data_constructors, value_constructor_1) {
  long double value = 2.5345432534523;
  s21::Deque<BigData<256, long double>> d1(5, value);
  EXPECT_EQ(d1.Size(), 5);
  for (auto itB = d1.Begin(); itB != d1.End(); ++itB) {
    for (size_t i = 0; i < 256; ++i) {
      EXPECT_EQ((*itB).ValueProof(value), 1);
    }
  }
}

TEST(big_data_constructors, value_constructor_2) {
  using big_data = BigData<256, long double>;

  EXPECT_DEATH(s21::Deque<big_data> d1(0, 2.534345434357),
               "To use this constructor Tp_qty must be greater than 0");
}

TEST(big_data_constructors, value_constructor_3) {
  using big_data = BigData<256, long double>;
  EXPECT_DEATH(s21::Deque<big_data> d1(-1, 2.8645634),
               "To use this constructor Tp_qty must be less than MaxSize()");
}

TEST(big_data_constructors, value_constructor_4) {
  using big_data = BigData<256, long double>;
  EXPECT_DEATH(s21::Deque<big_data> d1(-2, 2.665745687456346),
               "To use this constructor Tp_qty must be less than MaxSize()");
}

TEST(big_data_constructors, value_constructor_5) {
  using big_data = BigData<256, long double>;
  EXPECT_DEATH(s21::Deque<big_data> d1(-2222, 2.75347456462345645),
               "To use this constructor Tp_qty must be less than MaxSize()");
}

/*---------→ VALUE ←---------------*/
TEST(big_data_constructors, init_list_constructor_1) {
  s21::Deque<BigData<256, char>> d1{};
  EXPECT_EQ(d1.Size(), 0);
  EXPECT_EQ(d1.Begin() == d1.End(), 1);
}
