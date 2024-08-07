#include <set>
#include "test_runner.h"

TEST(MultiSetTest, InsertMany) {
    s21::MultiSet<int> multiset;

    auto results = multiset.insert_many(1, 2, 3, 1, 2, 3);

    EXPECT_EQ(static_cast<int>(multiset.size()), 6);
    EXPECT_EQ(static_cast<int>(multiset.count(1)), 2);
    EXPECT_EQ(static_cast<int>(multiset.count(2)), 2);
    EXPECT_EQ(static_cast<int>(multiset.count(3)), 2);
}

TEST(multiset_test, constructor_1) {
    s21::MultiSet<char> multiset1 {'1', '2', '3', '4', '5'};
    std::multiset<char> multiset2 {'1', '2', '3', '4', '5'};
    auto it1 = multiset1.begin();
    EXPECT_EQ(multiset1.size(), multiset2.size());
    for (auto it2 = multiset2.begin(); it2 != multiset2.end(); it1++, it2++) {
        EXPECT_EQ(*it1, *it2);
    }
}

TEST(multiset_test, constructor_2) {
    s21::MultiSet<char> multiset1 = {'1', '2', '3'};
    std::multiset<char> multiset2 = {'1', '2', '3'};
    auto it1 = multiset1.begin();
    EXPECT_EQ(multiset1.size(), multiset2.size());
    for (auto it2 = multiset2.begin(); it2 != multiset2.end(); it1++, it2++) {
        EXPECT_EQ(*it1, *it2);
    }
}

TEST(multiset_test, constructor_3) {
    s21::MultiSet<char> multiset1 = {'1', '2', '3', '4', '5'};
    std::multiset<char> multiset2 = {'1', '2', '3', '4', '5'};
    EXPECT_EQ(multiset1.size(), multiset2.size());
    auto it1 = multiset1.begin();
    for (auto it2 = multiset2.begin(); it2 != multiset2.end(); it1++, it2++) {
        EXPECT_EQ(*it1, *it2);
    }
}

TEST(multiset_test, constructor_4) {
    s21::MultiSet<char> multiset1 = {'1', '2', '3', '4', '5'};
    std::multiset<char> multiset2 = {'1', '2', '3', '4', '5'};
    auto a = multiset1;
    auto b = multiset2;
    auto it1 = a.begin();
    for (auto it2 = b.begin(); it2 != b.end(); it1++, it2++) {
        EXPECT_EQ(*it1, *it2);
    }
    EXPECT_EQ(a.size(), b.size());
    it1 = multiset1.begin();
    EXPECT_EQ(multiset1.size(), multiset2.size());
    for (auto it2 = multiset2.begin(); it2 != multiset2.end(); it1++, it2++) {
        EXPECT_EQ(*it1, *it2);
    }
}

TEST(multiset_test, constructor_5) {
    s21::MultiSet<char> multiset1 = {'1', '2', '3', '4', '5'};
    std::multiset<char> multiset2 = {'1', '2', '3', '4', '5'};
    auto a = multiset1;
    auto b = multiset2;
    auto it1 = a.begin();
    for (auto it2 = b.begin(); it2 != b.end(); it1++, it2++) {
        EXPECT_EQ(*it1, *it2);
    }
    EXPECT_EQ(a.size(), b.size());
    it1 = multiset1.begin();
    for (auto it2 = multiset2.begin(); it2 != multiset2.end(); it1++, it2++) {
        EXPECT_EQ(*it1, *it2);
    }
    EXPECT_EQ(multiset1.size(), multiset2.size());
}

TEST(multiset_test, constructor_7) {
    s21::MultiSet<char> multiset1 = {'1', '2', '3', '4', '5'};
    std::multiset<char> multiset2 = {'1', '2', '3', '4', '5'};
    auto a = std::move(multiset1);
    auto b = std::move(multiset2);
    auto it1 = a.begin();
    EXPECT_EQ(a.size(), b.size());
    EXPECT_EQ(multiset1.size(), multiset2.size());

    for (auto it2 = b.begin(); it2 != b.end(); it1++, it2++) {
        EXPECT_EQ(*it1, *it2);
    }
}


TEST(multiset_test, constructor_8) {
    s21::MultiSet<std::string> multiset1 = {"test", "cases", "hello"};
    std::multiset<std::string> multiset2 = {"test", "cases", "hello"};
    auto it1 = multiset1.begin();
    for (auto it2 = multiset2.begin(); it2 != multiset2.end(); it1++, it2++) {
        EXPECT_EQ(*it1, *it2);
    }
}

