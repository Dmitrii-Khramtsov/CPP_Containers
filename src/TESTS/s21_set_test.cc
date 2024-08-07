#include "test_runner.h"
#include <set>

TEST(SetTest, InsertMany) {
  s21::Set<int> set;

  auto results = set.insert_many(1, 2, 3);

  EXPECT_EQ(static_cast<int>(set.size()), 3);
  EXPECT_TRUE(results[0].second);
  EXPECT_TRUE(results[1].second);
  EXPECT_TRUE(results[2].second);

  EXPECT_NE(set.find(1), set.end());
  EXPECT_NE(set.find(2), set.end());
  EXPECT_NE(set.find(3), set.end());
}

TEST(set_test, constructor_1) {
  s21::Set<int> set1;
  std::set<int> set2;
  s21::Set<int> set3 = {1, 2, 3};
  s21::Set<int> set4 = set3;
  s21::Set<int> set5 = std::move(set4);
  const s21::Set<int> set_const = {1, 2, 3};
  const s21::Set<int> set_const2 = {1, 2, 3};
  auto it1 = set_const.begin();
  for (auto it2 = set_const2.begin(); it2 != set_const2.end(); it1++, it2++) {
    EXPECT_EQ(*it1, *it2);
  }
  const std::set<int> set_const3 = {1, 2, 3};
  auto it2 = set_const.end();
  it2--;
  auto it3 = set_const3.end();
  it3--;
  EXPECT_EQ(*it2, *it3);
  EXPECT_EQ(set1.size(), set2.size());
}

TEST(set_test, constructor_2) {
  s21::Set<char> set1 = {'a', '2', 'c'};
  std::set<char> set2 = {'a', '2', 'c'};
  auto it1 = set1.begin();
  for (auto it2 = set2.begin(); it2 != set2.end(); it1++, it2++) {
    EXPECT_EQ(*it1, *it2);
  }
}

TEST(set_test, constructor_3) {
  s21::Set<char> set1 = {'a', '2', 'c', '4'};
  std::set<char> set2 = {'a', '2', 'c', '4'};
  auto a = std::move(set1);
  auto b = std::move(set2);
  auto it1 = a.begin();
  EXPECT_EQ(set1.size(), set2.size());
  EXPECT_EQ(a.size(), b.size());
  for (auto it2 = b.begin(); it2 != b.end(); it1++, it2++) {
    EXPECT_EQ(*it1, *it2);
  }
}

TEST(set_test, constructor_4) {
  s21::Set<char> set1 = {'a', '2', 'c', '4'};
  std::set<char> set2 = {'a', '2', 'c', '4'};
  auto a = set1;
  auto b = set2;
  auto it1 = a.begin();
  EXPECT_EQ(set1.size(), set2.size());
  EXPECT_EQ(a.size(), b.size());
  for (auto it2 = b.begin(); it2 != b.end(); it1++, it2++) {
    EXPECT_EQ(*it1, *it2);
  }
}

TEST(set_test, end_1) {
  s21::Set<char> set1 = {'a', '2', 'c', '4'};
  std::set<char> set2 = {'a', '2', 'c', '4'};
  auto it1 = set1.end();
  auto it2 = set2.end();
  it1--, it2--;
  EXPECT_EQ(*it2, *it1);
}

TEST(set_test, begin_1) {
  s21::Set<char> set1 = {'a', '2', 'c', '4'};
  std::set<char> set2 = {'a', '2', 'c', '4'};
  auto it1 = set1.begin();
  auto it2 = set2.begin();
  EXPECT_EQ(*it1, *it2);
}

TEST(set_test, size_1) {
  s21::Set<char> set1 = {'a', '2', 'c', '4'};
  std::set<char> set2 = {'a', '2', 'c', '4'};
  EXPECT_EQ(set1.size(), set2.size());
}

TEST(set_test, size_2) {
  s21::Set<char> set1;
  std::set<char> set2;
  set1.insert('d');
  set2.insert('d');
  EXPECT_EQ(set1.size(), set2.size());
}

