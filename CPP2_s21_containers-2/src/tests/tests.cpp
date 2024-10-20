#include <gtest/gtest.h>

#include <vector>
#include <list>
#include <queue>
#include <stack>

#include "../s21_containers/map/s21_map.h"
#include "../s21_containers/s21_containers.h"
#include "../s21_containers/set/s21_set.h"

// VECTOR

TEST(Vector, ReferenceAt) {
  s21::Vector<int> a{100, 4, 3, 5, 8, 11, 0};
  std::vector<int> b{100, 4, 3, 5, 8, 11, 0};
  EXPECT_EQ(a.At(3), b.at(3));
  EXPECT_EQ(a.At(0), b.at(0));
  EXPECT_EQ(a.At(6), b.at(6));
  EXPECT_THROW(a.At(7), std::exception);
}

TEST(Vector, ReferenceFront) {
  s21::Vector<int> a{100, 4, 3, 5, 8, 11, 0};
  std::vector<int> b{100, 4, 3, 5, 8, 11, 0};
  EXPECT_EQ(a.Front(), b.front());
}

TEST(Vector, IteratorData) {
  s21::Vector<int> a{100, 4, 3, 5, 8, 11, 0};
  std::vector<int> b{100, 4, 3, 5, 8, 11, 0};
  EXPECT_EQ(*a.Data(), *b.data());
}

TEST(Vector, Empty) {
  s21::Vector<std::string> a{"hi",        "ha",   "hb",  "ht",
                             "highvideo", "houl", "hppp"};
  std::vector<std::string> b{"hi",        "ha",   "hb",  "ht",
                             "highvideo", "houl", "hppp"};
  EXPECT_EQ(a.Empty(), b.empty());
}

TEST(Vector, MaxSize) {
  s21::Vector<double> a{100, 4, 3, 5, 8, 11, 0};
  std::vector<double> b{100, 4, 3, 5, 8, 11, 0};
  EXPECT_EQ(a.MaxSize(), b.max_size());
}

TEST(Vector, Reserve1) {
  s21::Vector<int> a{100, 4, 3, 5, 8, 11, 0};
  std::vector<int> b{100, 4, 3, 5, 8, 11, 0};
  a.Reserve(14);
  b.reserve(14);
  EXPECT_EQ(a.Capacity(), b.capacity());
  EXPECT_THROW(a.Reserve(a.MaxSize() + 1), std::exception);
}

TEST(Vector, Reserve2) {
  s21::Vector<int> a;
  std::vector<int> b;
  a.Clear();
  b.clear();
  a.ShrinkToFit();
  b.shrink_to_fit();
  s21::Vector<int>::iterator my_it = a.Begin();
  std::vector<int>::iterator org_it = b.begin();
  a.Insert(my_it, 1);
  b.insert(org_it, 1);
  EXPECT_EQ(a[0], b[0]);
}

TEST(Vector, Erase1) {
  s21::Vector<std::string> a;
  std::vector<std::string> b;
  a.PushBack("a");
  a.PushBack("b");

  b.push_back("a");
  b.push_back("b");

  s21::Vector<std::string>::iterator my_it = a.Begin();
  std::vector<std::string>::iterator org_it = b.begin();
  ++my_it;
  ++org_it;
  a.Erase(my_it);
  b.erase(org_it);
  EXPECT_EQ(a[0], b[0]);
}

TEST(Vector, Erase2) {
  s21::Vector<int> a;
  std::vector<int> b;
  a.PushBack(12);
  a.PushBack(45);
  a.PushBack(31);
  a.PushBack(30);

  b.push_back(12);
  b.push_back(45);
  b.push_back(31);
  b.push_back(30);

  s21::Vector<int>::iterator my_it = a.Begin();
  std::vector<int>::iterator org_it = b.begin();

  a.Erase(my_it + 3);
  b.erase(org_it + 3);
  EXPECT_EQ(a[2], b[2]);
}

TEST(Vector, PopBack) {
  s21::Vector<int> a;
  std::vector<int> b;
  a.PushBack(12);
  a.PushBack(45);
  a.PushBack(31);
  a.PushBack(30);
  a.PopBack();
  a.PopBack();

  b.push_back(12);
  b.push_back(45);
  b.push_back(31);
  b.push_back(30);
  b.pop_back();
  b.pop_back();

  for (size_t i = 0; i < a.Size(); i++) {
    EXPECT_EQ(a[i], b[i]);
  }
}