TEST(multiset_test, begin) {
    s21::MultiSet<char> multiset1 = {'1', '2', '3', '4', '5'};
    std::multiset<char> multiset2 = {'1', '2', '3', '4', '5'};
    auto it1 = multiset1.begin();
    auto it2 = multiset2.begin();
    EXPECT_EQ(*it1, *it2);
}


TEST(multiset_test, end) {
    s21::MultiSet<char> multiset1 = {'1', '2', '3', '4', '5'};
    std::multiset<char> multiset2 = {'1', '2', '3', '4', '5'};
    auto it1 = multiset1.end();
    auto it2 = multiset2.end();
    it1--;
    it2--;
    EXPECT_EQ(*it1, *it2);
}


TEST(multiset_test, empty) {
    s21::MultiSet<char> multiset1;
    std::multiset<char> multiset2;
    EXPECT_EQ(multiset1.empty(), multiset2.empty());
    s21::MultiSet<char> multiset3 = {'1', '2', '3', '4', '5'};
    std::multiset<char> multiset4 = {'1', '2', '3', '4', '5'};
    EXPECT_EQ(multiset4.empty(), multiset3.empty());
    multiset3.clear();
    multiset4.clear();
    EXPECT_EQ(multiset3.empty(), multiset4.empty());

}

TEST(multiset_test, insert) {
    s21::MultiSet<char> multiset1;
    std::multiset<char> multiset2;
    for (int i = 0; i < 10; i++) {
        EXPECT_EQ(*(multiset1.insert(i)), *(multiset2.insert(i)));
    }
    EXPECT_EQ(multiset1.size(), multiset2.size());
}

TEST(multiset_test, size) {
    s21::MultiSet<char> multiset1;
    std::multiset<char> multiset2;
    s21::MultiSet<char> multiset3 = {'1', '2', '3', '4', '5'};
    std::multiset<char> multiset4 = {'1', '2', '3', '4', '5'};
    EXPECT_EQ(multiset1.size(), multiset2.size());
    EXPECT_EQ(multiset3.size(), multiset4.size());
    multiset3.clear();
    multiset4.clear();
    EXPECT_EQ(multiset3.size(), multiset4.size());

}


TEST(multiset_test, clear) {
    s21::MultiSet<char> multiset1 = {'1', '2', '3', '4', '5'};
    std::multiset<char> multiset2 = {'1', '2', '3', '4', '5'};
    multiset1.clear();
    multiset2.clear();
    EXPECT_EQ(multiset1.empty(), multiset2.empty());
}

TEST(multiset_test, clear2) {
    s21::MultiSet<char> multiset1;
    std::multiset<char> multiset2;
    multiset1.clear();
    multiset2.clear();
    EXPECT_EQ(multiset1.empty(), multiset2.empty());
}


TEST(multiset_test, init_1) {
  s21::MultiSet<double> v = {-3, 1, -5, 42, 2, -6, 8, 20, 1, 1, 20};
  std::multiset<double> vc = {-3, 1, -5, 42, 2, -6, 8, 20, 1, 1, 20};

  ASSERT_EQ(*v.begin(), *vc.begin());
  ASSERT_EQ(v.empty(), vc.empty());
  ASSERT_EQ(v.size(), vc.size());
}

TEST(multiset_test, init_2) {
  s21::MultiSet<double> v = {-3, 1, -5, 42, 2, -6, 8, 20, 1, 1, 20};
  std::multiset<double> vc = {-3, 1, -5, 42, 2, -6, 8, 20, 1, 1, 20};
  auto x = v.begin();
  auto y = vc.begin();

  for (; x != v.end(); ++x, ++y) {
    ASSERT_EQ(*x, *y);
  }
}


TEST(multiset_test, insert_erase) {
  s21::MultiSet<double> v = {2, -3, 20, -5, 1, -6, 8, 42, 26, 1, 1, 1, 8, 8, 8};
  std::multiset<double> vc = {2,  -3, 20, -5, 1, -6, 8, 42,
                              26, 1,  1,  1,  8, 8,  8};
  v.insert(15);
  vc.insert(15);
  v.erase(v.begin());
  vc.erase(vc.begin());
  auto x = v.begin();
  auto y = vc.begin();
  for (; x != v.end(); ++x, ++y) {
    ASSERT_EQ(*x, *y);
  }
}