TEST(set_test, empty_clear) {
  s21::Set<char> set1 = {'a', '2', 'c', '4'};
  std::set<char> set2 = {'a', '2', 'c', '4'};
  EXPECT_EQ(set1.empty(), set2.empty());
  EXPECT_EQ(set1.size(), set2.size());
  set1.clear();
  set2.clear();
  EXPECT_EQ(set1.empty(), set2.empty());
  EXPECT_EQ(set1.size(), set2.size());
  s21::Set<char> empty1;
  std::set<char> empty2;
  empty1.clear();
  empty2.clear();
  EXPECT_EQ(empty1.size(), empty2.size());
  EXPECT_EQ(empty1.empty(), empty2.empty());
}

TEST(set_test, erase_1) {
  s21::Set<char> set1 = {'a', '2', 'c', '4'};
  std::set<char> set2 = {'a', '2', 'c', '4'};
  auto it1 = set1.begin();
  auto it2 = set2.begin();
  set1.erase(it1);
  set2.erase(it2);
  EXPECT_EQ(set1.size(), set2.size());
}

TEST(set_test, erase_2) {
  s21::Set<char> set1 = {'a', '2', 'c', '4'};
  std::set<char> set2 = {'a', '2', 'c', '4'};
  EXPECT_EQ(set1.size(), set2.size());
  auto it1 = set1.begin();
  auto it2 = set2.begin();
  set1.erase(it1);
  set2.erase(it2);
  EXPECT_EQ(set1.size(), set2.size());
}

TEST(set_test, swap) {
  s21::Set<char> set1 = {'a', '2', 'c', '4'};
  std::set<char> set2 = {'a', '2', 'c', '4'};
  s21::Set<char> a;
  std::set<char> b;
  set1.swap(a);
  set2.swap(b);
  EXPECT_EQ(set1.size(), set2.size());
  EXPECT_EQ(a.size(), b.size());
  auto it1 = a.begin();
  for (auto it2 = b.begin(); it2 != b.end(); it1++, it2++) {
    EXPECT_EQ(*it1, *it2);
  }
  set1 = {'a', '2', 'c', '4'};
  set2 = {'a', '2', 'c', '4'};
  set1.swap(a);
  set2.swap(b);
  EXPECT_EQ(set1.size(), set2.size());
  EXPECT_EQ(a.size(), b.size());
  it1 = a.begin();
  for (auto it2 = b.begin(); it2 != b.end(); it1++, it2++) {
    EXPECT_EQ(*it1, *it2);
  }
}

TEST(set_test, merge_1) {
  s21::Set<char> set1 = {'a', '2', 'c', '4'};
  std::set<char> set2 = {'a', '2', 'c', '4'};
  s21::Set<char> a = {'e', '6', 'g', '8'};
  std::set<char> b = {'e', '6', 'g', '8'};
  set1.merge(a);
  set2.merge(b);
  EXPECT_EQ(set1.size(), set2.size());
  EXPECT_EQ(a.size(), b.size());
  auto it1 = set1.begin();
  for (auto it2 = set2.begin(); it2 != set2.end(); it1++, it2++) {
    EXPECT_EQ(*it1, *it2);
  }
}

TEST(set_test, iterator_1) {
  s21::Set<char> set1 = {'a', '2', 'c', '4', 'e', '6'};
  s21::Set<char> set2 = {'a', '2', 'c', '4', 'e', '6'};
  auto it1 = set1.begin();
  auto it2 = set2.begin();
  for (int i = 0; i < 6; i++) {
    it1++, it2++;
  }
  it1 = set1.end();
  it2 = set2.end();
  for (int i = 0; i < 6; i++) {
    it1--, it2--;
  }
  EXPECT_EQ(*it1, *it2);
}

TEST(set_test, iterator_2) {
  s21::Set<char> set1 = {'a', '2', 'c', '4', 'e', '6'};
  s21::Set<char> set2 = {'a', '2', 'c', '4', 'e', '6'};
  auto it1 = set1.begin();
  auto it2 = set2.begin();
  it1++;
  EXPECT_EQ(it1 != it2, true);
  auto it3 = set1.end();
  auto it4 = set2.end();
  for (int i = 0; i < 3; i++) {
    it3--, it4--;
  }
  EXPECT_EQ(it3 == it4, false);
  EXPECT_EQ(*it3, *it4);
}

