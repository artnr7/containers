#include <gtest/gtest.h>

#include <list>

#include "base_containers/s21_list.h"

TEST(List, Constructor_Default) {
  s21::List<int> our_List;
  std::list<int> std_List;
  EXPECT_EQ(our_List.Empty(), std_List.empty());
}

TEST(List, Constructor_Size) {
  s21::List<int> our_List(5);
  std::list<int> std_List(5);
  EXPECT_EQ(our_List.Size(), std_List.size());
}

TEST(List, Constructor_List) {
  s21::List<int> our_List = {1, 2, 3};
  std::list<int> std_List = {1, 2, 3};
  EXPECT_EQ(our_List.Front(), std_List.front());
  EXPECT_EQ(our_List.Back(), std_List.back());
}

TEST(List, Constructor_Copy) {
  s21::List<int> our_List = {1, 2, 3};
  std::list<int> std_List = {1, 2, 3};
  s21::List<int> our_copy(our_List);
  std::list<int> std_copy(std_List);
  EXPECT_EQ(our_copy.Front(), std_copy.front());
  EXPECT_EQ(our_copy.Back(), std_copy.back());
}

TEST(List, Operator_Copy) {
  s21::List<int> our_List = {1, 2, 3};
  std::list<int> std_List = {1, 2, 3};
  s21::List<int> our_copy;
  our_copy = our_List;
  std::list<int> std_copy;
  std_copy = std_List;
  EXPECT_EQ(our_copy.Front(), std_copy.front());
  EXPECT_EQ(our_copy.Back(), std_copy.back());
}

TEST(List, Constructor_Move) {
  s21::List<int> our_List = {1, 2, 3};
  std::list<int> std_List = {1, 2, 3};
  s21::List<int> our_copy(std::move(our_List));
  std::list<int> std_copy(std::move(std_List));
  EXPECT_EQ(our_copy.Front(), std_copy.front());
  EXPECT_EQ(our_copy.Back(), std_copy.back());
  EXPECT_EQ(our_List.Empty(), std_List.empty());
}

TEST(List, Operator_Move) {
  s21::List<int> our_List = {1, 2, 3};
  std::list<int> std_List = {1, 2, 3};
  s21::List<int> our_copy;
  our_copy = std::move(our_List);
  std::list<int> std_copy;
  std_copy = std::move(std_List);
  EXPECT_EQ(our_copy.Front(), std_copy.front());
  EXPECT_EQ(our_copy.Back(), std_copy.back());
  EXPECT_EQ(our_List.Empty(), std_List.empty());
}

TEST(List, Size) {
  s21::List<int> our_List = {1, 2, 3};
  std::list<int> std_List = {1, 2, 3};
  EXPECT_EQ(our_List.Size(), std_List.size());
}

TEST(List, PushFront) {
  s21::List<int> our_List;
  std::list<int> std_List;
  our_List.PushFront(1);
  std_List.push_front(1);
  EXPECT_EQ(our_List.Front(), std_List.front());
  EXPECT_EQ(our_List.Back(), std_List.back());
  our_List.PushFront(2);
  std_List.push_front(2);
  EXPECT_EQ(our_List.Front(), std_List.front());
  EXPECT_EQ(our_List.Back(), std_List.back());
  our_List.PushFront(3);
  std_List.push_front(3);
  EXPECT_EQ(our_List.Front(), std_List.front());
  EXPECT_EQ(our_List.Back(), std_List.back());
}

TEST(List, PushBack) {
  s21::List<int> our_List;
  std::list<int> std_List;
  our_List.PushBack(1);
  std_List.push_back(1);
  EXPECT_EQ(our_List.Front(), std_List.front());
  EXPECT_EQ(our_List.Back(), std_List.back());
  our_List.PushBack(2);
  std_List.push_back(2);
  EXPECT_EQ(our_List.Front(), std_List.front());
  EXPECT_EQ(our_List.Back(), std_List.back());
  our_List.PushBack(3);
  std_List.push_back(3);
  EXPECT_EQ(our_List.Front(), std_List.front());
  EXPECT_EQ(our_List.Back(), std_List.back());
}

TEST(List, PopFront) {
  s21::List<int> our_List;
  std::list<int> std_List;
  our_List.PushBack(1);
  std_List.push_back(1);
  EXPECT_EQ(our_List.Front(), std_List.front());
  EXPECT_EQ(our_List.Back(), std_List.back());
  our_List.PushBack(2);
  std_List.push_back(2);
  EXPECT_EQ(our_List.Front(), std_List.front());
  EXPECT_EQ(our_List.Back(), std_List.back());
  our_List.PushBack(3);
  std_List.push_back(3);
  EXPECT_EQ(our_List.Front(), std_List.front());
  EXPECT_EQ(our_List.Back(), std_List.back());
  our_List.PopFront();
  std_List.pop_front();
  EXPECT_EQ(our_List.Front(), std_List.front());
  EXPECT_EQ(our_List.Back(), std_List.back());
}

