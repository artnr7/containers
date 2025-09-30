#include <gtest/gtest.h>

#include "base_containers/s21_array.h"

TEST(ArrayTest, DefaultConstructor) {
  s21::Array<int, 3> arr;
  EXPECT_EQ(arr.Size(), 3);
  EXPECT_EQ(arr[0], 0);
}

TEST(ArrayTest, CopyConstructor) {
  s21::Array<int, 3> original = {1, 2, 3};
  s21::Array<int, 3> copy(original);

  EXPECT_EQ(copy[0], 1);
  EXPECT_EQ(copy[1], 2);
  EXPECT_EQ(copy[2], 3);

  EXPECT_EQ(original[0], 1);
  EXPECT_EQ(original[1], 2);
  EXPECT_EQ(original[2], 3);

  copy[0] = 100;
  EXPECT_EQ(original[0], 1);
  EXPECT_EQ(copy[0], 100);
}

TEST(ArrayTest, MoveConstructor) {
  s21::Array<int, 4> original = {10, 20, 30, 40};
  s21::Array<int, 4> moved(std::move(original));

  EXPECT_EQ(moved[0], 10);
  EXPECT_EQ(moved[1], 20);
  EXPECT_EQ(moved[2], 30);
  EXPECT_EQ(moved[3], 40);
}

TEST(ArrayTest, InitializerListConstructor) {
  s21::Array<int, 3> arr{1, 2, 3};
  EXPECT_EQ(arr[0], 1);
  EXPECT_EQ(arr[1], 2);
  EXPECT_EQ(arr[2], 3);
}

TEST(ArrayTest, AtMethodValid) {
  s21::Array<int, 2> arr{10, 20};
  EXPECT_EQ(arr.At(0), 10);
  EXPECT_EQ(arr.At(1), 20);
}

TEST(ArrayTest, AtMethodThrows) {
  s21::Array<int, 2> arr{10, 20};
  EXPECT_THROW(arr.At(2), std::out_of_range);
}

TEST(ArrayTest, ConstAtMethodValid) {
  const s21::Array<int, 2> arr{10, 20};
  EXPECT_EQ(arr.At(0), 10);
  EXPECT_EQ(arr.At(1), 20);
}

TEST(ArrayTest, ConstAtMethodThrows) {
  const s21::Array<int, 2> arr{10, 20};
  EXPECT_THROW(arr.At(2), std::out_of_range);
}

TEST(ArrayTest, OperatorSquareBrackets) {
  s21::Array<int, 2> arr{5, 6};
  EXPECT_EQ(arr[0], 5);
  EXPECT_EQ(arr[1], 6);
}

TEST(ArrayTest, ConstOperatorSquareBrackets) {
  const s21::Array<int, 2> arr{5, 6};
  EXPECT_EQ(arr[0], 5);
  EXPECT_EQ(arr[1], 6);
}

TEST(ArrayTest, FrontAndBack) {
  s21::Array<int, 3> arr{9, 8, 7};
  EXPECT_EQ(arr.Front(), 9);
  EXPECT_EQ(arr.Back(), 7);
}

TEST(ArrayTest, ConstFrontAndBack) {
  const s21::Array<int, 3> arr{9, 8, 7};
  EXPECT_EQ(arr.Front(), 9);
  EXPECT_EQ(arr.Back(), 7);
}

TEST(ArrayTest, DataTest) {
  s21::Array<int, 3> arr{9, 8, 7};
  EXPECT_EQ(arr.Data()[0], 9);
}

TEST(ArrayTest, ConstDataTest) {
  const s21::Array<int, 3> arr{9, 8, 7};
  EXPECT_EQ(arr.Data()[0], 9);
}

TEST(ArrayTest, FillMethod) {
  s21::Array<int, 4> arr;
  arr.Fill(42);
  for (int i = 0; i < 4; ++i) {
    EXPECT_EQ(arr[i], 42);
  }
}

TEST(ArrayTest, SwapMethod) {
  s21::Array<int, 2> a{1, 2};
  s21::Array<int, 2> b{3, 4};
  a.Swap(b);
  EXPECT_EQ(a[0], 3);
  EXPECT_EQ(a[1], 4);
  EXPECT_EQ(b[0], 1);
  EXPECT_EQ(b[1], 2);
}

TEST(ArrayTest, MoveAssignment) {
  s21::Array<int, 3> a{1, 2, 3};
  s21::Array<int, 3> b;
  b = std::move(a);
  EXPECT_EQ(b[0], 1);
  EXPECT_EQ(b[1], 2);
  EXPECT_EQ(b[2], 3);
}

TEST(ArrayTest, Iterators) {
  s21::Array<int, 3> arr{10, 20, 30};
  auto it = arr.Begin();
  EXPECT_EQ(*it, 10);
  ++it;
  EXPECT_EQ(*it, 20);
  ++it;
  EXPECT_EQ(*it, 30);
  ++it;
  EXPECT_EQ(it, arr.End());
}

TEST(ArrayTest, MaxSize) {
  s21::Array<int, 3> arr{10, 20, 30};
  EXPECT_EQ(arr.MaxSize(), 3);
}