TEST(multiset_test, lower_bound) {
  s21::MultiSet<double> v = {2, -3, 20, -5, 1, -6, 8, 42, 26, 1, 1, 1};
  s21::MultiSet<double>::iterator x = v.lower_bound(8);
  --x;
  ASSERT_EQ(*x, 2);
}

TEST(multiset_test, rand) {
  s21::MultiSet<double> v;
  for (int i = 0; i <= 100; i++) {
      v.insert(rand() % 1001);
  }

  for (int i = 0; i <= 100; i++) {
      auto it = v.find(rand() % 1001);
      v.erase(it);
  }
  EXPECT_EQ(v.size(), v.size());
}

TEST(multiset_test, upper_bound) {
  s21::MultiSet<double> v = {2, -3, 20, -5, 1, -6, 8, 42, 26, 1, 1, 1, 8, 8, 8};
  auto x = v.upper_bound(8);
  --x;
  ASSERT_EQ(*x, 8);
}

TEST(multiset_test, cont) {
  s21::MultiSet<double> v = {2, -3, 20, -5, 1, -6, 8, 42, 26, 1, 1, 1, 8, 8, 8};
  EXPECT_EQ(static_cast<int>(v.count(1)), 4);
}

TEST(multiset_test, find4) {
  s21::MultiSet<double> v = {2, -3, 20, -5, 1, -6, 8, 42, 26, 1, 1, 1, 8, 8, 8};
  EXPECT_EQ(*(v.find(1)), 1);
}

TEST(multiset_test, contains) {
  s21::MultiSet<double> v = {2, -3, 20, -5, 1, -6, 8, 42, 26, 1, 1, 1, 8, 8, 8};
  EXPECT_EQ(v.contains(1), true);
}


TEST(multiset_test, swap_3) {
  s21::MultiSet<double> v = {-3, 1, -5, 42, 2, -6, 8, 20, 26};
  std::multiset<double> vc = {-3, 1, -5, 42, 2, -6, 8, 20, 26};
  s21::MultiSet<double> v1 = {100, 200, 300, 400, 500};
  std::multiset<double> vc1 = {100, 200, 300, 400, 500};
  v.swap(v1);
  vc.swap(vc1);
  v.max_size();

  auto x = v.begin();
  auto y = vc.begin();
  for (; x != v.end(); ++x, ++y) {
    EXPECT_EQ(*x, *y);
  }
}

TEST(multiset_test, merge_4) {
  s21::MultiSet<double> v = {-3, 1, -5, 42, 2, -6, 8, 20, 26};
  s21::MultiSet<double> v1 = {100, 200, 300, 400, 500};
  s21::MultiSet<double> vc = {-3, 1,  -5,  42,  2,   -6,  8,
                              20, 26, 100, 200, 300, 400, 500};
  v.merge(v1);

  auto x = v.begin();
  auto y = vc.begin();
  for (; x != v.end(); ++x, ++y) {
    ASSERT_EQ(*x, *y);
  }
}

TEST(multiset_test, insert3) {
    s21::MultiSet<char> multiset1 = {'1', '2', '3', '4', '5'};
    std::multiset<char> multiset2 = {'1', '2', '3', '4', '5'};
    for (int i = 0; i < 5; i++) {
        multiset1.insert(i);
        multiset2.insert(i);
    }
    auto it1 = multiset1.begin();
    for (auto it2 = multiset2.begin(); it2 != multiset2.end(); it1++, it2++) {
        EXPECT_EQ(*it1, *it2);
    }
    EXPECT_EQ(multiset1.size(), multiset2.size());
}

TEST(multiset_test, erase2) {
    s21::MultiSet<char> multiset1 = {'1', '2', '3', '4', '5'};
    std::multiset<char> multiset2 = {'1', '2', '3', '4', '5'};
    EXPECT_EQ(multiset1.size(), multiset2.size());
    auto it1 = multiset1.begin();
    auto it2 = multiset2.begin();
    multiset1.erase(it1);
    multiset2.erase(it2);
    it1 = multiset1.begin();
    it2 = multiset2.begin();
    for (; it2 != multiset2.end(); it1++, it2++) EXPECT_EQ(*it1, *it2);
    EXPECT_EQ(multiset1.size(), multiset2.size());
}