TEST(List, PopBack) {
  s21::List<int> our_List;
  std::list<int> std_List;
  our_List.PushBack(1);
  std_List.push_back(1);
  EXPECT_EQ(our_List.Front(), std_List.front());
  EXPECT_EQ(our_List.Back(), std_List.back());
  our_List.PushBack(2);
  std_List.push_back(2);
  EXPECT_EQ(our_List.Front(), std_List.front());
  EXPECT_EQ(our_List.Back(), std_List.back());
  our_List.PushBack(3);
  std_List.push_back(3);
  EXPECT_EQ(our_List.Front(), std_List.front());
  EXPECT_EQ(our_List.Back(), std_List.back());
  our_List.PopBack();
  std_List.pop_back();
  EXPECT_EQ(our_List.Front(), std_List.front());
  EXPECT_EQ(our_List.Back(), std_List.back());
}

TEST(List, Iterator_Begin) {
  s21::List<int> our_List = {1, 2, 3};
  std::list<int> std_List = {1, 2, 3};
  s21::List<int>::Iterator our_it;
  our_it = our_List.Begin();
  std::list<int>::iterator std_it;
  std_it = std_List.begin();
  EXPECT_EQ(*our_it, *std_it);
}

TEST(List, Iterator_BeginPlusAndMinus) {
  s21::List<int> our_List = {1, 2, 3};
  std::list<int> std_List = {1, 2, 3};
  s21::List<int>::Iterator our_it;
  our_it = our_List.Begin();
  ++our_it;
  std::list<int>::iterator std_it;
  std_it = std_List.begin();
  ++std_it;
  EXPECT_EQ(*our_it, *std_it);
  --our_it;
  --std_it;
  EXPECT_EQ(*our_it, *std_it);
}

TEST(List, Iterator_End_Last) {
  s21::List<int> our_List = {1, 2, 3};
  std::list<int> std_List = {1, 2, 3};
  s21::List<int>::Iterator our_it;
  our_it = our_List.End();
  --our_it;
  std::list<int>::iterator std_it;
  std_it = std_List.end();
  --std_it;
  EXPECT_EQ(*our_it, *std_it);
}

TEST(List, Iterator_Equals) {
  s21::List<int> first_List = {1, 2, 3};
  s21::List<int>::Iterator our_it_first;
  our_it_first = first_List.Begin();
  s21::List<int>::Iterator our_it_second;
  our_it_second = first_List.Begin();
  EXPECT_TRUE(our_it_first == our_it_second);
  ++our_it_second;
  EXPECT_TRUE(our_it_first != our_it_second);
}

TEST(List, Insert) {
  s21::List<int> our_List;
  std::list<int> std_List;
  s21::List<int>::Iterator our_it;
  our_it = our_List.Begin();
  std::list<int>::iterator std_it;
  std_it = std_List.begin();
  our_List.Insert(our_it, 5);
  std_List.insert(std_it, 5);
  EXPECT_EQ(our_List.Front(), std_List.front());
  EXPECT_EQ(our_List.Back(), std_List.back());
  our_List.Insert(our_it, 7);
  std_List.insert(std_it, 7);
  our_List.Insert(our_it, 9);
  std_List.insert(std_it, 9);
  EXPECT_EQ(our_List.Front(), std_List.front());
  EXPECT_EQ(our_List.Back(), std_List.back());
}

TEST(List, Erase) {
  s21::List<int> our_List = {1, 2, 3, 4, 5};
  std::list<int> std_List = {1, 2, 3, 4, 5};
  our_List.Erase(our_List.Begin());
  std_List.erase(std_List.begin());
  EXPECT_EQ(our_List.Front(), std_List.front());
  EXPECT_EQ(our_List.Back(), std_List.back());
  s21::List<int>::Iterator our_it;
  our_it = our_List.Begin();
  ++our_it;
  std::list<int>::iterator std_it;
  std_it = std_List.begin();
  ++std_it;
  EXPECT_EQ(our_List.Front(), std_List.front());
  EXPECT_EQ(our_List.Back(), std_List.back());
}

