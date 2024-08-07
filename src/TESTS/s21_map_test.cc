#include <map>
#include "test_runner.h"


TEST(map_test, InsertMany) {
    s21::Map<int, std::string> map;

    auto results = map.insert_many(std::make_pair(1, "one"), std::make_pair(2, "two"), std::make_pair(3, "three"));

    EXPECT_EQ(static_cast<int>(map.size()), 3);
    EXPECT_TRUE(results[0].second);
    EXPECT_TRUE(results[1].second);
    EXPECT_TRUE(results[2].second);

    EXPECT_EQ(map.find(1)->second, "one");
    EXPECT_EQ(map.find(2)->second, "two");
    EXPECT_EQ(map.find(3)->second, "three");
}


TEST(map_test, Modifier_Insert) {
  s21::Map<char, int> s21_map_1 = {{'b', 228}, {'c', 1337}};
  s21::Map<char, int> s21_map_2 = {{'b', 228}, {'c', 1337}, {'d', 322}, {'a', 5}};
  s21_map_1 = s21_map_2;
}

TEST(map_test, insert_or_assign) {
  s21::Map<char, int> s21_map_1 = {{'b', 228}, {'c', 1337}};
  s21_map_1.insert_or_assign('b', 138);
  s21_map_1.insert_or_assign('u', 638);
  EXPECT_EQ(s21_map_1['b'], 138);
  EXPECT_EQ(s21_map_1['u'], 638);
}


TEST(map_test, erase_3) {
  std::pair<int, int> pair1{10, 10};
  std::pair<int, int> pair2{5, 5};
  std::pair<int, int> pair3{15, 15};
  std::pair<int, int> pair4{4, 4};
  std::pair<int, int> pair5{18, 18};
  std::pair<int, int> pair6{13, 13};
  std::pair<int, int> pair7{16, 16};

  s21::Map<int, int> s21_map = {pair1, pair2, pair3, pair4,
                                pair5, pair6, pair7};

  auto it = s21_map.begin();
  it++;
  it++;
  it++;
  it++;
  s21_map.erase(it);
  EXPECT_EQ((*s21_map.begin()).first, 4);
  // EXPECT_EQ((*s21_map.end()).first, 0);
  EXPECT_EQ(s21_map.size(), 6U);

  it = s21_map.begin();
  s21_map.erase(it);
  EXPECT_EQ((*s21_map.begin()).first, 5);
  // EXPECT_EQ((*s21_map.end()).first, 0);
  EXPECT_EQ(s21_map.size(), 5U);

  it = s21_map.begin();
  it++;
  s21_map.erase(it);
  EXPECT_EQ((*s21_map.begin()).first, 5);
  // EXPECT_EQ((*s21_map.end()).first, 0);
  EXPECT_EQ(s21_map.size(), 4U);

  it = s21_map.end();
  --it;
  s21_map.erase(it);
  EXPECT_EQ((*s21_map.begin()).first, 5);
  // EXPECT_EQ((*s21_map.end()).first, 0);
  EXPECT_EQ(s21_map.size(), 3U);

  it = s21_map.begin();
  it++;
  s21_map.erase(it);

  it = s21_map.begin();
  it++;
  s21_map.erase(it);

  it = s21_map.begin();
  s21_map.erase(it);

  EXPECT_EQ(s21_map.size(), 0U);
}

TEST(map_erase, case2) {
  std::pair<int, int> pair1{30, 30};
  std::pair<int, int> pair2{1543, 1543};

  s21::Map<int, int> s21_map = {pair1, pair2};

  auto it = s21_map.begin();
  it++;
  s21_map.erase(it);
  it = s21_map.begin();
  s21_map.erase(it);

  EXPECT_EQ(s21_map.size(), 0U);
}

TEST(map_test, erase_4) {
  std::pair<std::string, int> pair1{"hello", 1};
  std::pair<std::string, int> pair2{"hi", 2};
  std::pair<std::string, int> pair3{"hola-hola", 2};
  std::pair<std::string, int> pair4{"hola", 3};
  std::pair<std::string, int> pair5{"hello, there", 1};

  s21::Map<std::string, int> s21_map = {pair1, pair2, pair3, pair4, pair5};

  auto it = s21_map.end();
  --it;
  s21_map.erase(it);
  EXPECT_EQ((*(--s21_map.end())).first, "hola");
  EXPECT_EQ(s21_map.size(), 4U);

  it = s21_map.end();
  --it;
  s21_map.erase(it);
  EXPECT_EQ((*(--s21_map.end())).first, "hi");
  EXPECT_EQ(s21_map.size(), 3U);

  s21_map.insert(pair3);
  s21_map.insert(pair4);
  it = s21_map.end();
  --it;
  s21_map.erase(it);
  EXPECT_EQ((*(--s21_map.end())).first, "hola");
  EXPECT_EQ(s21_map.size(), 4U);
}

