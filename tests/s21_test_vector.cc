#include <gtest/gtest.h>

#include "./../s21_vector.h"

// TODO(root): Add test cases for vector

TEST(vectorTest, DefaultConstructor) {
  s21::vector<int> victor;
  EXPECT_EQ(victor.size(), 0);
  EXPECT_EQ(victor.capacity(), 0);
}

TEST(vectorTest, SizedConstructor) {
  s21::vector<int> victor(5);
  EXPECT_EQ(victor.size(), 5);
  EXPECT_EQ(victor.capacity(), 5);
}

TEST(vectorTest, InitializerListConstructor) {
  s21::vector<int> victor{1, 2, 3, 4};
  EXPECT_EQ(victor.size(), 4);
  EXPECT_EQ(victor[0], 1);
  EXPECT_EQ(victor[1], 2);
  EXPECT_EQ(victor[2], 3);
  EXPECT_EQ(victor[3], 4);
}

TEST(vectorTest, CopyConstructor) {
  s21::vector<int> zictor{1, 2, 3, 4};
  s21::vector<int> victor(zictor);
  EXPECT_EQ(victor.size(), 4);
  EXPECT_EQ(victor[0], 1);
  EXPECT_EQ(victor[1], 2);
  EXPECT_EQ(victor[2], 3);
  EXPECT_EQ(victor[3], 4);
}

TEST(vectorTest, MoveConstructor) {
  s21::vector<int> zictor{1, 2, 3, 4};
  s21::vector<int> victor(std::move(zictor));
  EXPECT_EQ(victor.size(), 4);
  EXPECT_EQ(victor[0], 1);
  EXPECT_EQ(victor[1], 2);
  EXPECT_EQ(victor[2], 3);
  EXPECT_EQ(victor[3], 4);
  EXPECT_EQ(zictor.size(), 0);
  EXPECT_EQ(zictor.capacity(), 0);
}

TEST(vectorTest, MoveEqConstructor) {
  s21::vector<int> zictor{1, 2, 3, 4};
  s21::vector<int> victor;
  victor = std::move(zictor);
  EXPECT_EQ(victor.size(), 4);
  EXPECT_EQ(victor[0], 1);
  EXPECT_EQ(victor[1], 2);
  EXPECT_EQ(victor[2], 3);
  EXPECT_EQ(victor[3], 4);
  EXPECT_EQ(zictor.size(), 0);
  EXPECT_EQ(zictor.capacity(), 0);
}

TEST(vectorTest, AtValidIndex) {
  s21::vector<int> victor = {10, 20, 30};
  EXPECT_EQ(victor.at(0), 10);
  EXPECT_EQ(victor.at(1), 20);
  EXPECT_EQ(victor.at(2), 30);
}

TEST(vectorTest, AtInvalidIndexThrows) {
  s21::vector<int> victor = {1, 2, 3};
  EXPECT_THROW(victor.at(3), std::out_of_range);
  EXPECT_THROW(victor.at(100), std::out_of_range);
}

TEST(VectorTest, ConstAtWorksCorrectly) {
  const s21::vector<int> vec = {5, 10, 15};
  EXPECT_EQ(vec.at(0), 5);
  EXPECT_EQ(vec.at(1), 10);
  EXPECT_EQ(vec.at(2), 15);
}

TEST(VectorTest, ConstAtInvalidIndexThrows) {
  const s21::vector<int> vec = {7, 8};
  EXPECT_THROW((void)vec.at(2), std::out_of_range);
}

TEST(vectorTest, OperatorSquareBrackets) {
  s21::vector<int> victor = {5, 10, 15};
  EXPECT_EQ(victor[0], 5);
  EXPECT_EQ(victor[1], 10);
  EXPECT_EQ(victor[2], 15);
  victor[1] = 42;
  EXPECT_EQ(victor[1], 42);
}

TEST(vectorTest, FrontBackData) {
  s21::vector<int> victor = {100, 200, 300};
  EXPECT_EQ(victor.front(), 100);
  EXPECT_EQ(victor.back(), 300);
  EXPECT_EQ(victor.data()[0], 100);
}