TEST(ArrayTest, ConstMaxSize) {
  const s21::Array<int, 3> arr{10, 20, 30};
  EXPECT_EQ(arr.MaxSize(), 3);
}

TEST(ArrayTest, ConstSize) {
  const s21::Array<int, 3> arr{10, 20, 30};
  EXPECT_EQ(arr.Size(), 3);
}

TEST(ArrayTest, Empty) {
  s21::Array<int, 3> arr{10, 20, 30};
  EXPECT_FALSE(arr.Empty());
}

TEST(ArrayTest, ConstEmpty) {
  const s21::Array<int, 3> arr{10, 20, 30};
  EXPECT_FALSE(arr.Empty());
}

TEST(ArrayIteratorTest, DereferenceOperator) {
  s21::Array<int, 3> arr = {10, 20, 30};
  auto it = arr.Begin();
  EXPECT_EQ(*it, 10);
}

TEST(ArrayIteratorTest, IncrementOperators) {
  s21::Array<int, 3> arr = {1, 2, 3};
  auto it = arr.Begin();

  ++it;
  EXPECT_EQ(*it, 2);

  it++;
  EXPECT_EQ(*it, 3);
}

TEST(ArrayIteratorTest, DecrementOperators) {
  s21::Array<int, 3> arr = {5, 6, 7};
  auto it = arr.End();
  --it;
  EXPECT_EQ(*it, 7);

  it--;
  EXPECT_EQ(*it, 6);
}

TEST(ArrayIteratorTest, EqualityOperators) {
  s21::Array<int, 2> arr = {100, 200};
  auto it1 = arr.Begin();
  auto it2 = arr.Begin();
  auto it3 = arr.Begin() + 1;

  EXPECT_TRUE(it1 == it2);
  EXPECT_FALSE(it1 == it3);
  EXPECT_TRUE(it1 != it3);
}

TEST(ArrayIteratorTest, SubscriptOperator) {
  s21::Array<int, 3> arr = {3, 6, 9};
  auto it = arr.Begin();
  EXPECT_EQ(it[0], 3);
  EXPECT_EQ(it[1], 6);
  EXPECT_EQ(it[2], 9);
}

TEST(ArrayIteratorTest, ArithmeticOperators) {
  s21::Array<int, 5> arr = {1, 2, 3, 4, 5};
  auto it = arr.Begin();
  auto it2 = it + 3;
  EXPECT_EQ(*it2, 4);

  auto it3 = it2 - 2;
  EXPECT_EQ(*it3, 2);

  EXPECT_EQ(it3 - it, 1);
}

TEST(ArrayIteratorTest, RelationalOperators) {
  s21::Array<int, 3> arr = {1, 2, 3};
  auto it1 = arr.Begin();
  auto it2 = arr.Begin() + 2;

  EXPECT_TRUE(it2 > it1);
  EXPECT_TRUE(it1 < it2);
  EXPECT_TRUE(it2 >= it1);
  EXPECT_TRUE(it1 <= it2);
  EXPECT_TRUE(it1 <= it1);
  EXPECT_TRUE(it1 >= it1);
}

TEST(ArrayConstIteratorTest, DereferenceOperator) {
  const s21::Array<int, 3> arr = {10, 20, 30};
  auto it = arr.Cbegin();
  EXPECT_EQ(*it, 10);
}

TEST(ArrayConstIteratorTest, EqualityOperators) {
  const s21::Array<int, 2> arr = {100, 200};
  auto it1 = arr.Cbegin();
  auto it2 = arr.Cbegin();
  auto it3 = arr.Cbegin() + 1;

  EXPECT_TRUE(it1 == it2);
  EXPECT_FALSE(it1 == it3);
  EXPECT_TRUE(it1 != it3);
}

TEST(ArrayConstIteratorTest, SubscriptOperator) {
  const s21::Array<int, 3> arr = {3, 6, 9};
  auto it = arr.Cbegin();
  EXPECT_EQ(it[0], 3);
  EXPECT_EQ(it[1], 6);
  EXPECT_EQ(it[2], 9);
}

TEST(ArrayConstIteratorTest, ArithmeticOperators) {
  const s21::Array<int, 5> arr = {1, 2, 3, 4, 5};
  auto it = arr.Cbegin();
  auto it2 = it + 3;
  EXPECT_EQ(*it2, 4);

  auto it3 = it2 - 2;
  EXPECT_EQ(*it3, 2);

  EXPECT_EQ(it3 - it, 1);
}

TEST(ArrayConstIteratorTest, RelationalOperators) {
  const s21::Array<int, 3> arr = {1, 2, 3};
  auto it1 = arr.Cbegin();
  auto it2 = arr.Cbegin() + 2;

  EXPECT_TRUE(it2 > it1);
  EXPECT_TRUE(it1 < it2);
  EXPECT_TRUE(it2 >= it1);
  EXPECT_TRUE(it1 <= it2);
  EXPECT_TRUE(it1 <= it1);
  EXPECT_TRUE(it1 >= it1);
}
