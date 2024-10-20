#include <gtest/gtest.h>

#include "../s21_containersplus/array/s21_array.h"
#include "../s21_containersplus/multiset/s21_multiset.h"
#include "../s21_containersplus/s21_containersplus.h"

// MULTISET

TEST(Multiset, Size) {
  s21::Multiset<char> aTemp{'a', 'b', 'x', 'z'};
  std::multiset<char> bTemp{'a', 'b', 'x', 'z'};
  EXPECT_EQ(aTemp.Size(), bTemp.size());
}

TEST(Multiset, MaxSize) {
  s21::Multiset<double> a;
  EXPECT_TRUE(a.MaxSize());
}

TEST(Multiset, Clear) {
  s21::Multiset<std::string> a{"21", "BRYAN", "PROGRAMMER", "TEST"};
  std::multiset<std::string> b{"21", "BRYAN", "PROGRAMMER", "TEST"};
  a.Clear();
  b.clear();
  EXPECT_EQ(a.Size(), b.size());
}

TEST(Multiset, InsertFirstSituation) {
  s21::Multiset<double> a;
  std::multiset<double> b;
  s21::Multiset<double>::iterator myIt = a.Insert(13.21);
  std::multiset<double>::iterator originalIt = b.insert(13.21);
  EXPECT_EQ(myIt.First(), *originalIt);
}

TEST(Multiset, Erase1) {
  s21::Multiset<int> a{13, 8, 17, 1, 11, 15, 25};
  std::multiset<int> b{13, 8, 17, 1, 11, 15, 25};
  s21::Multiset<int>::iterator myIt = a.Begin();
  std::multiset<int>::iterator originalIt = b.begin();
  a.Erase(myIt);
  b.erase(originalIt);
  s21::Multiset<int>::iterator myItTemp = a.Begin();
  std::multiset<int>::iterator originalItTemp = b.begin();
  while (myItTemp != a.End()) {
    EXPECT_EQ(myItTemp.First(), *originalItTemp);
    ++myItTemp;
    ++originalItTemp;
  }
}

TEST(Multiset, Erase2) {
  s21::Multiset<int> a{13, 8, 17, 1, 11, 15, 25};
  std::multiset<int> b{13, 8, 17, 1, 11, 15, 25};
  a.Erase(a.Find(13));
  b.erase(b.find(13));
  s21::Multiset<int>::iterator myItTemp = a.Begin();
  std::multiset<int>::iterator originalItTemp = b.begin();
  while (myItTemp != a.End()) {
    EXPECT_EQ(myItTemp.First(), *originalItTemp);
    ++myItTemp;
    ++originalItTemp;
  }
}

TEST(Multiset, EqualRangeThird) {
  s21::Multiset<char> a{'a', 'b', 'b', 'd'};
  std::multiset<char> b{'a', 'b', 'b', 'd'};
  auto myPair = a.EqualRange('b');
  auto originalPair = b.equal_range('b');
  EXPECT_EQ(myPair.first.First(), *originalPair.first);
  EXPECT_EQ(myPair.second.First(), *originalPair.second);
}

TEST(Multiset, MoveOperator) {
  s21::Multiset<int> a{13, 8, 17, 17, 1, 11, 17, 15, -1, 25};
  s21::Multiset<int> aTemp;
  aTemp = std::move(a);
  EXPECT_FALSE(aTemp.Empty());
}

TEST(Multiset, ConstuctorCopy) {
  s21::Multiset<int> a({1, 4, 5, 2, 7, 12, 14});
  s21::Multiset<int> b;
  b = a;
  EXPECT_EQ(a.Size(), b.Size());
}

TEST(Multiset, Decrement1) {
  s21::Multiset<int> a({1, 4, 5, 2, 7, 12, 14});
  a.Clear();
  s21::Multiset<int>::iterator myIt = a.Begin();
  ASSERT_ANY_THROW(--myIt);
}

TEST(Multiset, Decrement2) {
  s21::Multiset<int> a({5, 5, 5});
  s21::Multiset<int>::iterator it1 = a.End();
  EXPECT_ANY_THROW(*it1);
  EXPECT_ANY_THROW(it1.First());
  for (size_t i = 0; i < a.Size(); ++i) {
    --it1;
    EXPECT_TRUE(it1.First() == 5);
  }
}

TEST(Multiset, Increment1) {
  s21::Multiset<int> a({1, 4, 5, 2, 7, 12, 14});
  std::multiset<int> b({1, 4, 5, 2, 7, 12, 14});
  s21::Multiset<int>::iterator myIt = a.Begin();
  std::multiset<int>::iterator originalIt = b.begin();
  ++myIt;
  ++originalIt;
  EXPECT_EQ(myIt.First(), *originalIt);
}