TEST(vectorTest, Iterators) {
  s21::vector<int> victor = {1, 2, 3};
  auto itVector = victor.begin();
  EXPECT_EQ(*itVector, 1);
  ++itVector;
  EXPECT_EQ(*itVector, 2);
  auto end = victor.end();
  --end;
  EXPECT_EQ(*end, 3);
}

TEST(vectorTest, ConstIterators) {
  const s21::vector<int> victor = {11, 22, 33};
  auto itVector = victor.cbegin();
  EXPECT_EQ(*itVector, 11);
  ++itVector;
  EXPECT_EQ(*itVector, 22);
  auto end = victor.cend();
  --end;
  EXPECT_EQ(*end, 33);
}

TEST(vectorTest, EmptyAndSize) {
  s21::vector<int> empty_victor;
  EXPECT_TRUE(empty_victor.empty());
  EXPECT_EQ(empty_victor.size(), 0);

  s21::vector<int> victor(4);
  EXPECT_FALSE(victor.empty());
  EXPECT_EQ(victor.size(), 4);
}

TEST(vectorTest, MaxSize) {
  s21::vector<int> victor;
  EXPECT_GT(victor.max_size(), 1000);
}

TEST(VectorTest, ReserveIncreasesCapacity) {
  s21::vector<int> victor;
  victor.reserve(10);
  EXPECT_GE(victor.capacity(), 10);
}

TEST(VectorTest, ShrinkToFitReducesCapacity) {
  s21::vector<int> victor;
  for (int i = 0; i < 10; ++i) {
    victor.push_back(i);
  }
  victor.reserve(20);
  EXPECT_GT(victor.capacity(), victor.size());
  victor.shrink_to_fit();
  EXPECT_EQ(victor.capacity(), victor.size());
}

TEST(VectorTest, ClearEmptiesVector) {
  s21::vector<int> victor{1, 2, 3};
  victor.clear();
  EXPECT_EQ(victor.size(), 0);
  EXPECT_GE(victor.capacity(), 3);
}

TEST(VectorTest, PushBackAddsElements) {
  s21::vector<int> victor;
  victor.push_back(42);
  EXPECT_EQ(victor.size(), 1);
  EXPECT_EQ(victor[0], 42);
}

TEST(VectorTest, PopBackRemovesLastElement) {
  s21::vector<int> victor{1, 2, 3};
  victor.pop_back();
  EXPECT_EQ(victor.size(), 2);
  EXPECT_EQ(victor.back(), 2);
}

TEST(VectorTest, PopBackThrowsWhenEmpty) {
  s21::vector<int> victor;
  EXPECT_THROW(victor.pop_back(), std::out_of_range);
}

TEST(VectorTest, InsertAtBeginning) {
  s21::vector<int> victor{2, 3};
  victor.insert(victor.begin(), 1);
  EXPECT_EQ(victor[0], 1);
  EXPECT_EQ(victor.size(), 3);
}

TEST(VectorTest, InsertInMiddle) {
  s21::vector<int> victor{1, 3};
  victor.insert(victor.begin() + 1, 2);
  EXPECT_EQ(victor[1], 2);
}

TEST(VectorTest, EraseRemovesElement) {
  s21::vector<int> victor{1, 2, 3};
  victor.erase(victor.begin() + 1);
  EXPECT_EQ(victor.size(), 2);
  EXPECT_EQ(victor[1], 3);
}

TEST(VectorTest, SwapExchangesData) {
  s21::vector<int> firstVec{1, 2};
  s21::vector<int> secVec{3, 4, 5};
  firstVec.swap(secVec);
  EXPECT_EQ(firstVec.size(), 3);
  EXPECT_EQ(secVec.size(), 2);
  EXPECT_EQ(firstVec[0], 3);
  EXPECT_EQ(secVec[0], 1);
}

TEST(VectorIteratorTest, DereferenceOperator) {
  s21::vector<int> vec = {10, 20, 30};
  auto it = vec.begin();
  EXPECT_EQ(*it, 10);
}

TEST(VectorIteratorTest, IncrementOperators) {
  s21::vector<int> vec = {1, 2, 3};
  auto it = vec.begin();

  ++it;
  EXPECT_EQ(*it, 2);

  it++;
  EXPECT_EQ(*it, 3);
}