TEST(Vector, Swap) {
  s21::Vector<int> a{4, 4, 4};
  s21::Vector<int> aTemp{1, 1, 1};
  std::vector<int> b{4, 4, 4};
  std::vector<int> bTemp{1, 1, 1};
  a.Swap(aTemp);
  b.swap(bTemp);
  for (size_t i = 0; i < a.Size(); i++) {
    EXPECT_EQ(a[i], b[i]);
    EXPECT_EQ(aTemp[i], bTemp[i]);
  }
}

TEST(Vector, SizeN) {
  s21::Vector<int> a(5);
  EXPECT_EQ(a.Capacity(), 5);
  EXPECT_THROW(s21::Vector<int> a(-2), std::exception);
}

TEST(Vector, OperatorEqual) {
  s21::Vector<int> a{4, 4, 4};
  s21::Vector<int> aTemp = a;
  for (size_t i = 0; i < a.Size(); i++) {
    EXPECT_EQ(a[i], aTemp[i]);
  }
}

TEST(Vector, MoveConstructor) {
  s21::Vector<int> a{4, 4, 4};
  s21::Vector<int> aTemp(std::move(a));
  for (size_t i = 0; i < aTemp.Size(); i++) {
    EXPECT_EQ(aTemp[i], 4);
  }
}

TEST(Vector, SecondTime) {
  s21::Vector<std::string> a{"hi",        "ha",   "hb",  "ht",
                             "highvideo", "houl", "hppp"};
  std::vector<std::string> b{"hi",        "ha",   "hb",  "ht",
                             "highvideo", "houl", "hppp"};
  a = s21::Vector<std::string>{"jjjj"};
  b = {"jjjj"};
  EXPECT_EQ(a[0], b[0]);
  EXPECT_EQ(a.Size(), b.size());
  s21::Vector<int> a_int{4, 4, 4};
  a_int = s21::Vector<int>{1};
  EXPECT_EQ(a_int.Size(), 1);
}

TEST(Vector, EmplaceBack) {
  s21::Vector<int> a;
  a.EmplaceBack(7, 7, 7);
  for (size_t i = 0; i < a.Size(); i++) {
    EXPECT_EQ(a[i], 7);
  }
}

TEST(Vector, EmplaceBack1) {
  s21::Vector<int> a;
  a.EmplaceBack();
  for (size_t i = 0; i < a.Size(); i++) {
    EXPECT_EQ(a[i], 0);
  }
}

TEST(Vector, EmplaceBack2) {
  s21::Vector<int> a;
  s21::Vector<int> b{1, 2, 5, 3, 4, 6, 8};
  a.EmplaceBack(1, 2, 5, 3, 4, 6, 8);
  for (size_t i = 0; i < a.Size(); i++) {
    EXPECT_EQ(a[i], b[i]);
  }
}

TEST(Vector, Emplace) {
  s21::Vector<int> a;
  a.Emplace(a.Begin());
  for (size_t i = 0; i < a.Size(); i++) {
    EXPECT_EQ(a[i], 0);
  }
}

TEST(Vector, Emplace1) {
  s21::Vector<std::string> a;
  a.Emplace(a.Begin());
  for (size_t i = 0; i < a.Size(); i++) {
    EXPECT_EQ(a[i], "\0");
  }
}

TEST(Vector, Emplace2) {
  s21::Vector<int> a{1, 2};
  s21::Vector<int> b{1, 39, 39, 39, 2};
  a.Emplace(a.Begin() + 1, 39, 39, 39);
  for (size_t i = 0; i < a.Size(); i++) {
    EXPECT_EQ(a[i], b[i]);
  }
}

TEST(Vector, Emplace3) {
  s21::Vector<std::string> a{"c", "c"};
  s21::Vector<std::string> b{"c",   "dg b",  "dsfs", "etv", "ert",
                             "sdf", "dssff", "3hk",  "c"};
  a.Emplace(a.Begin() + 1, "3hk", "dssff", "sdf", "ert", "etv", "dsfs", "dg b");
  for (size_t i = 0; i < a.Size(); i++) {
    EXPECT_EQ(a[i], b[i]);
  }
}