TEST(set_test, contains_1) {
  s21::Set<char> set1 = {'a', '2', 'c', '4'};
  s21::Set<char> set2 = {'a', '2', 'c', '4'};
  EXPECT_EQ(set1.contains('d'), false);
  EXPECT_EQ(set2.contains('a'), true);
}

TEST(RBTreeTest, erase2) {
  s21::Set<int> myTree = {200, 100, 300, 555, 22,  333, 111, 23,  334, 112, 25,
                          336, 145, 19,  376, 147, 13,  370, 102, 9,   399};

  auto it2 = myTree.find(399);
  myTree.erase(it2);

  EXPECT_EQ(myTree.size(), 20u);
  EXPECT_EQ(myTree.find(399), myTree.end()); // Узел должен быть удален
}

TEST(RBTreeTest, erase3) {
  s21::Set<int> myTree = {200, 100, 300, 555, 22,  333, 111, 23,  334, 112,
                          25,  336, 145, 19,  376, 147, 13,  370, 102, 9};

  auto it2 = myTree.find(9);
  myTree.erase(it2);

  EXPECT_EQ(myTree.size(), 19u);
  EXPECT_EQ(myTree.find(9), myTree.end()); 
}

TEST(RBTreeTest, erase4) {
  s21::Set<int> myTree = {200, 100, 300, 555, 22,  333, 111, 23,  334, 112,
                          25,  336, 145, 19,  376, 147, 13,  370, 102};

  auto it2 = myTree.find(102);
  myTree.erase(it2);

  EXPECT_EQ(myTree.size(), 18u);
  EXPECT_EQ(myTree.find(102), myTree.end()); 
}

TEST(RBTreeTest, erase5) {
  s21::Set<int> myTree = {200, 100, 300, 555, 22, 333, 111, 23, 334,
                          112, 25,  336, 145, 19, 376, 147, 13, 370};

  auto it2 = myTree.find(370);
  myTree.erase(it2);

  EXPECT_EQ(myTree.size(), 17u);
  EXPECT_EQ(myTree.find(370), myTree.end()); 
}

TEST(RBTreeTest, erase6) {
  s21::Set<int> myTree = {200, 100, 300, 555, 22, 333, 111, 23, 334,
                          112, 25,  336, 145, 19, 376, 147, 13};

  auto it2 = myTree.find(13);
  myTree.erase(it2);

  EXPECT_EQ(myTree.size(), 16u);
  EXPECT_EQ(myTree.find(13), myTree.end()); 
}

TEST(RBTreeTest, erase7) {
  s21::Set<int> myTree = {200, 100, 300, 555, 22,  333, 111, 23,
                          334, 112, 25,  336, 145, 19,  376, 147};

  auto it2 = myTree.find(147);
  myTree.erase(it2);

  EXPECT_EQ(myTree.size(), 15u);
  EXPECT_EQ(myTree.find(147), myTree.end()); 
}

TEST(RBTreeTest, erase8) {
  s21::Set<int> myTree = {200, 100, 300, 555, 22,  333, 111, 23,
                          334, 112, 25,  336, 145, 19,  376};

  auto it2 = myTree.find(376);
  myTree.erase(it2);

  EXPECT_EQ(myTree.size(), 14u);
  EXPECT_EQ(myTree.find(376), myTree.end()); 
}

TEST(RBTreeTest, erase9) {
  s21::Set<int> myTree = {200, 100, 300, 555, 22,  333, 111,
                          23,  334, 112, 25,  336, 145, 19};

  auto it2 = myTree.find(19);
  myTree.erase(it2);

  EXPECT_EQ(myTree.size(), 13u);
  EXPECT_EQ(myTree.find(19), myTree.end()); 
}

