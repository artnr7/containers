#include <gtest/gtest.h>

#include <vector>

#include "../include/base_containers/s21_vector.h"

// TODO(root): Add test cases for vector

TEST(vectorTest, DefaultConstructor) {
  s21::Vector<int> victor;
  EXPECT_EQ(victor.Size(), 0);
  EXPECT_EQ(victor.Capacity(), 0);
}

TEST(vectorTest, SizedConstructor) {
  s21::Vector<int> victor(5);
  EXPECT_EQ(victor.Size(), 5);
  EXPECT_EQ(victor.Capacity(), 5);
}

TEST(vectorTest, InitializerListConstructor) {
  s21::Vector<int> victor{1, 2, 3, 4};
  EXPECT_EQ(victor.Size(), 4);
  EXPECT_EQ(victor[0], 1);
  EXPECT_EQ(victor[1], 2);
  EXPECT_EQ(victor[2], 3);
  EXPECT_EQ(victor[3], 4);
}

TEST(vectorTest, CopyConstructor) {
  s21::Vector<int> zictor{1, 2, 3, 4};
  s21::Vector<int> victor(zictor);
  EXPECT_EQ(victor.Size(), 4);
  EXPECT_EQ(victor[0], 1);
  EXPECT_EQ(victor[1], 2);
  EXPECT_EQ(victor[2], 3);
  EXPECT_EQ(victor[3], 4);
}

TEST(vectorTest, MoveConstructor) {
  s21::Vector<int> zictor{1, 2, 3, 4};
  s21::Vector<int> victor(std::move(zictor));
  EXPECT_EQ(victor.Size(), 4);
  EXPECT_EQ(victor[0], 1);
  EXPECT_EQ(victor[1], 2);
  EXPECT_EQ(victor[2], 3);
  EXPECT_EQ(victor[3], 4);
  EXPECT_EQ(zictor.Size(), 0);
  EXPECT_EQ(zictor.Capacity(), 0);
}

TEST(vectorTest, MoveEqConstructor) {
  s21::Vector<int> zictor{1, 2, 3, 4};
  s21::Vector<int> victor;
  victor = std::move(zictor);
  EXPECT_EQ(victor.Size(), 4);
  EXPECT_EQ(victor[0], 1);
  EXPECT_EQ(victor[1], 2);
  EXPECT_EQ(victor[2], 3);
  EXPECT_EQ(victor[3], 4);
  EXPECT_EQ(zictor.Size(), 0);
  EXPECT_EQ(zictor.Capacity(), 0);
}

TEST(vectorTest, AtValidIndex) {
  s21::Vector<int> victor = {10, 20, 30};
  EXPECT_EQ(victor.At(0), 10);
  EXPECT_EQ(victor.At(1), 20);
  EXPECT_EQ(victor.At(2), 30);
}

TEST(vectorTest, AtInvalidIndexThrows) {
  s21::Vector<int> victor = {1, 2, 3};
  EXPECT_THROW(victor.At(3), std::out_of_range);
  EXPECT_THROW(victor.At(100), std::out_of_range);
}

TEST(VectorTest, ConstAtWorksCorrectly) {
  const s21::Vector<int> vec = {5, 10, 15};
  EXPECT_EQ(vec.At(0), 5);
  EXPECT_EQ(vec.At(1), 10);
  EXPECT_EQ(vec.At(2), 15);
}

TEST(VectorTest, ConstAtInvalidIndexThrows) {
  const s21::Vector<int> vec = {7, 8};
  EXPECT_THROW((void)vec.At(2), std::out_of_range);
}

TEST(vectorTest, OperatorSquareBrackets) {
  s21::Vector<int> victor = {5, 10, 15};
  EXPECT_EQ(victor[0], 5);
  EXPECT_EQ(victor[1], 10);
  EXPECT_EQ(victor[2], 15);
  victor[1] = 42;
  EXPECT_EQ(victor[1], 42);
}

TEST(vectorTest, FrontBackData) {
  s21::Vector<int> victor = {100, 200, 300};
  EXPECT_EQ(victor.Front(), 100);
  EXPECT_EQ(victor.Back(), 300);
  EXPECT_EQ(victor.Data()[0], 100);
}

TEST(vectorTest, Iterators) {
  s21::Vector<int> victor = {1, 2, 3};
  auto itVector = victor.Begin();
  EXPECT_EQ(*itVector, 1);
  ++itVector;
  EXPECT_EQ(*itVector, 2);
  auto end = victor.End();
  --end;
  EXPECT_EQ(*end, 3);
}

TEST(vectorTest, EmptyAndSize) {
  s21::Vector<int> empty_victor;
  EXPECT_TRUE(empty_victor.Empty());
  EXPECT_EQ(empty_victor.Size(), 0);

  s21::Vector<int> victor(4);
  EXPECT_FALSE(victor.Empty());
  EXPECT_EQ(victor.Size(), 4);
}

TEST(vectorTest, MaxSize) {
  s21::Vector<int> victor;
  EXPECT_GT(victor.MaxSize(), 1000);
}