TEST(multiset_test, swap2) {
    s21::MultiSet<char> multiset1 = {'1', '2', '3', '4', '5'};
    std::multiset<char> multiset2 = {'1', '2', '3', '4', '5'};
    s21::MultiSet<char> a = {'1', '2', '3', '4', '5'};
    std::multiset<char> b = {'1', '2', '3', '4', '5'};
    multiset1.swap(a);
    multiset2.swap(b);
    EXPECT_EQ(multiset1.size(), multiset2.size());
    EXPECT_EQ(a.size(), b.size());
    auto it1 = multiset1.begin();
    auto it11 = a.begin();
    auto it2 = multiset2.begin();
    auto it22 = b.begin();
    for (; it2 != multiset2.end(); it1++, it2++) EXPECT_EQ(*it1, *it2);
    for (; it22 != b.end(); it11++, it22++) EXPECT_EQ(*it11, *it22);
}

TEST(multiset_test, merge1) {
    s21::MultiSet<char> multiset1 = {'1', '2', '3', '4', '5'};
    std::multiset<char> multiset2 = {'1', '2', '3', '4', '5'};
    s21::MultiSet<char> a = {'1', '2', '3', '4', '5'};
    std::multiset<char> b = {'1', '2', '3', '4', '5'};
    multiset1.merge(a);
    multiset2.merge(b);
    auto it1 = multiset1.begin();
    for (auto it2 = multiset2.begin(); it2 != multiset2.end(); it1++, it2++) EXPECT_EQ(*it1, *it2);
}

TEST(multiset_test, merge2) {
    s21::MultiSet<char> multiset1 = {'1', '2', '3', '4', '5'};
    std::multiset<char> multiset2 = {'1', '2', '3', '4', '5'};
    s21::MultiSet<char> a;
    std::multiset<char> b;
    multiset1.merge(a);
    multiset2.merge(b);
    auto it1 = multiset1.begin();
    for (auto it2 = multiset2.begin(); it2 != multiset2.end(); it1++, it2++) EXPECT_EQ(*it1, *it2);
}

TEST(multiset_test, count1) {
    s21::MultiSet<char> multiset1 = {'1', '2', '3', '4', '5'};
    std::multiset<char> multiset2 = {'1', '2', '3', '4', '5'};
    EXPECT_EQ(multiset1.count(1), multiset2.count(1));
    EXPECT_EQ(multiset1.count(2), multiset2.count(2));
    EXPECT_EQ(multiset1.count(6), multiset2.count(6));
}

TEST(multiset_test, count2) {
    s21::MultiSet<char> multiset1;
    std::multiset<char> multiset2;
    EXPECT_EQ(multiset1.count(1), multiset2.count(1));
    EXPECT_EQ(multiset1.count(2), multiset2.count(2));
    EXPECT_EQ(multiset1.count(6), multiset2.count(6));
}

TEST(multiset_test, count3) {
    s21::MultiSet<char> multiset1 = {1, 1, 1, 1, 1, 1, 1, 1};
    std::multiset<char> multiset2 = {1, 1, 1, 1, 1, 1, 1, 1};
    EXPECT_EQ(multiset1.count(1), multiset2.count(1));
    EXPECT_EQ(multiset1.count(2), multiset2.count(2));
    EXPECT_EQ(multiset1.count(6), multiset2.count(6));
}

TEST(multiset_test, find3) {
    s21::MultiSet<char> multiset1 = {1, 1, 1, 1, 1, 1, 1, 1};
    std::multiset<char> multiset2 = {1, 1, 1, 1, 1, 1, 1, 1};
    EXPECT_EQ(*(multiset1.find(1)), *(multiset2.find(1)));
}

TEST(multiset_test, contains2) {
    s21::MultiSet<char> multiset1;
    EXPECT_EQ(multiset1.contains(1), false);
    EXPECT_EQ(multiset1.contains(2), false);
    EXPECT_EQ(multiset1.contains(6), false);
}

TEST(multiset_test, contains3) {
    s21::MultiSet<char> multiset1 = {1, 1, 1, 1, 1, 1, 1, 1};
    std::multiset<char> multiset2 = {1, 1, 1, 1, 1, 1, 1, 1};
    EXPECT_EQ(multiset1.contains(1), true);
    EXPECT_EQ(multiset1.contains(2), false);
    EXPECT_EQ(multiset1.contains(6), false);
}

TEST(multiset_test, lower_bound1) {
    s21::MultiSet<char> multiset1 = {'1', '2', '3', '4', '5'};
    std::multiset<char> multiset2 = {'1', '2', '3', '4', '5'};
    auto it1 = multiset1.lower_bound(9);
    auto it2 = multiset2.lower_bound(9);
    EXPECT_EQ(*(it1), *(it2));
    it1 = multiset1.lower_bound(1);
    it2 = multiset2.lower_bound(1);
    EXPECT_EQ(*(it1), *(it2));
    it1 = multiset1.lower_bound(2);
    it2 = multiset2.lower_bound(2);
    EXPECT_EQ(*(it1), *(it2));
}

