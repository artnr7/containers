#include <gtest/gtest.h>

#include "./../s21_array.h"

// TODO(root): Add test cases for array

TEST(ArrayTest, DefaultConstructor) {
  s21::array<int, 3> arr;
  EXPECT_EQ(arr.size(), 3);
  EXPECT_EQ(arr[0], 0);
}

TEST(ArrayTest, InitializerListConstructor) {
  s21::array<int, 3> arr{1, 2, 3};
  EXPECT_EQ(arr[0], 1);
  EXPECT_EQ(arr[1], 2);
  EXPECT_EQ(arr[2], 3);
}

TEST(ArrayTest, AtMethodValid) {
  s21::array<int, 2> arr{10, 20};
  EXPECT_EQ(arr.at(0), 10);
  EXPECT_EQ(arr.at(1), 20);
}

TEST(ArrayTest, AtMethodThrows) {
  s21::array<int, 2> arr{10, 20};
  EXPECT_THROW(arr.at(2), std::out_of_range);
}

TEST(ArrayTest, ConstAtMethodValid) {
  const s21::array<int, 2> arr{10, 20};
  EXPECT_EQ(arr.at(0), 10);
  EXPECT_EQ(arr.at(1), 20);
}

TEST(ArrayTest, ConstAtMethodThrows) {
  const s21::array<int, 2> arr{10, 20};
  EXPECT_THROW(arr.at(2), std::out_of_range);
}

TEST(ArrayTest, OperatorSquareBrackets) {
  s21::array<int, 2> arr{5, 6};
  EXPECT_EQ(arr[0], 5);
  EXPECT_EQ(arr[1], 6);
}

TEST(ArrayTest, ConstOperatorSquareBrackets) {
  const s21::array<int, 2> arr{5, 6};
  EXPECT_EQ(arr[0], 5);
  EXPECT_EQ(arr[1], 6);
}

TEST(ArrayTest, FrontAndBack) {
  s21::array<int, 3> arr{9, 8, 7};
  EXPECT_EQ(arr.front(), 9);
  EXPECT_EQ(arr.back(), 7);
}

TEST(ArrayTest, ConstFrontAndBack) {
  const s21::array<int, 3> arr{9, 8, 7};
  EXPECT_EQ(arr.front(), 9);
  EXPECT_EQ(arr.back(), 7);
}

TEST(ArrayTest, DataTest) {
  s21::array<int, 3> arr{9, 8, 7};
  EXPECT_EQ(arr.data()[0], 9);
}

TEST(ArrayTest, ConstDataTest) {
  const s21::array<int, 3> arr{9, 8, 7};
  EXPECT_EQ(arr.data()[0], 9);
}

TEST(ArrayTest, FillMethod) {
  s21::array<int, 4> arr;
  arr.fill(42);
  for (int i = 0; i < 4; ++i) {
    EXPECT_EQ(arr[i], 42);
  }
}

TEST(ArrayTest, SwapMethod) {
  s21::array<int, 2> a{1, 2};
  s21::array<int, 2> b{3, 4};
  a.swap(b);
  EXPECT_EQ(a[0], 3);
  EXPECT_EQ(a[1], 4);
  EXPECT_EQ(b[0], 1);
  EXPECT_EQ(b[1], 2);
}

TEST(ArrayTest, MoveAssignment) {
  s21::array<int, 3> a{1, 2, 3};
  s21::array<int, 3> b;
  b = std::move(a);
  EXPECT_EQ(b[0], 1);
  EXPECT_EQ(b[1], 2);
  EXPECT_EQ(b[2], 3);
}

TEST(ArrayTest, Iterators) {
  s21::array<int, 3> arr{10, 20, 30};
  auto it = arr.begin();
  EXPECT_EQ(*it, 10);
  ++it;
  EXPECT_EQ(*it, 20);
  ++it;
  EXPECT_EQ(*it, 30);
  ++it;
  EXPECT_EQ(it, arr.end());
}

TEST(ArrayTest, ConstIterators) {
  const s21::array<int, 3> arr{10, 20, 30};
  auto it = arr.begin();
  EXPECT_EQ(*it, 10);
  ++it;
  EXPECT_EQ(*it, 20);
  ++it;
  EXPECT_EQ(*it, 30);
  ++it;
  EXPECT_EQ(it, arr.end());
}

TEST(ArrayTest, MaxSize) {
  s21::array<int, 3> arr{10, 20, 30};
  EXPECT_EQ(arr.max_size(), 3);
}

TEST(ArrayTest, ConstMaxSize) {
  const s21::array<int, 3> arr{10, 20, 30};
  EXPECT_EQ(arr.max_size(), 3);
}

TEST(ArrayTest, ConstSize) {
  const s21::array<int, 3> arr{10, 20, 30};
  EXPECT_EQ(arr.size(), 3);
}

TEST(ArrayTest, Empty) {
  s21::array<int, 3> arr{10, 20, 30};
  EXPECT_FALSE(arr.empty());
}

TEST(ArrayTest, ConstEmpty) {
  const s21::array<int, 3> arr{10, 20, 30};
  EXPECT_FALSE(arr.empty());
}