TEST(VectorTest, ReserveIncreasesCapacity) {
  s21::Vector<int> victor;
  victor.Reserve(10);
  EXPECT_GE(victor.Capacity(), 10);
}

TEST(VectorTest, ShrinkToFitReducesCapacity) {
  s21::Vector<int> victor;
  for (int i = 0; i < 10; ++i) {
    victor.PushBack(i);
  }
  victor.Reserve(20);
  EXPECT_GT(victor.Capacity(), victor.Size());
  victor.ShrinkToFit();
  EXPECT_EQ(victor.Capacity(), victor.Size());
}

TEST(VectorTest, ClearEmptiesVector) {
  s21::Vector<int> victor{1, 2, 3};
  victor.Clear();
  EXPECT_EQ(victor.Size(), 0);
  EXPECT_GE(victor.Capacity(), 3);
}

TEST(VectorTest, PushBackAddsElements) {
  s21::Vector<int> victor;
  victor.PushBack(42);
  EXPECT_EQ(victor.Size(), 1);
  EXPECT_EQ(victor[0], 42);
}

TEST(VectorTest, PopBackRemovesLastElement) {
  s21::Vector<int> victor{1, 2, 3};
  victor.PopBack();
  EXPECT_EQ(victor.Size(), 2);
  EXPECT_EQ(victor.Back(), 2);
}

TEST(VectorTest, PopBackThrowsWhenEmpty) {
  s21::Vector<int> victor;
  EXPECT_THROW(victor.PopBack(), std::out_of_range);
}

TEST(VectorTest, InsertAtBeginning) {
  s21::Vector<int> victor{2, 3};
  victor.Insert(victor.Begin(), 1);
  EXPECT_EQ(victor[0], 1);
  EXPECT_EQ(victor.Size(), 3);
}

TEST(VectorTest, InsertInMiddle) {
  s21::Vector<int> victor{1, 3};
  victor.Insert(victor.Begin() + 1, 2);
  EXPECT_EQ(victor[1], 2);
}

TEST(VectorTest, EraseRemovesElement) {
  s21::Vector<int> victor{1, 2, 3};
  victor.Erase(victor.Begin() + 1);
  EXPECT_EQ(victor.Size(), 2);
  EXPECT_EQ(victor[1], 3);
}

TEST(VectorTest, SwapExchangesData) {
  s21::Vector<int> firstVec{1, 2};
  s21::Vector<int> secVec{3, 4, 5};
  firstVec.Swap(secVec);
  EXPECT_EQ(firstVec.Size(), 3);
  EXPECT_EQ(secVec.Size(), 2);
  EXPECT_EQ(firstVec[0], 3);
  EXPECT_EQ(secVec[0], 1);
}

TEST(VectorIteratorTest, DereferenceOperator) {
  s21::Vector<int> vec = {10, 20, 30};
  auto it = vec.Begin();
  EXPECT_EQ(*it, 10);
}

TEST(VectorIteratorTest, IncrementOperators) {
  s21::Vector<int> vec = {1, 2, 3};
  auto it = vec.Begin();

  ++it;
  EXPECT_EQ(*it, 2);

  it++;
  EXPECT_EQ(*it, 3);
}

TEST(VectorIteratorTest, DecrementOperators) {
  s21::Vector<int> vec = {5, 6, 7};
  auto it = vec.End();
  --it;
  EXPECT_EQ(*it, 7);

  it--;
  EXPECT_EQ(*it, 6);
}

TEST(VectorIteratorTest, EqualityOperators) {
  s21::Vector<int> vec = {100, 200};
  auto it1 = vec.Begin();
  auto it2 = vec.Begin();
  auto it3 = vec.Begin() + 1;

  EXPECT_TRUE(it1 == it2);
  EXPECT_FALSE(it1 == it3);
  EXPECT_TRUE(it1 != it3);
}

TEST(VectorIteratorTest, SubscriptOperator) {
  s21::Vector<int> vec = {3, 6, 9};
  auto it = vec.Begin();
  EXPECT_EQ(it[0], 3);
  EXPECT_EQ(it[1], 6);
  EXPECT_EQ(it[2], 9);
}

TEST(VectorIteratorTest, ArithmeticOperators) {
  s21::Vector<int> vec = {1, 2, 3, 4, 5};
  auto it = vec.Begin();
  auto it2 = it + 3;
  EXPECT_EQ(*it2, 4);

  auto it3 = it2 - 2;
  EXPECT_EQ(*it3, 2);

  EXPECT_EQ(it3 - it, 1);
}

TEST(VectorIteratorTest, RelationalOperators) {
  s21::Vector<int> vec = {1, 2, 3};
  auto it1 = vec.Begin();
  auto it2 = vec.Begin() + 2;

  EXPECT_TRUE(it2 > it1);
  EXPECT_TRUE(it1 < it2);
  EXPECT_TRUE(it2 >= it1);
  EXPECT_TRUE(it1 <= it2);
  EXPECT_TRUE(it1 <= it1);
  EXPECT_TRUE(it1 >= it1);
}

