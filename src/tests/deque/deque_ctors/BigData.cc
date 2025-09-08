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

  size_t bd_deque_size = 0;
  for (auto itB = d1.Begin(); itB != d1.End(); ++itB) {
    bd_deque_size += (*itB).Size();
    EXPECT_EQ((*itB).ValueProof(value), 1);
  }
  EXPECT_EQ(bd_deque_size, 5 * 256);
}

TEST(big_data_constructors, value_constructor_2) {
  int value = 77;
  s21::Deque<BigData<256>> d1(1029, value);
  EXPECT_EQ(d1.Size(), 1029);

  size_t bd_deque_size = 0;
  for (auto itB = d1.Begin(); itB != d1.End(); ++itB) {
    bd_deque_size += (*itB).Size();
    EXPECT_EQ((*itB).ValueProof(value), 1);
  }
  EXPECT_EQ(bd_deque_size, 1029 * 256);
}

TEST(big_data_constructors, value_constructor_3) {
  EXPECT_DEATH(s21::Deque<BigData<256>> d1(0, 1),
               "To use this constructor Tp_qty must be greater than 0");
}

TEST(big_data_constructors, value_constructor_4) {
  EXPECT_DEATH(s21::Deque<BigData<256>> d1(-1, 2),
               "To use this constructor Tp_qty must be less than MaxSize()");
}

TEST(big_data_constructors, value_constructor_5) {
  EXPECT_DEATH(s21::Deque<BigData<256>> d1(-2, 3),
               "To use this constructor Tp_qty must be less than MaxSize()");
}

TEST(big_data_constructors, value_constructor_6) {
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

  size_t bd_deque_size = 0;
  for (auto itB = d1.Begin(); itB != d1.End(); ++itB, ++j) {
    bd_deque_size += (*itB).Size();
    EXPECT_EQ((*itB).ValueProof(j), 1);
  }

  EXPECT_EQ(bd_deque_size, 5 * 256);
}

TEST(big_data_constructors, init_list_constructor_3) {
  s21::Deque<BigData<255>> d1{1, 2, 3, 4, 5};
  EXPECT_EQ(d1.Size(), 5);
  int j = 1;

  size_t bd_deque_size = 0;
  for (auto itB = d1.Begin(); itB != d1.End(); ++itB, ++j) {
    bd_deque_size += (*itB).Size();
    EXPECT_EQ((*itB).ValueProof(j), 1);
  }

  EXPECT_EQ(bd_deque_size, 5 * 255);
}

TEST(big_data_constructors, init_list_constructor_4) {
  s21::Deque<BigData<257>> d1{1, 2, 3, 4, 5};
  EXPECT_EQ(d1.Size(), 5);
  int j = 1;

  size_t bd_deque_size = 0;
  for (auto itB = d1.Begin(); itB != d1.End(); ++itB, ++j) {
    bd_deque_size += (*itB).Size();
    EXPECT_EQ((*itB).ValueProof(j), 1);
  }

  EXPECT_EQ(bd_deque_size, 5 * 257);
}

TEST(big_data_constructors, init_list_constructor_5) {
  s21::Deque<BigData<512>> d1{1, 2, 3, 4, 5};
  EXPECT_EQ(d1.Size(), 5);
  int j = 1;

  size_t bd_deque_size = 0;
  for (auto itB = d1.Begin(); itB != d1.End(); ++itB, ++j) {
    bd_deque_size += (*itB).Size();
    EXPECT_EQ((*itB).ValueProof(j), 1);
  }

  EXPECT_EQ(bd_deque_size, 5 * 512);
}

TEST(big_data_constructors, init_list_constructor_6) {
  s21::Deque<BigData<511>> d1{1, 2, 3, 4, 5};
  EXPECT_EQ(d1.Size(), 5);
  int j = 1;

  size_t bd_deque_size = 0;
  for (auto itB = d1.Begin(); itB != d1.End(); ++itB, ++j) {
    bd_deque_size += (*itB).Size();
    EXPECT_EQ((*itB).ValueProof(j), 1);
  }

  EXPECT_EQ(bd_deque_size, 5 * 511);
}

TEST(big_data_constructors, init_list_constructor_7) {
  s21::Deque<BigData<513>> d1{1, 2, 3, 4, 5};
  EXPECT_EQ(d1.Size(), 5);
  int j = 1;

  size_t bd_deque_size = 0;
  for (auto itB = d1.Begin(); itB != d1.End(); ++itB, ++j) {
    bd_deque_size += (*itB).Size();
    EXPECT_EQ((*itB).ValueProof(j), 1);
  }

  EXPECT_EQ(bd_deque_size, 5 * 513);
}

/*---------→ COPY ←---------------*/
TEST(big_data_constructors, copy_1) {
  s21::Deque<BigData<256>> d1{};
  s21::Deque<BigData<256>> d2(d1);

  EXPECT_EQ(d2.Size(), 0);
  EXPECT_EQ(d2.Begin() == d2.End(), 1);
}

TEST(big_data_constructors, copy_2) {
  s21::Deque<BigData<256>> d1(5, 2);
  s21::Deque<BigData<256>> d2(d1);

  EXPECT_EQ(d2.Size(), 5);

  for (auto itB = d1.Begin(); itB != d1.End(); ++itB) {
    EXPECT_EQ((*itB).ValueProof(2), 1);
  }
}

TEST(big_data_constructors, copy_3) {
  s21::Deque<BigData<256>> d1{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  s21::Deque<BigData<256>> d2(d1);

  EXPECT_EQ(d2.Size(), 10);

  int j = 1;

  for (auto itB = d1.Begin(); itB != d1.End(); ++itB, ++j) {
    EXPECT_EQ((*itB).ValueProof(j), 1);
  }
}

/*---------→ MOVE ←---------------*/
TEST(big_data_constructors, move_1) {
  s21::Deque<BigData<256>> d1{};
  s21::Deque<BigData<256>> d2(std::move(d1));

  EXPECT_EQ(d2.Size(), 0);
  EXPECT_EQ(d2.Begin() == d2.End(), 1);
}

TEST(big_data_constructors, move_2) {
  s21::Deque<BigData<256>> d1(5, 2);
  s21::Deque<BigData<256>> d2(std::move(d1));

  EXPECT_EQ(d2.Size(), 5);

  for (auto itB = d1.Begin(); itB != d1.End(); ++itB) {
    EXPECT_EQ((*itB).ValueProof(2), 1);
  }
}

TEST(big_data_constructors, move_3) {
  s21::Deque<BigData<256>> d1{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  s21::Deque<BigData<256>> d2(std::move(d1));

  EXPECT_EQ(d2.Size(), 10);

  int j = 1;

  for (auto itB = d1.Begin(); itB != d1.End(); ++itB, ++j) {
    EXPECT_EQ((*itB).ValueProof(j), 1);
  }
}