#include <gtest/gtest.h>

#include "s21_list.h"
#include "s21_queue.h"

TEST(test_queue, default_constructor) {
  s21::queue<int> queue1;
  s21::queue<int, std::vector<int>> queue2;
}

TEST(test_queue, container_constructor) {
  s21::queue<char> queue(s21::list<char>{'a', 'b'});

  ASSERT_EQ(2, queue.size());
  ASSERT_EQ('a', queue.front());
  ASSERT_EQ('b', queue.back());
  queue.pop();
}

TEST(test_queue, copy_constructor) {
  s21::queue<std::string> queue1;
  s21::queue<std::string> queue2(queue1);

  ASSERT_EQ(queue1, queue2);

  queue2.push("Hello");
  s21::queue<std::string> queue3(queue2);
  ASSERT_EQ(queue2, queue3);
}

TEST(test_queue, move_constructor) {
  s21::queue<std::string> queue1;
  s21::queue<std::string> queue2(std::move(queue1));

  ASSERT_TRUE(queue2.empty());
  ASSERT_EQ(0, queue2.size());

  std::string value = "World";
  queue2.push(value);
  s21::queue<std::string> queue3(std::move(queue2));

  ASSERT_FALSE(queue3.empty());
  ASSERT_EQ(1, queue3.size());
  ASSERT_EQ(value, queue3.back());
}

TEST(test_queue, ilist) {
  std::string value = "1";
  s21::queue<std::string> queue1({value});
  s21::queue<std::string> queue2 = {value};

  ASSERT_EQ(queue1, queue2);
}

TEST(test_queue, empty_queue) {
  s21::queue<int> queue;

  ASSERT_TRUE(queue.empty());
  ASSERT_EQ(0, queue.size());
}

TEST(test_queue, push_pop) {
  s21::queue<char> queue;

  char value = 'a';
  queue.push(value);
  ASSERT_FALSE(queue.empty());
  ASSERT_EQ(1, queue.size());
  ASSERT_EQ(queue.front(), queue.back());

  queue.pop();
  ASSERT_TRUE(queue.empty());
  ASSERT_EQ(0, queue.size());
}

TEST(test_queue, comparisons) {
  s21::queue<char> queue1(s21::list<char>{'a', 'b'});
  s21::queue<char> queue2(s21::list<char>{'a', 'c'});
  s21::queue<char> queue3(queue1);

  ASSERT_EQ(queue1, queue3);
  ASSERT_NE(queue1, queue2);
  ASSERT_LE(queue1, queue3);
  ASSERT_LT(queue1, queue2);
  ASSERT_GT(queue2, queue1);
  ASSERT_GE(queue2, queue1);
}

TEST(test_queue, swap) {
  s21::queue<char> queue1(s21::list<char>{'a', 'b'});
  s21::queue<char> queue1_copy(queue1);
  s21::queue<char> queue2(s21::list<char>{'a', 'c'});
  s21::queue<char> queue2_copy(queue2);

  queue1.swap(queue2);
  ASSERT_EQ(queue1, queue2_copy);
  ASSERT_EQ(queue2, queue1_copy);

  s21::swap(queue2, queue1);
  ASSERT_EQ(queue1, queue1_copy);
  ASSERT_EQ(queue2, queue2_copy);
}

TEST(test_queue, insert_many_back) {
  s21::queue<int> queue;
  queue.push(3);

  queue.insert_many_back(2, 1);

  ASSERT_EQ(queue.front(), 3);
  queue.pop();
  ASSERT_EQ(queue.front(), 2);
  queue.pop();
  ASSERT_EQ(queue.front(), 1);
  queue.pop();
}
