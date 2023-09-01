#include <gtest/gtest.h>

#include "s21_stack.h"

TEST(test_stack, default_constructor) {
  s21::stack<int> stk1;
  s21::stack<int, std::vector<int>> stk2;
}

TEST(test_stack, container_constructor) {
  s21::stack<char> stk(s21::vector<char>{'a', 'b'});

  ASSERT_EQ(2, stk.size());
  ASSERT_EQ('b', stk.top());
  stk.pop();
  ASSERT_EQ('a', stk.top());
}

TEST(test_stack, copy_constructor) {
  s21::stack<std::string> stk1;
  s21::stack<std::string> stk2(stk1);

  ASSERT_EQ(stk1, stk2);

  stk2.push("Hello");
  s21::stack<std::string> stk3(stk2);
  ASSERT_EQ(stk2, stk3);
}

TEST(test_stack, move_constructor) {
  s21::stack<std::string> stk1;
  s21::stack<std::string> stk2(std::move(stk1));

  ASSERT_TRUE(stk2.empty());
  ASSERT_EQ(0, stk2.size());

  std::string value = "World";
  stk2.push(value);
  s21::stack<std::string> stk3(std::move(stk2));
  ASSERT_FALSE(stk3.empty());
  ASSERT_EQ(1, stk3.size());
  ASSERT_TRUE(value == stk3.top());
}

TEST(test_stack, ilist) {
  s21::stack<std::string> stack1({"1", "2"});
  s21::stack<std::string> stack2 = {"1", "2"};

  ASSERT_EQ(stack1, stack2);
}

TEST(test_stack, empty_stack) {
  s21::stack<int> stk;

  ASSERT_TRUE(stk.empty());
  ASSERT_EQ(0, stk.size());
  ASSERT_THROW(stk.top(), std::out_of_range);
}

TEST(test_stack, push_pop) {
  s21::stack<char> stk;

  char value = 'a';
  stk.push(value);
  ASSERT_FALSE(stk.empty());
  ASSERT_EQ(1, stk.size());
  ASSERT_TRUE(value == stk.top());
  stk.pop();
  ASSERT_TRUE(stk.empty());
  ASSERT_EQ(0, stk.size());
  ASSERT_THROW(stk.top(), std::out_of_range);
}

TEST(test_stack, comparisons) {
  s21::stack<char> stk1(s21::vector<char>{'a', 'b'});
  s21::stack<char> stk2(s21::vector<char>{'a', 'c'});
  s21::stack<char> stk3(stk1);

  ASSERT_EQ(stk1, stk3);
  ASSERT_NE(stk1, stk2);
  ASSERT_LE(stk1, stk3);
  ASSERT_LT(stk1, stk2);
  ASSERT_GT(stk2, stk1);
  ASSERT_GE(stk2, stk1);
}

TEST(test_stack, swap) {
  s21::stack<char> stk1(s21::vector<char>{'a', 'b'});
  s21::stack<char> stk1_copy(stk1);
  s21::stack<char> stk2(s21::vector<char>{'a', 'c'});
  s21::stack<char> stk2_copy(stk2);

  stk1.swap(stk2);
  ASSERT_EQ(stk1, stk2_copy);
  ASSERT_EQ(stk2, stk1_copy);

  s21::swap(stk2, stk1);
  ASSERT_EQ(stk1, stk1_copy);
  ASSERT_EQ(stk2, stk2_copy);
}

TEST(test_stack, insert_many_front) {
  s21::stack<int> stk;
  stk.push(3);

  stk.insert_many_front(2, 1);

  ASSERT_EQ(stk.top(), 1);
  stk.pop();
  ASSERT_EQ(stk.top(), 2);
  stk.pop();
  ASSERT_EQ(stk.top(), 3);
  stk.pop();
}
