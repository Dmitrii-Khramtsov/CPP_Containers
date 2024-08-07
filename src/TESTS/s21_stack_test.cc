
#include <stack>
#include "test_runner.h"


TEST(create_stack, check_create_stack_1) { s21::stack<int> ex; }

TEST(create_stack, check_create_stack_2) { s21::stack<char> ex; }

TEST(create_stack, check_copy_constructor_1) {
  s21::stack<int> st_1;
  st_1.push(21);
  st_1.push(2);
  st_1.push(8);
  st_1.push(-12);

  s21::stack<int> st_2(st_1);
  size_t size_1 = st_1.size();
  size_t size_2 = st_2.size();
  for (size_t i = 0; i < size_1 && i < size_2; i++) {
    EXPECT_EQ(st_1.top(), st_2.top());
    st_1.pop();
    st_2.pop();
  }
}

TEST(create_stack, check_move_constructor) {
  s21::stack<int> st_1;
  st_1.push(1);
  st_1.push(2);
  st_1.push(3);

  std::stack<int> st_1_buf;
  st_1_buf.push(1);
  st_1_buf.push(2);
  st_1_buf.push(3);

  s21::stack<int> st_2(std::move(st_1));
  std::stack<int> st_2_buf(std::move(st_1_buf));

  while (st_2.size() > 0 || st_2_buf.size() > 0) {
    EXPECT_EQ(st_2.top(), st_2_buf.top());
    st_2.pop();
    st_2_buf.pop();
  }
}

TEST(create_stack, check_constructor_with_initialization_list_1) {
  s21::stack<int> st_1{1, 2, 3, 4, 5};
  std::deque<int> st_1_buf_que{1, 2, 3, 4, 5};
  std::stack<int> st_1_buf{st_1_buf_que};

  while (st_1.size() > 0 || st_1_buf.size() > 0) {
    EXPECT_EQ(st_1.top(), st_1_buf.top());
    st_1.pop();
    st_1_buf.pop();
  }
}

TEST(stack_test_swap, check_swap_1) {
  s21::stack<int> st_1{1, 2, 3};
  s21::stack<int> st_2{4, 5, 6};

  std::stack<int> st_1_buf;
  st_1_buf.push(1);
  st_1_buf.push(2);
  st_1_buf.push(3);

  std::stack<int> st_2_buf;
  st_2_buf.push(4);
  st_2_buf.push(5);
  st_2_buf.push(6);

  st_1.swap(st_2);
  st_1_buf.swap(st_2_buf);



  while (!st_1.empty() || !st_1_buf.empty()) {

    EXPECT_EQ(st_1.top(), st_1_buf.top());
    st_1.pop();
    st_1_buf.pop();

  }

  while (!st_2.empty() || !st_2_buf.empty()) {
    EXPECT_EQ(st_2.top(), st_2_buf.top());
    st_2.pop();
    st_2_buf.pop();
  }

}


TEST(test_insert_many, check_insert_many_1) {
  s21::stack<int> st_1{1, 2, 3};
  st_1.insert_many_back(1, 2, 3);

  std::deque<int> st_2_buf_que{1, 2, 3, 1, 2, 3};
  std::stack<int> st_2(st_2_buf_que);

  while (!st_1.empty()) {
    EXPECT_EQ(st_1.top(), st_2.top());
    st_1.pop();
    st_2.pop();
  }
}

