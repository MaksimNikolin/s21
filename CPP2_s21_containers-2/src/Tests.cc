#include <gtest/gtest.h>

#include <list>
#include <vector>

#include "./s21_containers/s21_containers.h"

// VECTOR

TEST(Vector, Constructor) {
  try { s21::vector<int> s21_vec(-1); }
  catch (std::out_of_range const& err) {
    EXPECT_EQ(err.what(), std::string("out of range"));
  }
}

TEST(Vector, ConstructorInitializerList) {
  std::initializer_list<int> b;
  s21::vector<int> s21_vec{b};
  std::vector<int> std_vec{b};
}

TEST(Vector, At) {
  s21::vector<int> s21_vec;
  std::vector<int> std_vec;
  EXPECT_ANY_THROW(s21_vec.at(1));
  EXPECT_ANY_THROW(std_vec.at(1));
}

TEST(Vector, Insert1) {
  s21::vector<int> s21_vec{1, 3, 4};
  std::vector<int> std_vec{1, 3, 4};
  s21_vec.insert(s21_vec.begin() + 1, 2);
  std_vec.insert(std_vec.begin() + 1, 2);
}

TEST(Vector, Insert2) {
  try {
    s21::vector<int> s21_vec{1, 2, 3};
    s21_vec.insert(s21_vec.begin() + 5, 6);
  } catch (std::out_of_range const& err) {
    EXPECT_EQ(err.what(), std::string("out ot range"));
  }
}

TEST(Vector, Erase1) {
  s21::vector<int> s21_vec{1, 2, 3};
  std::vector<int> std_vec{1, 2, 3};
  s21_vec.erase(s21_vec.begin() + 1);
  std_vec.erase(std_vec.begin() + 1);
  EXPECT_EQ(s21_vec.at(0), std_vec.at(0));
}

TEST(Vector, Erase2) {
  try {
    s21::vector<int> s21_vec{1, 2, 3};
    s21_vec.erase(s21_vec.begin() - 1);
  } catch (std::out_of_range const& err) {
    EXPECT_EQ(err.what(), std::string("out ot range"));
  }
}

TEST(Vector, PopBack) {
  s21::vector<int> s21_vec{1, 2};
  s21_vec.pop_back();
  EXPECT_EQ(s21_vec.size(), 1);
}

TEST(Vector, PushBack) {
  int n = 2;
  s21::vector<int> s21_vec(n);
  s21_vec.push_back(1);
  EXPECT_EQ(s21_vec.size(), n + 1);
}

// LIST

template <typename value_type>
bool compare_lists(s21::list<value_type> s21_list, std::list<value_type> std_list) {
  bool res = true;
  if (s21_list.size() == std_list.size()) {
    auto s21_it = s21_list.begin();
    auto std_it = std_list.begin();
    for (size_t i = 0; i != s21_list.size(); i++) {
      s21_it++;
      std_it++;
    }
  }
  return res;
}

TEST(List, SizeConstructorThrow) {
  try { s21::list<int> s21_list(-1); }
  catch (std::out_of_range const& err) {
    EXPECT_EQ(err.what(), std::string("out of range"));
  }
}

TEST(List, Front) {
  s21::list<int> s21_list{1, 2, 3};
  std::list<int> std_list{1, 2, 3};
  EXPECT_EQ(s21_list.front(), std_list.front());
}

TEST(List, Back) {
  s21::list<int> s21_list{1, 2, 3};
  std::list<int> std_list{1, 2, 3};
  EXPECT_EQ(s21_list.back(), std_list.back());
}

TEST(List, Begin) {
  s21::list<int> s21_list1{1, 2, 3};
  std::list<int> std_list2{1, 2, 3};
  EXPECT_EQ(*s21_list1.begin(), *std_list2.begin());
}

TEST(List, End) {
  s21::list<int> s21_list1{1, 2, 3};
  std::list<int> std_list2{1, 2, 3};
  EXPECT_EQ(*s21_list1.begin(), *std_list2.begin());
}

TEST(List, Merge1) {
  s21::list<int> s21_list1{1, 6, 4};
  s21::list<int> s21_list2{5, 3, 2, 7};
  s21_list1.merge(s21_list2);
  std::list<int> std_list1{1, 6, 4};
  std::list<int> std_list2{5, 3, 2, 7};
  std_list1.merge(std_list2);
  EXPECT_TRUE(compare_lists(s21_list1, std_list1));
}