TEST(Multiset, Increment2) {
  s21::Multiset<int> a({1, 2, 5, 2, 7, 2, 14});
  std::multiset<int> b({1, 2, 5, 2, 7, 2, 14});
  EXPECT_TRUE(a.Count(2) == b.count(2));
  EXPECT_TRUE(a.Count(13) == b.count(13));
}

TEST(Multiset, EqualOperator) {
  s21::Multiset<int> a({1, 4, 5});
  s21::Multiset<int>::iterator it1 = a.Begin();
  s21::Multiset<int>::iterator it2 = a.End();
  ++it1;
  --it2;
  --it2;
  EXPECT_TRUE(it1 == it2);
}

TEST(Multiset, Erase3) {
  s21::Multiset<int> a({10, 8, 5, 5, 5, 6, 3});
  std::multiset<int> b({10, 8, 5, 5, 5, 6, 3});
  s21::Multiset<int>::Iterator it1 = a.Begin();
  std::multiset<int>::iterator it2 = b.begin();
  ++it1;
  a.Erase(it1);
  it1 = a.Begin();
  ++it2;
  b.erase(it2);
  it2 = b.begin();
  for (size_t i = 0; i < a.Size(); i++) {
    EXPECT_TRUE(*it1 == *it2);
    ++it1;
    ++it2;
  }
}

TEST(Multiset, Erase4) {
  s21::Multiset<int> ms1({10, 10, 8});
  s21::Multiset<int> res({10, 8});
  ms1.Erase(++ms1.Begin());

  s21::Multiset<int>::iterator it1 = ms1.Begin();
  s21::Multiset<int>::iterator it2 = res.Begin();
  EXPECT_EQ(ms1.Size(), 2);
  for (size_t i = 0; i < res.Size(); i++) {
    EXPECT_EQ(*it1, *it2);
    ++it1;
    ++it2;
  }
}

TEST(Multiset, Erase5) {
  s21::Multiset<int> ms1({10, 8, 5, 6, 5});
  std::multiset<int> ms2({10, 8, 5, 6, 5});
  ms1.Erase(ms1.Begin());
  ms2.erase(ms2.begin());
  s21::Multiset<int>::iterator it1 = ms1.Begin();
  std::multiset<int>::iterator it2 = ms2.begin();
  for (size_t i = 0; i < ms1.Size(); i++) {
    EXPECT_EQ(*it1, *it2);
    ++it1;
    ++it2;
  }
}

TEST(Multiset, Erase6) {
  s21::Multiset<int> ms1({10, 18, 16, 16, 15});
  std::multiset<int> ms2({10, 18, 16, 16, 15});
  s21::Multiset<int>::iterator it1 = ms1.Begin();
  std::multiset<int>::iterator it2 = ms2.begin();
  ++it1;
  ++it1;
  ++it2;
  ++it2;
  ms1.Erase(it1);
  ms2.erase(it2);
  it1 = ms1.Begin();
  it2 = ms2.begin();
  for (size_t i = 0; i < ms1.Size(); i++) {
    EXPECT_EQ(*it1, *it2);  // key
    ++it1;
    ++it2;
  }
  EXPECT_TRUE(ms1.Find(16).Second() == 0);
}

TEST(Multiset, Erase7) {
  s21::Multiset<int> ms1({10, 8, 5, 1, 3});
  std::multiset<int> ms2({10, 8, 5, 1, 3});
  ms1.Erase(ms1.Find(5));
  ms2.erase(ms2.find(5));
  s21::Multiset<int>::iterator it1 = ms1.Begin();
  std::multiset<int>::iterator it2 = ms2.begin();
  for (size_t i = 0; i < ms1.Size(); i++) {
    EXPECT_EQ(*it1, *it2);
    ++it1;
    ++it2;
  }
}

TEST(Multiset, Erase8) {
  s21::Multiset<int> ms1({10, 8, 5, 7, 6});
  std::multiset<int> ms2({10, 8, 5, 7, 6});
  ms1.Erase(ms1.Find(5));
  ms2.erase(ms2.find(5));
  s21::Multiset<int>::iterator it1 = ms1.Begin();
  std::multiset<int>::iterator it2 = ms2.begin();
  for (size_t i = 0; i < ms1.Size(); i++) {
    EXPECT_EQ(*it1, *it2);
    ++it1;
    ++it2;
  }
}

TEST(Multiset, Erase9) {
  s21::Multiset<int> ms1({10, 10, 11});
  std::multiset<int> ms2({10, 10, 11});
  ms1.Erase(ms1.Begin());
  ms2.erase(ms2.begin());
  ms1.Erase(ms1.Begin());
  ms2.erase(ms2.begin());
  ms1.Erase(ms1.Begin());
  ms2.erase(ms2.begin());
  EXPECT_EQ(ms1.Size(), ms2.size());
  EXPECT_ANY_THROW((ms1.Begin()).Second());
}