// LIST

template <typename value_type>
bool compare_lists(s21::list<value_type> s21_list,
                   std::list<value_type> std_list) {
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
  try {
    s21::list<int> s21_list(-1);
  } catch (std::out_of_range const& err) {
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

// QUEUE

template <typename value_type>
bool compare_queues(s21::queue<value_type> s21_queue,
                    std::queue<value_type> std_queue) {
  bool result = true;
  if (s21_queue.size() == std_queue.size()) {
    while (!s21_queue.empty() && !std_queue.empty()) {
      if (s21_queue.front() != std_queue.front()) {
        result = false;
        break;
      }
      s21_queue.pop();
      std_queue.pop();
    }
  } else {
    result = false;
  }
  return result;
}

TEST(Queue, CompareQueues1) {
  s21::queue<int> s21_queue{1, 2, 3};
  std::queue<int> std_queue;
  std_queue.push(1);
  std_queue.push(2);
  std_queue.push(3);
  EXPECT_TRUE(compare_queues(s21_queue, std_queue));
  std_queue.push(10);
  EXPECT_FALSE(compare_queues(s21_queue, std_queue));
}

TEST(Queue, CompareQueues2) {
  s21::queue<int> s21_queue{1, 2, 3};
  std::queue<int> std_queue;
  std_queue.push(1);
  std_queue.push(2);
  std_queue.push(10);
  EXPECT_FALSE(compare_queues(s21_queue, std_queue));
}

// STACK

TEST(Stack, ConstructorInitializerList) {
  s21::Stack<int> s21_stack{1, 2, 3};
  EXPECT_EQ(s21_stack.Top(), 3);
}

TEST(Stack, Top) {
  std::initializer_list<int> il{};
  s21::Stack<int> s21_stack{il};
  EXPECT_THROW(s21_stack.Top(), std::out_of_range);
}

// MAP

TEST(Map, At1) {
  s21::Map<int, std::string> m1 = s21::Map<int, std::string>{{0, "pear"}};
  std::map<int, std::string> m2 = {{0, "pear"}};
  ASSERT_EQ(m1.At(0), m2.at(0));
}

TEST(Map, At2) {
  s21::Map<int, std::string> m1 = s21::Map<int, std::string>{{1, "pear"}};
  EXPECT_THROW(m1.At(24), std::exception);
}

TEST(Map, SquareBrackets) {
  s21::Map<int, std::string> m1 =
      s21::Map<int, std::string>{{1, "pear"}, {4, "apple"}};
  std::map<int, std::string> m2 = {{1, "pear"}, {4, "apple"}};
  m1[2] = "cherry";
  m2[2] = "cherry";
  ASSERT_EQ(m1[2], m2[2]);
}

TEST(Map, Insert1) {
  s21::Map<int, std::string> m1 = s21::Map<int, std::string>{{4, "apple"}};
  std::map<int, std::string> m2 = {{4, "apple"}};
  std::pair<int, std::string> k = {10, "cherry"};
  auto it_m1 = m1.Insert(k);
  auto it_m2 = m2.insert(k);
  EXPECT_EQ((*(it_m1.first)).first, (*(it_m2.first)).first);
  EXPECT_EQ((*(it_m1.first)).second, (*(it_m2.first)).second);
  s21::Map<int, std::string>::iterator it1 = m1.Begin();
  std::map<int, std::string>::iterator it2 = m2.begin();
  for (size_t i = 0; i < m1.Size(); i++) {
    EXPECT_EQ((*it1).first, (*it2).first);
    EXPECT_EQ((*it1).second, (*it2).second);
    ++it1;
    ++it2;
  }
}

TEST(Map, Insert2) {
  s21::Map<char, double> m1 = s21::Map<char, double>{{'s', 125.365}};
  std::map<char, double> m2 = {{'s', 125.365}};
  std::pair<char, double> k = {'a', 488.02255};
  auto it_m1 = m1.Insert(k);
  auto it_m2 = m2.insert(k);
  EXPECT_EQ((*(it_m1.first)).first, (*(it_m2.first)).first);
  EXPECT_EQ((*(it_m1.first)).second, (*(it_m2.first)).second);
  s21::Map<char, double>::iterator it1 = m1.Begin();
  std::map<char, double>::iterator it2 = m2.begin();
  for (size_t i = 0; i < m1.Size(); i++) {
    EXPECT_EQ((*it1).first, (*it2).first);
    EXPECT_EQ((*it1).second, (*it2).second);
    ++it1;
    ++it2;
  }
}

TEST(Map, Insert3) {
  s21::Map<char, double> m1;
  std::map<char, double> m2;
  auto it_m1 = m1.Insert(std::pair<char, double>('n', 0.20251));
  auto it_m2 = m2.insert(std::pair<char, double>('n', 0.20251));
  EXPECT_EQ((*(it_m1.first)).first, (*(it_m2.first)).first);
  EXPECT_EQ((*(it_m1.first)).second, (*(it_m2.first)).second);
  s21::Map<char, double>::iterator it1 = m1.Begin();
  std::map<char, double>::iterator it2 = m2.begin();
  for (size_t i = 0; i < m1.Size(); i++) {
    EXPECT_EQ((*it1).first, (*it2).first);
    EXPECT_EQ((*it1).second, (*it2).second);
    ++it1;
    ++it2;
  }
}

TEST(Map, Insert2Parameters) {
  s21::Map<int, std::string> m1 = s21::Map<int, std::string>{{4, "apple"}};
  std::map<int, std::string> m2 = {{4, "apple"}};
  auto it_m1 = m1.Insert(10, "cherry");
  auto it_m2 = m2.insert({10, "cherry"});
  EXPECT_EQ(it_m1.first.First(), it_m2.first->first);
  EXPECT_EQ(it_m1.first.Second(), it_m2.first->second);
  s21::Map<int, std::string>::iterator it1 = m1.Begin();
  std::map<int, std::string>::iterator it2 = m2.begin();
  for (size_t i = 0; i < m1.Size(); i++) {
    EXPECT_EQ(it1.First(), it2->first);
    EXPECT_EQ(it1.Second(), it2->second);
    ++it1;
    ++it2;
  }
}

TEST(Map, InsertOrAssign) {
  s21::Map<int, char> m1 = s21::Map<int, char>{{1, 'n'}, {2, 'a'}};
  std::map<int, char> m2{{1, 'n'}, {2, 'a'}};
  auto it_m1 = m1.InsertOrAssign(1, 'v');
  auto it_m2 = m2.insert_or_assign(1, 'v');
  EXPECT_EQ(it_m1.first.First(), it_m2.first->first);
  EXPECT_EQ(it_m1.first.Second(), it_m2.first->second);
  m1.InsertOrAssign(10, 'v');
  m2.insert_or_assign(10, 'v');
  s21::Map<int, char>::iterator it1 = m1.Begin();
  std::map<int, char>::iterator it2 = m2.begin();
  for (size_t i = 0; i < m1.Size(); i++) {
    EXPECT_EQ(it1.First(), it2->first);
    EXPECT_EQ(it1.Second(), it2->second);
    ++it1;
    ++it2;
  }
}

TEST(Map, Erase1) {
  s21::Map<int, std::string> m1 = s21::Map<int, std::string>{{4, "apple"}};
  std::map<int, std::string> m2 = {{4, "apple"}};
  s21::Map<int, std::string>::iterator it_m1 = m1.Begin();
  std::map<int, std::string>::iterator it_m2 = m2.begin();
  m1.Erase(it_m1);
  m2.erase(it_m2);
  EXPECT_EQ(m1.Empty(), m2.empty());
}

TEST(Map, Erase2) {
  s21::Map<int, char> m1 =
      s21::Map<int, char>{{10, 'n'}, {8, 'a'}, {5, 'n'}, {6, 't'}};
  std::map<int, char> m2{{10, 'n'}, {8, 'a'}, {5, 'n'}, {6, 't'}};
  m1.Erase(m1.Begin());
  m2.erase(m2.begin());
  s21::Map<int, char>::iterator it1 = m1.Begin();
  std::map<int, char>::iterator it2 = m2.begin();
  for (size_t i = 0; i < m1.Size(); i++) {
    EXPECT_EQ(it1.First(), it2->first);
    EXPECT_EQ(it1.Second(), it2->second);
    ++it1;
    ++it2;
  }
}

TEST(Map, Erase3) {
  s21::Map<int, char> m1 = s21::Map<int, char>{
      {15, 'n'}, {8, 'a'}, {5, 'n'}, {6, 't'}, {10, 'j'}, {12, 'd'}, {13, 'e'}};
  std::map<int, char> m2{{15, 'n'}, {8, 'a'},  {5, 'n'}, {6, 't'},
                         {10, 'j'}, {12, 'd'}, {13, 'e'}};
  s21::Map<int, char>::iterator it1 = m1.End();
  std::map<int, char>::iterator it2 = m2.end();
  --it1;
  --it1;
  --it1;
  m1.Erase(it1);
  --it2;
  --it2;
  --it2;
  m2.erase(it2);
  it1 = m1.Begin();
  it2 = m2.begin();
  for (size_t i = 0; i < m1.Size(); i++) {
    EXPECT_EQ(it1.First(), it2->first);
    EXPECT_EQ(it1.Second(), it2->second);
    ++it1;
    ++it2;
  }
}

TEST(Map, Erase4) {
  s21::Map<int, char> m1 =
      s21::Map<int, char>{{10, 'n'}, {8, 'a'}, {5, 'n'}, {6, 't'}, {3, 'y'}};
  std::map<int, char> m2{{10, 'n'}, {8, 'a'}, {5, 'n'}, {6, 't'}, {3, 'y'}};
  s21::Map<int, char>::iterator it1 = m1.Begin();
  ++it1;
  std::map<int, char>::iterator it2 = m2.begin();
  ++it2;
  m1.Erase(it1);
  m2.erase(it2);
  it1 = m1.Begin();
  it2 = m2.begin();
  for (size_t i = 0; i < m1.Size(); i++) {
    EXPECT_EQ(it1.First(), it2->first);
    EXPECT_EQ(it1.Second(), it2->second);
    ++it1;
    ++it2;
  }
}

TEST(Map, Erase5) {
  s21::Map<int, char> m1 =
      s21::Map<int, char>{{10, 'n'}, {8, 'a'}, {5, 'n'}, {1, 't'}, {3, 'y'}};
  std::map<int, char> m2{{10, 'n'}, {8, 'a'}, {5, 'n'}, {1, 't'}, {3, 'y'}};
  s21::Map<int, char>::iterator it1 = m1.Begin();
  ++it1;
  ++it1;
  ++it1;
  std::map<int, char>::iterator it2 = m2.begin();
  ++it2;
  ++it2;
  ++it2;
  m1.Erase(it1);
  m2.erase(it2);
  it1 = m1.Begin();
  it2 = m2.begin();
  for (size_t i = 0; i < m1.Size(); i++) {
    EXPECT_EQ(it1.First(), it2->first);
    EXPECT_EQ(it1.Second(), it2->second);
    ++it1;
    ++it2;
  }
}

TEST(Map, EraseEmpty) {
  s21::Map<int, std::string> m1;
  m1.Erase(m1.Begin());
  EXPECT_EQ(m1.Empty(), 1);
}

TEST(Map, EraseRoot1) {
  s21::Map<int, int> m1{{10, 3}, {15, 1}, {16, 2}, {0, 1}, {5, 3}, {3, 2}};
  s21::Map<int, int> res{{0, 1}, {3, 2}, {5, 3}, {15, 1}, {16, 2}};
  s21::Map<int, int>::iterator it1 = m1.Begin();
  s21::Map<int, int>::iterator it2 = res.Begin();
  ++it1;
  ++it1;
  ++it1;
  m1.Erase(it1);
  it1 = m1.Begin();
  for (; it1 != m1.End(); ++it1) {
    EXPECT_EQ((*it1).first, (*it2).first);
    EXPECT_EQ((*it1).second, (*it2).second);
    ++it2;
  }
}

TEST(Map, EraseRoot2) {
  s21::Map<int, int> m1{{10, 3}, {11, 4}};
  s21::Map<int, int> res{{11, 4}};
  m1.Erase(m1.Begin());
  s21::Map<int, int>::iterator it1 = m1.Begin();
  s21::Map<int, int>::iterator it2 = res.Begin();
  EXPECT_EQ(m1.Size(), 1);
  EXPECT_EQ((*it1).first, (*it2).first);
}

TEST(Map, Merge) {
  s21::Map<int, char> m1_1 = s21::Map<int, char>{{1, 'n'}, {2, 'a'}};
  s21::Map<int, char> m1_2{{1, 'l'}, {3, 'k'}};
  std::map<int, char> m2_1 = {{1, 'n'}, {2, 'a'}};
  std::map<int, char> m2_2{{1, 'l'}, {3, 'k'}};
  m1_1.Merge(m1_2);
  m2_1.merge(m2_2);
  s21::Map<int, char>::iterator it1 = m1_1.Begin();
  std::map<int, char>::iterator it2 = m2_1.begin();
  for (size_t i = 0; i < m1_1.Size(); i++) {
    EXPECT_EQ(it1.First(), it2->first);    // key
    EXPECT_EQ(it1.Second(), it2->second);  // value;
    ++it1;
    ++it2;
  }
  s21::Map<int, char>::iterator it1_2 = m1_2.Begin();
  std::map<int, char>::iterator it2_2 = m2_2.begin();
  for (size_t i = 0; i < m1_2.Size(); i++) {
    EXPECT_EQ(it1_2.First(), it2_2->first);    // key
    EXPECT_EQ(it1_2.Second(), it2_2->second);  // value;
    ++it1;
    ++it2;
  }
}

TEST(Map, MoveConstructor) {
  s21::Map<int, int> m{{1, 2}, {5, 6}};
  s21::Map<int, int> res{{1, 2}, {5, 6}};
  s21::Map<int, int> m_copy(std::move(m));
  s21::Map<int, int>::iterator it1 = res.Begin();
  s21::Map<int, int>::iterator it2 = m_copy.Begin();
  for (size_t i = 0; i < res.Size(); i++) {
    EXPECT_EQ(it1.First(), it2.First());    // key
    EXPECT_EQ(it1.Second(), it2.Second());  // value;
    ++it1;
    ++it2;
  }
}

TEST(Map, DecrementBeginEmpty) {
  s21::Map<int, int> m1;
  s21::Map<int, int>::iterator it1 = m1.Begin();
  ASSERT_ANY_THROW(--it1);
  ASSERT_ANY_THROW((*it1).first);
  ASSERT_ANY_THROW((*it1).second);
  it1 = m1.Begin();
  ASSERT_ANY_THROW(it1.First());
  ASSERT_ANY_THROW(it1.Second());
}

TEST(Map, IteratorMinus) {
  s21::Map<int, double> m1{{1, 2}, {5, 6}};
  std::map<int, double> m2{{1, 2}, {5, 6}};
  s21::Map<int, double>::iterator it1 = m1.End();
  std::map<int, double>::iterator it2 = m2.end();
  --it1;
  --it1;
  --it2;
  --it2;
  EXPECT_EQ((*it1).first, (*it2).first);
  EXPECT_EQ((*it1).second, (*it2).second);
}

TEST(Map, IteratorEqual) {
  s21::Map<int, std::string> ma{{1, "apple"}, {5, "pear"}, {10, "banana"}};
  s21::Map<int, std::string>::iterator it1 = ma.Begin();
  s21::Map<int, std::string>::iterator it2 = ma.End();
  ++it1;
  --it2;
  --it2;
  EXPECT_TRUE(it1 == it2);
}

TEST(Map, CopyConstructor1) {
  s21::Map<int, int> m2;
  s21::Map<int, int> m1(m2);
  EXPECT_EQ(m2.Size(), m1.Size());
}

TEST(Map, CopyConstructor2) {
  s21::Map<int, int> m2;
  s21::Map<int, int> m1{{3, 2}};
  s21::Map<int, int> res{{3, 2}};
  m2 = std::move(m1);
  EXPECT_EQ(m2.Size(), 1);
  for (auto it1 = m2.Begin(), it2 = res.Begin(); it1 != m2.End(); ++it1) {
    EXPECT_EQ((*it1).first, (*it2).first);
    EXPECT_EQ((*it1).second, (*it2).second);
    ++it2;
  }
}

TEST(Map, CopyConstructor3) {
  s21::Map<int, std::string> m2{{5, "apple"}};
  s21::Map<int, std::string> m1(m2);
  EXPECT_EQ(m2.Size(), m1.Size());
}

TEST(Map, CopyTree3) {
  s21::Map<int, int> m2{{2, 3}, {5, 3}};
  s21::Map<int, int> m1;
  m1.~Map();
  m2 = m1;
  EXPECT_EQ(m2.Size(), m1.Size());
}

TEST(Map, Emplace1) {
  s21::Map<int, int> m1{{1, 2}, {5, 6}};
  s21::Map<int, int> res{{1, 2}, {5, 6}, {0, 0}, {3, 4}, {7, 7}};
  m1.Emplace(std::pair<int, int>(0, 0), std::pair<int, int>(3, 4),
             std::pair<int, int>(7, 7));
  EXPECT_EQ(m1[0], res[0]);
  EXPECT_EQ(m1[3], res[3]);
  EXPECT_EQ(res.Size(), m1.Size());
}

TEST(Map, Emplace2) {
  s21::Map<int, int> m;
  m.Emplace();
  EXPECT_EQ(m.Size(), 1);
}

TEST(Map, Emplace3) {
  s21::Map<int, int> m1{{1, 1}, {2, 2}};
  std::map<int, int> m2{{1, 1}, {2, 2}};
  m1.Emplace(std::pair(2, 3));
  m2.emplace(std::pair(2, 3));
  s21::Map<int, int>::iterator it1 = m1.Begin();
  std::map<int, int>::iterator it2 = m2.begin();

  for (size_t i = 0; i < m1.Size(); i++) {
    EXPECT_EQ(it1.First(), it1.Second());
    EXPECT_EQ(it2->first, it2->second);
    ++it1;
    ++it2;
  }
  EXPECT_EQ(m1.Size(), m2.size());
}

// SET

TEST(Set, Erase1) {
  s21::Set<int> a{13, 8, 1, 11, 15, 25, 2, 13, 123, 23, 26, 14, 16};
  std::set<int> std_a{13, 8, 1, 11, 15, 25, 2, 13, 123, 23, 26, 14, 16};
  a.Erase(a.Find(15));
  a.Erase(a.Find(1));
  a.Erase(a.Find(11));
  std_a.erase(std_a.find(15));
  std_a.erase(std_a.find(1));
  std_a.erase(std_a.find(11));
  s21::Set<int>::iterator my_itTemp = a.Begin();
  std::set<int>::iterator origina_itTemp = std_a.begin();
  while (my_itTemp != a.End()) {
    EXPECT_EQ((*my_itTemp), *origina_itTemp);
    ++my_itTemp;
    ++origina_itTemp;
  }
}

TEST(Set, Erase2) {
  s21::Set<int> a{13, 8, 1, 11, 15, 25, 2, 13, 123, 23, 26, 14, 16};
  std::set<int> std_a{13, 8, 1, 11, 15, 25, 2, 13, 123, 23, 26, 14, 16};
  a.Erase(a.Find(26));
  a.Erase(a.Find(23));
  std_a.erase(std_a.find(26));
  std_a.erase(std_a.find(23));
  s21::Set<int>::iterator my_itTemp = a.Begin();
  std::set<int>::iterator origina_itTemp = std_a.begin();
  while (my_itTemp != a.End()) {
    EXPECT_EQ((*my_itTemp), *origina_itTemp);
    ++my_itTemp;
    ++origina_itTemp;
  }
}

TEST(Set, Erase3) {
  s21::Set<int> a{13, 15, 17};
  std::set<int> std_a{13, 15, 17};
  a.Erase(a.Find(15));
  std_a.erase(std_a.find(15));
  s21::Set<int>::iterator my_itTemp = a.Begin();
  std::set<int>::iterator origina_itTemp = std_a.begin();
  while (my_itTemp != a.End()) {
    EXPECT_EQ((*my_itTemp), *origina_itTemp);
    ++my_itTemp;
    ++origina_itTemp;
  }
}

TEST(Set, Erase4) {
  s21::Set<int> a{1, 2, 3};
  std::set<int> std_a{1, 2, 3};
  a.Erase(a.Find(1));
  std_a.erase(std_a.find(1));
  s21::Set<int>::iterator my_itTemp = a.Begin();
  std::set<int>::iterator origina_itTemp = std_a.begin();
  while (my_itTemp != a.End()) {
    EXPECT_EQ((*my_itTemp), *origina_itTemp);
    ++my_itTemp;
    ++origina_itTemp;
  }
}

TEST(Set, Merge) {
  s21::Set<int> a{13, 8, 17, 1, 11, 15, 25};
  s21::Set<int> aTemp{12, 3, 2};
  std::set<int> std_a{13, 8, 17, 1, 11, 15, 25};
  std::set<int> std_aTemp{12, 3, 2};
  a.Merge(aTemp);
  std_a.merge(std_aTemp);
  s21::Set<int>::iterator my_it = a.Begin();
  std::set<int>::iterator origina_it = std_a.begin();
  for (size_t i = 0; i < a.Size(); i++) {
    EXPECT_EQ((*my_it), *origina_it);
    ++my_it;
    ++origina_it;
  }
}

TEST(Set, CopyConstructor1) {
  s21::Set<int> a{13, 8, 17, 1, 11, 15, 25};
  s21::Set<int> copySet(a);
  s21::Set<int>::iterator my_it = a.Begin();
  s21::Set<int>::iterator copyIt = copySet.Begin();
  for (size_t i = 0; i < a.Size(); i++) {
    EXPECT_EQ((*my_it), (*copyIt));
    ++my_it;
    ++copyIt;
  }
}

TEST(Set, CopyConstructor2) {
  s21::Set<int> s2;
  s21::Set<int> s1{3, 2};
  s2 = s1;
  EXPECT_EQ(s2.Size(), s1.Size());
}

TEST(Set, MoveConstructor1) {
  s21::Set<int> a{13, 8, 17, 1, 11, 15, 25};
  s21::Set<int> aTemp{13, 8, 17, 1, 11, 15, 25};
  s21::Set<int> copySet(std::move(a));
  s21::Set<int>::iterator my_it = aTemp.Begin();
  s21::Set<int>::iterator copyIt = copySet.Begin();
  for (size_t i = 0; i < a.Size(); i++) {
    EXPECT_EQ((*my_it), (*copyIt));
    ++my_it;
    ++copyIt;
  }
}

TEST(Set, MoveConstructor2) {
  s21::Set<int> s2;
  s21::Set<int> s1{3, 2};
  s21::Set<int> res{3, 2};
  s2 = std::move(s1);
  EXPECT_EQ(s2.Size(), res.Size());
  for (auto it1 = s2.Begin(), it2 = res.Begin(); it1 != s2.End(); ++it1) {
    EXPECT_EQ(*it1, *it2);
    ++it2;
  }
}

TEST(Set, DecrementBeginEmpty) {
  s21::Set<int> s1;
  s21::Set<int>::iterator it1 = s1.Begin();
  ASSERT_ANY_THROW(--it1);
  ASSERT_ANY_THROW(*it1);
}

TEST(Set, IteratorBonus) {
  s21::Set<int> a{1, 4, 5, 2, 7, 12, 14};
  std::set<int> std_a{1, 4, 5, 2, 7, 12, 14};
  s21::Set<int>::iterator my_it = a.Begin();
  std::set<int>::iterator origina_it = std_a.begin();
  ++my_it;
  ++my_it;
  ++origina_it;
  ++origina_it;
  --my_it;
  --my_it;
  --origina_it;
  --origina_it;
  EXPECT_EQ((*my_it), *origina_it);
}

TEST(Set, IteratorEqual) {
  s21::Set<int> a{1, 5, 10};
  s21::Set<int>::iterator it1 = a.Begin();
  s21::Set<int>::iterator it2 = a.End();
  ++it1;
  --it2;
  --it2;
  EXPECT_TRUE(it1 == it2);
}

TEST(Set, Emplace1) {
  s21::Set<int> a;
  auto myPair = a.Emplace();
  EXPECT_EQ(myPair.Size(), 1);
}

TEST(Set, Emplace2) {
  s21::Set<int> a{21};
  auto myPair = a.Emplace(21);
  EXPECT_FALSE(myPair[0].second);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