TEST(List, Splice) {
  s21::List<int> our_List_first = {1};
  s21::List<int> our_List_second = {2, 3, 4, 5};
  std::list<int> std_List_first = {1};
  std::list<int> std_List_second = {2, 3, 4, 5};
  s21::List<int>::Iterator our_it = our_List_first.Begin();
  std::list<int>::iterator std_it = std_List_first.begin();
  our_List_first.Splice(our_it, our_List_second);
  std_List_first.splice(std_it, std_List_second);
  EXPECT_EQ(our_List_first.Front(), std_List_first.front());
  EXPECT_EQ(our_List_first.Back(), std_List_first.back());
}

TEST(List, Merge) {
  s21::List<int> our_List_first = {1};
  s21::List<int> our_List_second = {2, 3, 4, 5};
  std::list<int> std_List_first = {1};
  std::list<int> std_List_second = {2, 3, 4, 5};
  our_List_first.Merge(our_List_second);
  std_List_first.merge(std_List_second);
  EXPECT_EQ(our_List_first.Front(), std_List_first.front());
  EXPECT_EQ(our_List_first.Back(), std_List_first.back());
  EXPECT_EQ(our_List_second.Empty(), std_List_second.empty());
}

TEST(List, Reverse) {
  s21::List<int> our_List = {1, 2, 3, 4, 5};
  std::list<int> std_List = {1, 2, 3, 4, 5};
  our_List.Reverse();
  std_List.reverse();
  EXPECT_EQ(our_List.Front(), std_List.front());
  EXPECT_EQ(our_List.Back(), std_List.back());
}

TEST(List, Unique) {
  s21::List<int> our_List = {1, 2, 2, 3, 3};
  std::list<int> std_List = {1, 2, 2, 3, 3};
  s21::List<int>::Iterator our_it;
  std::list<int>::iterator std_it;
  our_List.Unique();
  std_List.unique();
  our_it = our_List.Begin();
  std_it = std_List.begin();
  EXPECT_EQ(*our_it, *std_it);
  ++our_it;
  ++std_it;
  EXPECT_EQ(*our_it, *std_it);
  ++our_it;
  ++std_it;
  EXPECT_EQ(*our_it, *std_it);
}

TEST(List, Sort) {
  s21::List<int> our_List = {2, 4, 1, 3, 5};
  std::list<int> std_List = {2, 4, 1, 3, 5};
  s21::List<int>::Iterator our_it;
  std::list<int>::iterator std_it;
  our_List.Sort();
  std_List.sort();
  our_it = our_List.Begin();
  std_it = std_List.begin();
  EXPECT_EQ(*our_it, *std_it);
  ++our_it;
  ++std_it;
  EXPECT_EQ(*our_it, *std_it);
  ++our_it;
  ++std_it;
  EXPECT_EQ(*our_it, *std_it);
  ++our_it;
  ++std_it;
  EXPECT_EQ(*our_it, *std_it);
  ++our_it;
  ++std_it;
  EXPECT_EQ(*our_it, *std_it);
}

TEST(List, InsertMany) {
  s21::List<int> our_List = {1, 2, 3, 4, 5};
  s21::List<int>::Iterator our_it = our_List.Begin();
  ++our_it;
  our_List.InsertMany(our_it, 7, 8, 9);
  our_it = our_List.Begin();
  EXPECT_EQ(*our_it, 1);
  ++our_it;
  EXPECT_EQ(*our_it, 9);
  ++our_it;
  EXPECT_EQ(*our_it, 8);
  ++our_it;
  EXPECT_EQ(*our_it, 7);
  ++our_it;
  EXPECT_EQ(*our_it, 2);
}

TEST(List, InsertManyBack) {
  s21::List<int> our_List = {1, 2, 3, 4, 5};
  s21::List<int>::Iterator our_it;
  our_List.InsertManyBack(7, 8, 9);
  our_it = our_List.End();
  --our_it;
  EXPECT_EQ(*our_it, 9);
  --our_it;
  EXPECT_EQ(*our_it, 8);
  --our_it;
  EXPECT_EQ(*our_it, 7);
  --our_it;
  EXPECT_EQ(*our_it, 5);
  --our_it;
  EXPECT_EQ(*our_it, 4);
}

TEST(List, InsertManyFront) {
  s21::List<int> our_List = {1, 2, 3, 4, 5};
  s21::List<int>::Iterator our_it;
  our_List.InsertManyFront(7, 8, 9);
  our_it = our_List.Begin();
  EXPECT_EQ(*our_it, 9);
  ++our_it;
  EXPECT_EQ(*our_it, 8);
  ++our_it;
  EXPECT_EQ(*our_it, 7);
  ++our_it;
  EXPECT_EQ(*our_it, 1);
  ++our_it;
  EXPECT_EQ(*our_it, 2);
}