TEST(Multiset, Emplace1) {
  s21::Multiset<int> ms1({1, 5, 6});
  std::multiset<int> ms2({1, 5, 6});
  ms1.Emplace();
  ms1.Emplace();
  ms2.emplace();
  ms2.emplace();
  s21::Multiset<int>::iterator it1 = ms1.Begin();
  std::multiset<int>::iterator it2 = ms2.begin();
  for (size_t i = 0; i < ms2.size(); i++) {
    EXPECT_EQ(*it1, *it2);
    ++it2;
    ++it1;
  }
  EXPECT_EQ(ms2.size(), ms1.Size());
}

TEST(Multiset, Emplace2) {
  s21::Multiset<int> ms1({1, 5, 6});
  std::multiset<int> ms2({1, 5, 6});
  ms1.Emplace(5);
  ms2.emplace(5);
  s21::Multiset<int>::iterator it1 = ms1.Begin();
  std::multiset<int>::iterator it2 = ms2.begin();
  for (size_t i = 0; i < ms2.size(); i++) {
    EXPECT_EQ(*it1, *it2);
    ++it2;
    ++it1;
  }
  EXPECT_EQ(ms2.size(), ms1.Size());
}

// ARRAY

TEST(Array, constructor_int) {
  s21::Array<int, 1> a;
  std::array<int, 1> b;
  EXPECT_EQ(a.Size(), b.size());
}

TEST(Array, constructor_int_2) {
  // throw of initializer_list
  ASSERT_ANY_THROW((s21::Array<int, 1>({0, 0})));
}

TEST(Array, constructor_double) {
  s21::Array<double, 10> a{12, 1, 6, 3, 100, 0, -1, -33, -89, 20};
  std::array<double, 10> b{1, 299, 9};
  EXPECT_EQ(a.Size(), b.size());
  EXPECT_EQ(a.MaxSize(), b.max_size());
}

TEST(Array, constructor_string) {
  s21::Array<std::string, 3> a{"kubik", "rubik", "ussr"};
  std::array<std::string, 3> b{"kubik", "rubik", "ussr"};
  EXPECT_EQ(a[0], b[0]);
  EXPECT_EQ(a[1], b[1]);
  EXPECT_EQ(a[2], b[2]);
}

TEST(Array, copy_constructor) {
  s21::Array<int, 10> a{12, 1, 6, 3, 100, 0, -1, -33, -89, 20};
  s21::Array<int, 10> a_copy(a);
  std::array<int, 10> b{12, 1, 6, 3, 100, 0, -1, -33, -89, 20};
  std::array<int, 10> b_copied(b);
  int i = 0;
  for (auto it = a.Begin(); it != a.End(); ++it) {
    EXPECT_EQ(a[i], b[i]);
    EXPECT_EQ(a_copy[i], b_copied[i]);
    ++i;
  }
}

TEST(Array, copy_constructor_string) {
  s21::Array<std::string, 10> a{"a", "b", "c"};
  s21::Array<std::string, 10> a_copy(a);
  std::array<std::string, 10> b{"a", "b", "c"};
  std::array<std::string, 10> b_copied(b);
  int i = 0;
  for (auto it = a.Begin(); it != a.End(); ++it) {
    EXPECT_EQ(a[i], b[i]);
    EXPECT_EQ(a_copy[i], b_copied[i]);
    ++i;
  }
}

TEST(Array, operator_string) {
  s21::Array<std::string, 10> a{"a", "b", "c"};
  s21::Array<std::string, 10> a_copy;
  a_copy = a;
  std::array<std::string, 10> b{"a", "b", "c"};
  std::array<std::string, 10> b_copied;
  b_copied = b;
  int i = 0;
  for (auto it = a.Begin(); it != a.End(); ++it) {
    EXPECT_EQ(a[i], b[i]);
    EXPECT_EQ(a_copy[i], b_copied[i]);
    ++i;
  }
}

TEST(Array, move_constructor_string) {
  s21::Array<std::string, 10> a{"a", "b", "c"};
  s21::Array<std::string, 10> a_moved(std::move(a));
  std::array<std::string, 10> b{"a", "b", "c"};
  std::array<std::string, 10> b_moved(std::move(b));
  for (size_t i = 0; i < a_moved.Size(); ++i) {
    EXPECT_EQ(a_moved[i], b_moved[i]);
  }
}