TEST(map_test, erase_6) {
  std::pair<double, int> pair1{22.2, 1};
  std::pair<double, int> pair2{44.48, 1};
  std::pair<double, int> pair3{12.4457, 2};
  std::pair<double, int> pair4{1.44, 3};

  s21::Map<double, int> s21_map = {pair1, pair2, pair3, pair4};

  auto it = s21_map.begin();
  it--;
  s21_map.erase(it);
  it = s21_map.begin();
  ++it;
  EXPECT_EQ((*it).first, 12.4457);
  EXPECT_EQ(s21_map.size(), 4U);
}

TEST(map_test, erase_7) {
  std::pair<double, int> pair1{22.2, 1};
  std::pair<double, int> pair2{44.48, 1};
  std::pair<double, int> pair3{12.4457, 2};
  std::pair<double, int> pair4{6.84, 2};
  std::pair<double, int> pair5{1.44, 3};

  s21::Map<double, int> s21_map = {pair1, pair2, pair3, pair4, pair5};

  auto it = s21_map.begin();
  ++it;
  ++it;
  ++it;
  s21_map.erase(it);
  it = s21_map.begin();
  ++it;
  ++it;
  ++it;
  EXPECT_EQ((*it).first, 44.48);
  EXPECT_EQ(s21_map.size(), 4U);
}

TEST(map_test, erase_8) {
  std::pair<double, int> pair1{22.2, 1};
  std::pair<double, int> pair2{12.4457, 2};
  std::pair<double, int> pair3{56.84, 2};
  std::pair<double, int> pair4{941.44, 3};
  std::pair<double, int> pair5{44.48, 1};

  s21::Map<double, int> s21_map = {pair1, pair2, pair3, pair4, pair5};

  auto it = s21_map.begin();
  ++it;
  s21_map.erase(it);
  it = s21_map.begin();
  ++it;
  EXPECT_EQ((*it).first, 44.48);
  EXPECT_EQ(s21_map.size(), 4U);
}

TEST(map_test, brackets) {
  std::pair<int, double> pair1{9, 1.4};
  std::pair<int, double> pair2{23, 2.77};
  std::pair<int, double> pair3{98, 3.9};
  std::pair<int, double> pair11{78, 3.9};
  std::pair<int, double> pair22{88, 3.9};
  std::pair<int, double> pair33{108, 3.9};

  s21::Map<int, double> s21_map_int{pair1,  pair2,  pair3,
                                    pair11, pair22, pair33};
  EXPECT_EQ(s21_map_int[9], 1.4);
  EXPECT_EQ(s21_map_int[23], 2.77);
  EXPECT_EQ(s21_map_int[98], 3.9);
  EXPECT_EQ(s21_map_int[78], 3.9);
  EXPECT_EQ(s21_map_int[88], 3.9);
  EXPECT_EQ(s21_map_int[108], 3.9);

  std::pair<double, std::string> pair4{1.4, "hello"};
  std::pair<double, std::string> pair5{2.77, "hi"};
  std::pair<double, std::string> pair6{3.9, "hola"};

  s21::Map<double, std::string> s21_map_double{pair4, pair5, pair6};
  EXPECT_EQ(s21_map_double[1.4], "hello");
  EXPECT_EQ(s21_map_double[2.77], "hi");
  EXPECT_EQ(s21_map_double[3.9], "hola");

  std::pair<std::string, int> pair7{"hello", 1};
  std::pair<std::string, int> pair8{"hi", 2};
  std::pair<std::string, int> pair9{"hola", 3};

  s21::Map<std::string, int> s21_map_string{pair7, pair8, pair9};
  EXPECT_EQ(s21_map_string["hello"], 1);
  EXPECT_EQ(s21_map_string["hi"], 2);
  EXPECT_EQ(s21_map_string["hola"], 3);
}