TEST(VectorIteratorTest, DecrementOperators) {
  s21::vector<int> vec = {5, 6, 7};
  auto it = vec.end();
  --it;
  EXPECT_EQ(*it, 7);

  it--;
  EXPECT_EQ(*it, 6);
}

TEST(VectorIteratorTest, EqualityOperators) {
  s21::vector<int> vec = {100, 200};
  auto it1 = vec.begin();
  auto it2 = vec.begin();
  auto it3 = vec.begin() + 1;

  EXPECT_TRUE(it1 == it2);
  EXPECT_FALSE(it1 == it3);
  EXPECT_TRUE(it1 != it3);
}

TEST(VectorIteratorTest, SubscriptOperator) {
  s21::vector<int> vec = {3, 6, 9};
  auto it = vec.begin();
  EXPECT_EQ(it[0], 3);
  EXPECT_EQ(it[1], 6);
  EXPECT_EQ(it[2], 9);
}

TEST(VectorIteratorTest, ArithmeticOperators) {
  s21::vector<int> vec = {1, 2, 3, 4, 5};
  auto it = vec.begin();
  auto it2 = it + 3;
  EXPECT_EQ(*it2, 4);

  auto it3 = it2 - 2;
  EXPECT_EQ(*it3, 2);

  EXPECT_EQ(it3 - it, 1);
}

TEST(VectorIteratorTest, RelationalOperators) {
  s21::vector<int> vec = {1, 2, 3};
  auto it1 = vec.begin();
  auto it2 = vec.begin() + 2;

  EXPECT_TRUE(it2 > it1);
  EXPECT_TRUE(it1 < it2);
  EXPECT_TRUE(it2 >= it1);
  EXPECT_TRUE(it1 <= it2);
  EXPECT_TRUE(it1 <= it1);
  EXPECT_TRUE(it1 >= it1);
}

TEST(VectorConstIteratorTest, DereferenceOperator) {
  const s21::vector<int> vec = {10, 20, 30};
  auto it = vec.cbegin();
  EXPECT_EQ(*it, 10);
}

TEST(VectorConstIteratorTest, IncrementOperators) {
  const s21::vector<int> vec = {1, 2, 3};
  auto it = vec.cbegin();

  ++it;
  EXPECT_EQ(*it, 2);

  it++;
  EXPECT_EQ(*it, 3);
}

TEST(VectorConstIteratorTest, DecrementOperators) {
  const s21::vector<int> vec = {5, 6, 7};
  auto it = vec.cend();
  --it;
  EXPECT_EQ(*it, 7);

  it--;
  EXPECT_EQ(*it, 6);
}

TEST(VectorConstIteratorTest, EqualityOperators) {
  const s21::vector<int> vec = {100, 200};
  auto it1 = vec.cbegin();
  auto it2 = vec.cbegin();
  auto it3 = vec.cbegin() + 1;

  EXPECT_TRUE(it1 == it2);
  EXPECT_FALSE(it1 == it3);
  EXPECT_TRUE(it1 != it3);
}

TEST(VectorConstIteratorTest, SubscriptOperator) {
  const s21::vector<int> vec = {3, 6, 9};
  auto it = vec.cbegin();
  EXPECT_EQ(it[0], 3);
  EXPECT_EQ(it[1], 6);
  EXPECT_EQ(it[2], 9);
}

TEST(VectorConstIteratorTest, ArithmeticOperators) {
  const s21::vector<int> vec = {1, 2, 3, 4, 5};
  auto it = vec.cbegin();
  auto it2 = it + 3;
  EXPECT_EQ(*it2, 4);

  auto it3 = it2 - 2;
  EXPECT_EQ(*it3, 2);

  EXPECT_EQ(it3 - it, 1);
}

TEST(VectorConstIteratorTest, RelationalOperators) {
  const s21::vector<int> vec = {1, 2, 3};
  auto it1 = vec.cbegin();
  auto it2 = vec.cbegin() + 2;

  EXPECT_TRUE(it2 > it1);
  EXPECT_TRUE(it1 < it2);
  EXPECT_TRUE(it2 >= it1);
  EXPECT_TRUE(it1 <= it2);
  EXPECT_TRUE(it1 <= it1);
  EXPECT_TRUE(it1 >= it1);
}