TEST(RBTreeTest, erase10) {
  s21::Set<int> myTree = {200, 100, 300, 555, 22,  333, 111,
                          23,  334, 112, 25,  336, 145};

  auto it2 = myTree.find(145);
  myTree.erase(it2);

  EXPECT_EQ(myTree.size(), 12u);
  EXPECT_EQ(myTree.find(145), myTree.end()); 
}

TEST(RBTreeTest, erase11) {
  s21::Set<int> myTree = {200, 100, 300, 555, 22, 333,
                          111, 23,  334, 112, 25, 336};

  auto it2 = myTree.find(336);
  myTree.erase(it2);

  EXPECT_EQ(myTree.size(), 11u);
  EXPECT_EQ(myTree.find(336), myTree.end()); 
}

TEST(RBTreeTest, erase12) {
  s21::Set<int> myTree = {200, 100, 300, 555, 22, 333, 111, 23, 334, 112, 25};

  auto it2 = myTree.find(25);
  myTree.erase(it2);

  EXPECT_EQ(myTree.size(), 10u);
  EXPECT_EQ(myTree.find(25), myTree.end()); 
}

TEST(RBTreeTest, erase13) {
  s21::Set<int> myTree = {200, 100, 300, 555, 22, 333, 111, 23, 334, 112};

  auto it2 = myTree.find(112);
  myTree.erase(it2);

  EXPECT_EQ(myTree.size(), 9u);
  EXPECT_EQ(myTree.find(112), myTree.end()); 
}

TEST(RBTreeTest, erase14) {
  s21::Set<int> myTree = {200, 100, 300, 555, 22, 333, 111, 23, 334};

  auto it2 = myTree.find(334);
  myTree.erase(it2);

  EXPECT_EQ(myTree.size(), 8u);
  EXPECT_EQ(myTree.find(334), myTree.end()); 
}

TEST(RBTreeTest, erase15) {
  s21::Set<int> myTree = {200, 100, 300, 555, 22, 333, 111, 23};

  auto it2 = myTree.find(23);
  myTree.erase(it2);

  EXPECT_EQ(myTree.size(), 7u);
  EXPECT_EQ(myTree.find(23), myTree.end()); 
}

TEST(RBTreeTest, erase16) {
  s21::Set<int> myTree = {200, 100, 300, 555, 22, 333, 111};

  auto it2 = myTree.find(111);
  myTree.erase(it2);

  EXPECT_EQ(myTree.size(), 6u);
  EXPECT_EQ(myTree.find(111), myTree.end()); 
}

TEST(RBTreeTest, erase17) {
  s21::Set<int> myTree = {200, 100, 300, 555, 22, 333};

  auto it2 = myTree.find(333);
  myTree.erase(it2);

  EXPECT_EQ(myTree.size(), 5u);
  EXPECT_EQ(myTree.find(333), myTree.end()); 
}

TEST(RBTreeTest, erase18) {
  s21::Set<int> myTree = {200, 100, 300, 555, 22};

  auto it2 = myTree.find(22);
  myTree.erase(it2);

  EXPECT_EQ(myTree.size(), 4u);
  EXPECT_EQ(myTree.find(22), myTree.end()); 
}

TEST(RBTreeTest, erase19) {
  s21::Set<int> myTree = {200, 100, 300, 555};

  auto it2 = myTree.find(555);
  myTree.erase(it2);

  EXPECT_EQ(myTree.size(), 3u);
  EXPECT_EQ(myTree.find(555), myTree.end()); 
}

TEST(RBTreeTest, erase20) {
  s21::Set<int> myTree = {200, 100, 300};

  auto it2 = myTree.find(300);
  myTree.erase(it2);

  EXPECT_EQ(myTree.size(), 2u);
  EXPECT_EQ(myTree.find(300), myTree.end()); 
}

TEST(RBTreeTest, erase21) {
  s21::Set<int> myTree = {11, 6, 12, 10, 13, 14, 7, 5, 9};

  auto it2 = myTree.find(7);
  myTree.erase(it2);

  EXPECT_EQ(myTree.size(), 8u);
  EXPECT_EQ(myTree.find(7), myTree.end()); 
}