TEST(map_test, constructor_1) {
    s21::Map<int, char> map1 = {{1, 'a'}, {2, 'b'}, {3, 'c'}, {4, 'd'}, {5, 'e'}};
    std::map<int, char> map2 = {{1, 'a'}, {2, 'b'}, {3, 'c'}, {4, 'd'}, {5, 'e'}};
    auto it = map1.begin();
    for (auto it2 = map2.begin(); it2 != map2.end(); it++, it2++) {
        EXPECT_EQ((*it).second, (*it2).second);
    }
    it = map1.begin(); 
    for (auto it2 = map2.begin(); it2 != map2.end(); it++, it2++) {
        EXPECT_EQ((*it).first, (*it2).first);
    }
    EXPECT_EQ(map1.size(), map2.size());
}

TEST(map_test, constructor_2) {
    s21::Map<int, char> map1 = {{1, 'a'}, {2, 'b'}, {3, 'c'}, {4, 'd'}, {5, 'e'}};
    std::map<int, char> map2 = {{1, 'a'}, {2, 'b'}, {3, 'c'}, {4, 'd'}, {5, 'e'}};
    auto map11 = map1;
    auto map22 = map2;
    auto it = map11.begin();
    for (auto it2 = map22.begin(); it2 != map22.end(); it2++, it++) {
        EXPECT_EQ((*it).second, (*it2).second);
    }
    EXPECT_EQ(map1.size(), map2.size());
    EXPECT_EQ(map11.size(), map22.size());
}

TEST(map_test, constructor_3) {
    s21::Map<int, char> map1;
    std::map<int, char> map2;
    EXPECT_EQ(map1.size(), map2.size());
    map1.insert({1, '1'});
    map2.insert({2, '2'});
    EXPECT_EQ(map1.size(), map2.size());
}



TEST(map_test, constructor_4) {
    s21::Map<int, char> map1 = {{1, 'a'}, {2, 'b'}, {3, 'c'}, {4, 'd'}, {5, 'e'}};
    std::map<int, char> map2 = {{1, 'a'}, {2, 'b'}, {3, 'c'}, {4, 'd'}, {5, 'e'}};
    auto a = std::move(map1);
    auto b = std::move(map2);
    auto it = a.begin();
    for (auto it2 = b.begin(); it2 != b.end(); it2++, it++) {
        EXPECT_EQ((*it).second, (*it2).second);
    }
    EXPECT_EQ(map1.size(), map2.size());
    EXPECT_EQ(a.size(), b.size());
}

TEST(map_test, constructor_5) {
    s21::Map<int, char> map1 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
    std::map<int, char> map2 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
    s21::Map<int, char> a;
    std::map<int, char> b;
    a = std::move(map1);
    b = std::move(map2);
    auto it = a.begin();
    for (auto it2 = b.begin(); it2 != b.end(); it2++, it++) {
        EXPECT_EQ((*it).second, (*it2).second);
    }
    EXPECT_EQ(map1.size(), map2.size());
    EXPECT_EQ(a.size(), b.size());
}

TEST(map_test, at_1) {
    s21::Map<int, char> map1 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
    std::map<int, char> map2 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
    for (size_t it = 1; it < map1.size(); it++) {
        EXPECT_EQ(map1.at(it), map2.at(it));
    }
}

TEST(map_test, at_2) {
    s21::Map<int, char> map1 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
    std::map<int, char> map2 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
    EXPECT_EQ(map1.at(2), map2.at(2));
}

TEST(map_test, at_3) {
    s21::Map<int, char> map1 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
    std::map<int, char> map2 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
    EXPECT_ANY_THROW(map1.at(100));
    EXPECT_ANY_THROW(map2.at(100));
}



TEST(map_test, operator1) {
    s21::Map<int, char> map1 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
    std::map<int, char> map2 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
    EXPECT_EQ(map1[100], map2[100]);
    EXPECT_ANY_THROW(map1.at(-4) = 'd');
    EXPECT_ANY_THROW(map2.at(-4) = 'd');
    EXPECT_NO_THROW(map1[-2] = 'b');
    EXPECT_NO_THROW(map2[-2] = 'b');
    EXPECT_EQ(map1.at(-2), map2.at(-2));
}

TEST(map_test, begin_1) {
    s21::Map<int, char> map1 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
    std::map<int, char> map2 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
    auto it = map1.begin();
    auto it2 = map2.begin();
    EXPECT_EQ((*it).second, (*it2).second);
}

TEST(map_test, end_1) {
    s21::Map<int, char> map1 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
    std::map<int, char> map2 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
    auto it = map1.end();
    auto it2 = map2.end();
    it--, it2--;
    EXPECT_EQ((*it2).second, (*it).second);
}

