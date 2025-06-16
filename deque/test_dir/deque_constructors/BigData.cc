#include "../utils/BigData.h"
#include "../test_main.h"

/*---------→ DEFAULT ←---------------*/
TEST(big_data_constructors, def_constructor_normal_size_1) {
  const int deq_size = 5;
  const size_t bd_template_size = BUF_SIZE / 2 - 1;

  s21::Deque<BigData<bd_template_size>> d1(deq_size);
  EXPECT_EQ(d1.Size(), deq_size);
  size_t bd_deque_size = 0;
  for (auto itB = d1.Begin(); itB != d1.End(); ++itB) {
    bd_deque_size += (*itB).Size();
  }
  EXPECT_EQ(bd_deque_size, deq_size * bd_template_size);
}
TEST(big_data_constructors, def_constructor_normal_size_2) {
  const int deq_size = 5;
  const size_t bd_template_size = BUF_SIZE / 2;

  s21::Deque<BigData<bd_template_size>> d1(deq_size);
  EXPECT_EQ(d1.Size(), deq_size);
  size_t bd_deque_size = 0;
  for (auto itB = d1.Begin(); itB != d1.End(); ++itB) {
    bd_deque_size += (*itB).Size();
  }
  EXPECT_EQ(bd_deque_size, deq_size * bd_template_size);
}
TEST(big_data_constructors, def_constructor_normal_size_3) {
  const int deq_size = 5;
  const size_t bd_template_size = BUF_SIZE / 2 + 1;

  s21::Deque<BigData<bd_template_size>> d1(deq_size);
  EXPECT_EQ(d1.Size(), deq_size);
  size_t bd_deque_size = 0;
  for (auto itB = d1.Begin(); itB != d1.End(); ++itB) {
    bd_deque_size += (*itB).Size();
  }
  EXPECT_EQ(bd_deque_size, deq_size * bd_template_size);
}

TEST(big_data_constructors, def_constructor_normal_size_4) {
  const int deq_size = 5;
  const size_t bd_template_size = BUF_SIZE;

  s21::Deque<BigData<bd_template_size>> d1(deq_size);
  EXPECT_EQ(d1.Size(), deq_size);
  size_t bd_deque_size = 0;
  for (auto itB = d1.Begin(); itB != d1.End(); ++itB) {
    bd_deque_size += (*itB).Size();
  }
  EXPECT_EQ(bd_deque_size, deq_size * bd_template_size);
}
TEST(big_data_constructors, def_constructor_normal_size_5) {
  const int deq_size = 5;
  const size_t bd_template_size = BUF_SIZE - 1;

  s21::Deque<BigData<bd_template_size>> d1(deq_size);
  EXPECT_EQ(d1.Size(), deq_size);
  size_t bd_deque_size = 0;
  for (auto itB = d1.Begin(); itB != d1.End(); ++itB) {
    bd_deque_size += (*itB).Size();
  }
  EXPECT_EQ(bd_deque_size, deq_size * bd_template_size);
}
TEST(big_data_constructors, def_constructor_normal_size_6) {
  const int deq_size = 5;
  const size_t bd_template_size = BUF_SIZE + 1;

  s21::Deque<BigData<bd_template_size>> d1(deq_size);
  EXPECT_EQ(d1.Size(), deq_size);
  size_t bd_deque_size = 0;
  for (auto itB = d1.Begin(); itB != d1.End(); ++itB) {
    bd_deque_size += (*itB).Size();
  }
  EXPECT_EQ(bd_deque_size, deq_size * bd_template_size);
}

TEST(big_data_constructors, def_constructor_small_size_1) {
  s21::Deque<BigData<256>> d1(0);
  EXPECT_EQ(d1.Size(), 0);
  EXPECT_EQ(d1.Begin() == d1.End(), 1);
}

TEST(big_data_constructors, def_constructor_small_size_2) {
  s21::Deque<BigData<256>> d1;
  EXPECT_EQ(d1.Size(), 0);
  EXPECT_EQ(d1.Begin() == d1.End(), 1);
}

TEST(big_data_constructors, def_constructor_big_size_1) {

  s21::Deque<BigData<256>> test;
  size_t deq_max_size = test.MaxSize();
  EXPECT_DEATH(s21::Deque<BigData<256>> d1(deq_max_size + 1),
               "To use this constructor Tp_qty must be less than MaxSize()");
}

TEST(big_data_constructors, def_constructor_big_size_2) {
  s21::Deque<BigData<256>> test;
  size_t deq_max_size = test.MaxSize();
  EXPECT_DEATH(s21::Deque<BigData<256>> d1(deq_max_size),
               "std::bad_array_new_length");
}

TEST(big_data_constructors, def_constructor_big_size_3) {
  s21::Deque<BigData<256>> test;
  size_t deq_max_size = test.MaxSize();
  EXPECT_DEATH(s21::Deque<BigData<256>> d1(deq_max_size - 1),
               "std::bad_array_new_length");
}

TEST(big_data_constructors, def_constructor_negative_size_1) {

  EXPECT_DEATH(s21::Deque<BigData<256>> d1(-2),
               "To use this constructor Tp_qty must be less than MaxSize()");
}

/*---------→ VALUE ←---------------*/
TEST(big_data_constructors, value_constructor_1) {
  int value = 1;
  s21::Deque<BigData<256>> d1(5, value);
  EXPECT_EQ(d1.Size(), 5);
  for (auto itB = d1.Begin(); itB != d1.End(); ++itB) {
    for (size_t i = 0; i < 256; ++i) {
      EXPECT_EQ((*itB).ValueProof(value), 1);
    }
  }
}

TEST(big_data_constructors, value_constructor_2) {
  EXPECT_DEATH(s21::Deque<BigData<256>> d1(0, 1),
               "To use this constructor Tp_qty must be greater than 0");
}

TEST(big_data_constructors, value_constructor_3) {
  EXPECT_DEATH(s21::Deque<BigData<256>> d1(-1, 2),
               "To use this constructor Tp_qty must be less than MaxSize()");
}

TEST(big_data_constructors, value_constructor_4) {
  EXPECT_DEATH(s21::Deque<BigData<256>> d1(-2, 3),
               "To use this constructor Tp_qty must be less than MaxSize()");
}

TEST(big_data_constructors, value_constructor_5) {
  EXPECT_DEATH(s21::Deque<BigData<256>> d1(-2222, 4),
               "To use this constructor Tp_qty must be less than MaxSize()");
}

/*---------→ INIT_LIST ←---------------*/
TEST(big_data_constructors, init_list_constructor_1) {
  s21::Deque<BigData<256>> d1{};
  EXPECT_EQ(d1.Size(), 0);
  EXPECT_EQ(d1.Begin() == d1.End(), 1);
}

TEST(big_data_constructors, init_list_constructor_2) {
  s21::Deque<BigData<256>> d1{1, 2, 3, 4, 5};
  EXPECT_EQ(d1.Size(), 5);
  int j = 1;

  for (auto itB = d1.Begin(); itB != d1.End(); ++itB, ++j) {
    for (size_t i = 0; i < 256; ++i) {
      EXPECT_EQ((*itB).ValueProof(j), 1);
    }
  }
}