TEST(Array, move_constructor_1) {
  s21::Array<int, 10> a{12, 1, 6, 3, 100, 0, -1, -33, -89, 20};
  s21::Array<int, 10> a_moved(std::move(a));
  std::array<int, 10> b{12, 1, 6, 3, 100, 0, -1, -33, -89, 20};
  std::array<int, 10> b_moved(std::move(b));
  for (size_t i = 0; i < a_moved.Size(); ++i) {
    EXPECT_EQ(a_moved[i], b_moved[i]);
  }
}

TEST(Array, move_operator_string) {
  s21::Array<std::string, 10> a{"a", "b", "c"};
  s21::Array<std::string, 10> a_moved;
  a_moved = std::move(a);
  std::array<std::string, 10> b{"a", "b", "c"};
  std::array<std::string, 10> b_moved;
  b_moved = std::move(b);
  for (size_t i = 0; i < a_moved.Size(); ++i) {
    EXPECT_EQ(a_moved[i], b_moved[i]);
  }
}

TEST(Array, at) {
  s21::Array<int, 10> a{12, 1, 6, 3, 100, 0, -1, -33, -89, 20};
  std::array<int, 10> b{12, 1, 6, 3, 100, 0, -1, -33, -89, 20};
  ASSERT_EQ(a.At(1), a.At(1));
  ASSERT_EQ(a.At(0), b.at(0));
  EXPECT_THROW(a.At(11), std::exception);
}

TEST(Array, front) {
  s21::Array<int, 10> a{12, 1, 6, 3, 100, 0, -1, -33, -89, 20};
  std::array<int, 10> b{12, 1, 6, 3, 100, 0, -1, -33, -89, 20};
  EXPECT_EQ(a.Front(), b.front());
  a[0] = 8;
  b[0] = 8;
  EXPECT_EQ(a.Front(), b.front());
}

TEST(Array, back) {
  s21::Array<int, 10> a{12, 1, 6, 3, 100, 0, -1, -33, -89, 20};
  std::array<int, 10> b{12, 1, 6, 3, 100, 0, -1, -33, -89, 20};
  EXPECT_EQ(a.Back(), b.back());
}

TEST(Array, empty) {
  s21::Array<int, 10> a{12, 1, 6, 3, 100, 0, -1, -33, -89, 20};
  std::array<int, 10> b{12, 1, 6, 3, 100, 0, -1, -33, -89, 20};
  ASSERT_EQ(a.Empty(), b.empty());
}

TEST(Array, empty2) {
  s21::Array<int, 0> a;
  std::array<int, 0> b;
  ASSERT_EQ(a.Empty(), b.empty());
}

TEST(Array, plus_minus) {
  s21::Array<int, 10> a{12, 1, 6, 3, 100, 0, -1, -33, -89, 20};
  s21::Array<int, 10>::iterator my_it = a.Begin();
  std::array<int, 10> b{12, 1, 6, 3, 100, 0, -1, -33, -89, 20};
  std::array<int, 10>::iterator org_it = b.begin();
  while (my_it != a.End()) {
    ASSERT_EQ(*my_it++, *org_it++);
  }
  while (my_it != a.Begin()) {
    ASSERT_EQ(*--my_it, *--org_it);
  }
}

TEST(Array, begin_end) {
  s21::Array<int, 0> a;
  s21::Array<int, 0>::iterator my_it = a.Begin();
  ASSERT_EQ(my_it, a.End());
}

TEST(Array, data) {
  s21::Array<int, 1> a{6};
  s21::Array<int, 1>::iterator my_it = a.Data();
  ASSERT_EQ(*my_it, 6);
  ASSERT_EQ(my_it, a.Begin());
}

TEST(Array, fill) {
  s21::Array<int, 10> a;
  a.Fill(99);
  std::array<int, 10> b;
  b.fill(99);
  for (size_t i = 0; i < b.size(); ++i) {
    EXPECT_EQ(a[i], b[i]);
  }
}

TEST(Array, swap) {
  s21::Array<int, 10> a{0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  s21::Array<int, 10> a2{12, 1, 6, 3, 100, 0, -1, -33, -89, 20};
  a.Swap(a2);

  std::array<int, 10> c{0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  std::array<int, 10> c2{12, 1, 6, 3, 100, 0, -1, -33, -89, 20};
  c.swap(c2);

  for (size_t i = 0; i < c.size(); ++i) {
    EXPECT_EQ(a[i], c[i]);
  }
}

TEST(Array, operator_move) {
  s21::Array<int, 10> a{12, 1, 6, 3, 100, 0, -1, -33, -89, 20};
  s21::Array<int, 10> b{0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  a = b;
  for (size_t i = 0; i < b.Size(); ++i) {
    EXPECT_EQ(a[i], b[i]);
  }
}
TEST(Array, operator_move_exp) {
  s21::Array<std::string, 1> a{"q"};
  s21::Array<std::string, 1> b{"v"};
  a = b;
  EXPECT_EQ(a[0], b[0]);
}
int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}