TEST(VectorConstIteratorTest, DereferenceOperator) {
  const s21::Vector<int> vec = {10, 20, 30};
  auto it = vec.Cbegin();
  EXPECT_EQ(*it, 10);
}

TEST(VectorConstIteratorTest, EqualityOperators) {
  const s21::Vector<int> vec = {100, 200};
  auto it1 = vec.Cbegin();
  auto it2 = vec.Cbegin();
  auto it3 = vec.Cbegin() + 1;

  EXPECT_TRUE(it1 == it2);
  EXPECT_FALSE(it1 == it3);
  EXPECT_TRUE(it1 != it3);
}

TEST(VectorConstIteratorTest, SubscriptOperator) {
  const s21::Vector<int> vec = {3, 6, 9};
  auto it = vec.Cbegin();
  EXPECT_EQ(it[0], 3);
  EXPECT_EQ(it[1], 6);
  EXPECT_EQ(it[2], 9);
}

TEST(VectorConstIteratorTest, ArithmeticOperators) {
  const s21::Vector<int> vec = {1, 2, 3, 4, 5};
  auto it = vec.Cbegin();
  auto it2 = it + 3;
  EXPECT_EQ(*it2, 4);

  auto it3 = it2 - 2;
  EXPECT_EQ(*it3, 2);

  EXPECT_EQ(it3 - it, 1);
}

TEST(VectorConstIteratorTest, RelationalOperators) {
  const s21::Vector<int> vec = {1, 2, 3};
  auto it1 = vec.Cbegin();
  auto it2 = vec.Cbegin() + 2;

  EXPECT_TRUE(it2 > it1);
  EXPECT_TRUE(it1 < it2);
  EXPECT_TRUE(it2 >= it1);
  EXPECT_TRUE(it1 <= it2);
  EXPECT_TRUE(it1 <= it1);
  EXPECT_TRUE(it1 >= it1);
}

TEST(VectorTest, InsertManyCheckEachElement) {
  s21::Vector<int> vec = {1, 2, 3};

  auto it = vec.InsertMany(vec.Cbegin() + 1, 10);

  ASSERT_EQ(vec.Size(), 4);

  EXPECT_EQ(vec[0], 1);
  EXPECT_EQ(vec[1], 10);  // вставленный элемент
  EXPECT_EQ(vec[2], 2);
  EXPECT_EQ(vec[3], 3);

  EXPECT_EQ(*it, 10);
  EXPECT_EQ(it, vec.Begin() + 1);
}

TEST(VectorTest, InsertManyMultipleElements) {
  s21::Vector<int> vec = {1, 2, 3};

  auto it = vec.InsertMany(vec.Cbegin(), 20, 30);

  ASSERT_EQ(vec.Size(), 5);
  EXPECT_EQ(vec[0], 20);  // первый вставленный
  EXPECT_EQ(vec[1], 30);  // второй вставленный
  EXPECT_EQ(vec[2], 1);
  EXPECT_EQ(vec[3], 2);
  EXPECT_EQ(vec[4], 3);

  EXPECT_EQ(*it, 20);
  EXPECT_EQ(it, vec.Begin());
}

TEST(VectorTest, InsertManyAtEnd) {
  s21::Vector<int> vec = {1, 2, 3};

  auto it = vec.InsertMany(vec.Cend(), 40, 50);

  ASSERT_EQ(vec.Size(), 5);
  EXPECT_EQ(vec[0], 1);
  EXPECT_EQ(vec[1], 2);
  EXPECT_EQ(vec[2], 3);
  EXPECT_EQ(vec[3], 40);
  EXPECT_EQ(vec[4], 50);

  EXPECT_EQ(*it, 40);
  EXPECT_EQ(it, vec.Begin() + 3);
}

TEST(VectorTest, InsertManyToEmpty) {
  s21::Vector<int> vec;

  auto it = vec.InsertMany(vec.Cbegin(), 10, 20, 30);

  ASSERT_EQ(vec.Size(), 3);
  EXPECT_EQ(vec[0], 10);
  EXPECT_EQ(vec[1], 20);
  EXPECT_EQ(vec[2], 30);

  EXPECT_EQ(it, vec.Begin());
}

TEST(VectorTest, InsertManyNoArgs) {
  s21::Vector<int> vec = {1, 2, 3};
  size_t old_size = vec.Size();

  auto it = vec.InsertMany(vec.Cbegin() + 1);

  ASSERT_EQ(vec.Size(), old_size);

  EXPECT_EQ(it, vec.Begin() + 1);

  EXPECT_EQ(vec[0], 1);
  EXPECT_EQ(vec[1], 2);
  EXPECT_EQ(vec[2], 3);
  EXPECT_EQ(1, 1);
}

TEST(VectorTest, InsertManyBack) {
  s21::Vector<int> v;

  v.InsertManyBack(1, 2, 3);
  ASSERT_EQ(v.Size(), 3);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
  EXPECT_EQ(v[2], 3);

  std::string s = "test";
  s21::Vector<std::string> vs;
  vs.InsertManyBack(std::move(s));
  EXPECT_FALSE(vs.Empty());
}