TEST(map_test, empty_1) {
    s21::Map<int, char> map1 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
    std::map<int, char> map2 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
    map1.clear();
    map2.clear();
    EXPECT_EQ(map1.empty(), map2.empty());
    s21::Map<int, char> a;
    std::map<int, char> b;
    EXPECT_EQ(map1.empty(), map2.empty());
}

TEST(map_test, empty_2) {
    s21::Map<int, char> map1 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
    std::map<int, char> map2 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
    EXPECT_EQ(map1.empty(), map2.empty());
}

TEST(map_test, size2) {
    s21::Map<int, char> map1 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
    std::map<int, char> map2 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
    EXPECT_EQ(map1.size(), map2.size());
}

TEST(map_test, size_3) {
    s21::Map<int, char> map1 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
    std::map<int, char> map2 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
    map1.clear();
    map2.clear();
    EXPECT_EQ(map1.size(), map2.size());
}

TEST(map_test, clear_1) {
    s21::Map<int, char> map1 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
    std::map<int, char> map2 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
    map1.clear();
    map2.clear();
    EXPECT_EQ(map1.empty(), map2.empty());
    EXPECT_EQ(map1.size(), map2.size());
    map1.clear();
    map2.clear();
    EXPECT_EQ(map1.size(), map2.size());
    EXPECT_EQ(map1.empty(), map2.empty());
}

TEST(map_test, clear_2) {
    s21::Map<int, char> map1;
    std::map<int, char> map2;
    map1.clear();
    map2.clear();
    EXPECT_EQ(map1.size(), map2.size());
    EXPECT_EQ(map1.empty(), map2.empty());

}


TEST(map_test, insert_1) {
    s21::Map<int, char> map1 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
    std::map<int, char> map2 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
    std::pair<int, char> pair = {6, 'c'};
    EXPECT_EQ(map1.insert(pair).second, map2.insert(pair).second);
    EXPECT_EQ(map1.size(), map2.size());
}

TEST(map_test, insert_2) {
    s21::Map<int, int> map1;
    std::map<int, int> map2;
    EXPECT_EQ(map1.empty(), map2.empty());
    std::pair<int, int> pair = {1,1};
    EXPECT_EQ(map1.insert(pair).second, map2.insert(pair).second);
    EXPECT_EQ(map1.empty(), map2.empty());
    EXPECT_EQ(map1.size(), map2.size());
}

TEST(map_test, erase_1) {
    s21::Map<int, char> map1 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
    std::map<int, char> map2 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
    EXPECT_EQ(map1.size(), map2.size());
    auto it1 = map1.begin();
    auto it2 = map2.begin();
    map1.erase(it1);
    map2.erase(it2);
    EXPECT_EQ(map1.size(), map2.size());
}

TEST(map_test, erase_2) {
    s21::Map<int, char> map1 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
    std::map<int, char> map2 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
    map1.erase(map1.begin());
    map2.erase(map2.begin());
    auto it = map1.begin();
    auto it2 = map2.begin();
    EXPECT_EQ((*it).second, (*it2).second);
    EXPECT_EQ(map1.size(), map2.size());
}

TEST(map_test, swap_1) {
    s21::Map<int, char> map1 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
    std::map<int, char> map2 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
    s21::Map<int, char> a;
    std::map<int, char> b;
    map1.swap(a);
    map2.swap(b);
    EXPECT_EQ(map1.size(), map2.size());
    EXPECT_EQ(a.size(), b.size());
    auto it = a.begin();
    for (auto it2 = b.begin(); it2 != b.end(); it++, it2++) {
        EXPECT_EQ((*it).second, (*it2).second);
    }
}

TEST(map_test, swap_2) {
    s21::Map<int, char> map1 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
    std::map<int, char> map2 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
    s21::Map<int, char> a = {{1, 'a'}, {2, 'b'}, {3, 'c'}, {4, 'd'}, {5, 'e'}};
    std::map<int, char> b = {{1, 'a'}, {2, 'b'}, {3, 'c'}, {4, 'd'}, {5, 'e'}};
    map1.swap(a);
    map2.swap(b);
    EXPECT_EQ(map1.size(), map2.size());
    EXPECT_EQ(a.size(), b.size());
    auto it = a.begin();
    for (auto it2 = b.begin(); it2 != b.end(); it++, it2++) {
        EXPECT_EQ((*it).second, (*it2).second);
    }
    s21::Map<int, char> map11;
    std::map<int, char> map22;
    s21::Map<int, char> a1;
    std::map<int, char> b1;
    map11.swap(a1);
    map22.swap(b1);
    EXPECT_EQ(map11.size(), map22.size());
    EXPECT_EQ(a1.size(), b1.size());
}