TEST(multiset_test, at) {
    s21::MultiSet<int> multiset1 = {1, 2, 3, 4, 5};
    std::multiset<int> multiset2 = {1, 2, 3, 4, 5};
    EXPECT_EQ(multiset1.count(1), multiset2.count(1));
    EXPECT_EQ(multiset1.count(5), multiset2.count(5));
}

TEST(multiset_test, operator) {
    s21::MultiSet<int> multiset1 = {1, 2, 3, 4, 5};
    std::multiset<int> multiset2 = {1, 2, 3, 4, 5};
    EXPECT_EQ(multiset1.count(1), multiset2.count(1));
    EXPECT_EQ(multiset1.count(5), multiset2.count(5));
}

TEST(multiset_test, data) {
    s21::MultiSet<int> multiset1 = {1, 2, 3, 4, 5};
    std::multiset<int> multiset2 = {1, 2, 3, 4, 5};
    EXPECT_EQ(multiset1.count(1), multiset2.count(1));
    EXPECT_EQ(multiset1.count(5), multiset2.count(5));
}

TEST(multiset_test, begin_end) {
    s21::MultiSet<int> multiset1 = {1, 2, 3, 4, 5};
    std::multiset<int> multiset2 = {1, 2, 3, 4, 5};
    auto it1 = multiset1.begin();
    auto it2 = multiset2.begin();
    EXPECT_EQ(*it1, *it2);
    auto it3 = multiset1.end();
    auto it4 = multiset2.end();
    it3--;
    it4--;
    EXPECT_EQ(*it3, *it4);
}

TEST(multiset_test, swap) {
    s21::MultiSet<int> multiset1 = {1, 2, 3, 4, 5};
    std::multiset<int> multiset2 = {1, 2, 3, 4, 5};
    s21::MultiSet<int> multiset3;
    std::multiset<int> multiset4;
    multiset1.swap(multiset3);
    multiset2.swap(multiset4);
    EXPECT_EQ(multiset1.size(), multiset2.size());
    EXPECT_EQ(multiset3.size(), multiset4.size());
    auto it1 = multiset3.begin();
    auto it2 = multiset4.begin();
    for (; it1 != multiset3.end() && it2 != multiset4.end(); ++it1, ++it2) {
        EXPECT_EQ(*it1, *it2);
    }
    s21::MultiSet<int> multiset5 = {6, 7, 8, 9, 0};
    std::multiset<int> multiset6 = {6, 7, 8, 9, 0};
    multiset5.swap(multiset3);
    multiset6.swap(multiset4);
    EXPECT_EQ(multiset5.size(), multiset6.size());
    EXPECT_EQ(multiset3.size(), multiset4.size());
}

TEST(multiset_test, fill) {
    s21::MultiSet<int> multiset1;
    std::multiset<int> multiset2;
    multiset1.insert(100);
    multiset2.insert(100);
    EXPECT_EQ(multiset1.size(), multiset2.size());
    auto it1 = multiset1.begin();
    auto it2 = multiset2.begin();
    for (; it1 != multiset1.end() && it2 != multiset2.end(); ++it1, ++it2) {
        EXPECT_EQ(*it1, *it2);
    }
}

TEST(multiset_test, constructor_throw) {
    try {
        s21::MultiSet<int> a = {1, 2, 3, 4, 5, 6};
    } catch(std::runtime_error &error) {
        EXPECT_EQ(error.what(), std::string("s21::MultiSet: Initializer_list's size is not the same as the multiset's size!"));
    }
}

TEST(multiset_test, at_const) {
    const s21::MultiSet<int> a = {1, 2, 3, 4, 5, 6};
    EXPECT_EQ(static_cast<int>(a.count(1)), 1);
    EXPECT_EQ(static_cast<int>(a.count(6)), 1);
}

TEST(multiset_test, operator_square_brackets) {
    const s21::MultiSet<int> a = {1, 2, 3, 4, 5, 6};
    EXPECT_EQ(static_cast<int>(a.count(1)), 1);
    EXPECT_EQ(static_cast<int>(a.count(6)), 1);
}

TEST(multiset_test, end_const) {
    const s21::MultiSet<int> a = {1, 2, 3, 4, 5, 6};
    for (auto el : a) {
        EXPECT_EQ(el, el);
    }
}