TEST(List, Merge2) {
  s21::list<int> s21_list1;
  s21::list<int> s21_list2{4, 2, 3, 1};
  s21_list1.merge(s21_list2);
  std::list<int> std_list1;
  std::list<int> std_list2{4, 2, 3, 1};
  std_list1.merge(std_list2);
  EXPECT_TRUE(compare_lists(s21_list1, std_list1));
}

TEST(List, Splice) {
  s21::list<int> s21_list1{1, 2, 3};
  s21::list<int> s21_list2{4, 5, 6};
  s21_list1.splice(s21_list1.begin(), s21_list2);
  std::list<int> std_list1{1, 2, 3};
  std::list<int> std_list2{4, 5, 6};
  std_list1.splice(std_list1.begin(), std_list2);
  EXPECT_TRUE(compare_lists(s21_list1, std_list1));
}

TEST(List, Reverse) {
  s21::list<int> s21_list{1, 2, 3};
  std::list<int> std_list{1, 2, 3};
  s21_list.reverse();
  std_list.reverse();
  EXPECT_TRUE(compare_lists(s21_list, std_list));
}

TEST(List, Unique) {
  s21::list<int> s21_list{1, 2, 2, 3, 4, 5, 5, 5};
  std::list<int> std_list{1, 2, 2, 3, 4, 5, 5, 5};
  s21_list.unique();
  std_list.unique();
  EXPECT_TRUE(compare_lists(s21_list, std_list));
}

TEST(List, Insert1) {
  s21::list<int> s21_list1(2);
  s21_list1.insert(s21_list1.begin(), 1);
  std::list<int> std_list1(2);
  std_list1.insert(std_list1.begin(), 1);
  EXPECT_TRUE(compare_lists(s21_list1, std_list1));
}

TEST(List, Insert2) {
  s21::list<int> s21_list1;
  s21_list1.insert(s21_list1.end(), 1);
  std::list<int> std_list1;
  std_list1.insert(std_list1.end(), 1);
  EXPECT_TRUE(compare_lists(s21_list1, std_list1));
}

TEST(List, Erase1) {
  s21::list<int> s21_list1{1, 2, 3};
  s21_list1.erase(s21_list1.begin());
  std::list<int> std_list1{1, 2, 3};
  std_list1.erase(std_list1.begin());
  EXPECT_TRUE(compare_lists(s21_list1, std_list1));
}

TEST(List, Erase2) {
  s21::list<int> s21_list1{1, 2, 3};
  EXPECT_THROW(s21_list1.erase(s21_list1.end()), std::invalid_argument);
}

TEST(List, Erase3) {
  s21::list<int> s21_list1{1, 2, 3};
  s21_list1.erase(--s21_list1.end());
  std::list<int> std_list1{1, 2, 3};
  std_list1.erase(std_list1.end().operator--());
  EXPECT_TRUE(compare_lists(s21_list1, std_list1));
}

TEST(List, PopBack) {
    s21::list<int> s21_list;
    EXPECT_THROW(s21_list.pop_back(), std::out_of_range);
}

TEST(List, PopFront1) {
  s21::list<int> s21_list{1, 2, 3};
  s21_list.pop_front();
  std::list<int> std_list{1, 2, 3};
  std_list.pop_front();
  EXPECT_TRUE(compare_lists(s21_list, std_list));
}

TEST(List, PopFront2) {
  s21::list<int> s21_list;
  EXPECT_THROW(s21_list.pop_front(), std::out_of_range);
}

TEST(List, PopFront3) {
  s21::list<int> s21_list{1};
  s21_list.pop_front();
  std::list<int> std_list{1};
  std_list.pop_front();
  EXPECT_TRUE(compare_lists(s21_list, std_list));
}

TEST(List, PushFront) {
  s21::list<int> s21_list{2, 3};
  s21_list.push_front(1);
  std::list<int> std_list{2, 3};
  std_list.push_front(1);
  EXPECT_TRUE(compare_lists(s21_list, std_list));
}

TEST(List, Swap) {
  s21::list<int> s21_list1{1, 2, 3};
  s21::list<int> s21_list2{4, 5, 6, 7};
  s21_list1.swap(s21_list2);
  std::list<int> std_list1{1, 2, 3};
  std::list<int> std_list2{4, 5, 6, 7};
  std_list1.swap(std_list2);
  EXPECT_TRUE(compare_lists(s21_list1, std_list1));
  EXPECT_TRUE(compare_lists(s21_list2, std_list2));
}

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
