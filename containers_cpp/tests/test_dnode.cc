#include <gtest/gtest.h>

#include "s21_dnode.h"

TEST(test_dnode, dnode_default) {
  s21::dnode<int> node;

  ASSERT_TRUE(node.prev == nullptr);
  ASSERT_TRUE(node.data == int());
  ASSERT_TRUE(node.next == nullptr);
}

TEST(test_dnode, dnode_param_copy) {
  char value = 'a';
  s21::dnode<char> node(value);

  ASSERT_TRUE(node.prev == nullptr);
  ASSERT_TRUE(node.data == value);
  ASSERT_TRUE(node.next == nullptr);
}

TEST(test_dnode, dnode_param_move) {
  std::string value = "str";
  s21::dnode<std::string> node("str");

  ASSERT_TRUE(node.prev == nullptr);
  ASSERT_TRUE(node.data == value);
  ASSERT_TRUE(node.next == nullptr);
}

TEST(test_dnode, dnode_copy_ctor) {
  bool value = true;
  s21::dnode<bool> node(value);
  s21::dnode<bool> copy_node(node);

  ASSERT_EQ(node, copy_node);
}

TEST(test_dnode, dnode_move_ctor) {
  bool value = false;
  s21::dnode<bool> node(value);
  s21::dnode<bool> move_node(std::move(node));

  ASSERT_TRUE(move_node.prev == nullptr);
  ASSERT_TRUE(move_node.data == value);
  ASSERT_TRUE(move_node.next == nullptr);
}

TEST(test_dnode, dnode_copy_assignment) {
  int value = 21;
  s21::dnode<int> node(value);
  s21::dnode<int> copy_node = node;

  ASSERT_EQ(node, copy_node);
}

TEST(test_dnode, dnode_move_assignment) {
  int value = 21;
  s21::dnode<int> node(value);
  s21::dnode<int> move_node = std::move(node);

  ASSERT_TRUE(move_node.prev == nullptr);
  ASSERT_TRUE(move_node.data == value);
  ASSERT_TRUE(move_node.next == nullptr);
}

TEST(test_dnode, dnode_attach_detach_prev) {
  s21::dnode<int> node1(21);
  s21::dnode<int> node2(42);

  node2.attach_prev(&node1);
  ASSERT_TRUE(node1.prev == nullptr);
  ASSERT_TRUE(node1.next == &node2);
  ASSERT_TRUE(node2.prev == &node1);

  s21::dnode<int> *prev_node = node2.detach_prev();
  ASSERT_EQ(*prev_node, node1);
  ASSERT_TRUE(node1.prev == nullptr);
  ASSERT_TRUE(node1.next == nullptr);
  ASSERT_TRUE(node2.prev == nullptr);
  ASSERT_TRUE(node2.next == nullptr);
}

TEST(test_dnode, dnode_attach_detach_next) {
  s21::dnode<int> node1(21);
  s21::dnode<int> node2(42);

  node1.attach_next(&node2);
  ASSERT_TRUE(node1.prev == nullptr);
  ASSERT_TRUE(node1.next == &node2);
  ASSERT_TRUE(node2.prev == &node1);

  s21::dnode<int> *prev_node = node2.detach_prev();
  ASSERT_EQ(*prev_node, node1);
  ASSERT_TRUE(node1.prev == nullptr);
  ASSERT_TRUE(node1.next == nullptr);
  ASSERT_TRUE(node2.prev == nullptr);
  ASSERT_TRUE(node2.next == nullptr);
}

TEST(test_dnode, swap) {
  s21::dnode<int> node1(21);
  s21::dnode<int> node1_next(22);
  s21::dnode<int> node2(42);
  s21::dnode<int> node2_next(43);

  node1.attach_next(&node1_next);
  node2.attach_next(&node2_next);
  ASSERT_TRUE(node1.prev == nullptr);
  ASSERT_TRUE(node1.next == &node1_next);
  ASSERT_TRUE(node2.prev == nullptr);
  ASSERT_TRUE(node2.next == &node2_next);

  node1.swap(node2);
  ASSERT_EQ(node1.data, 42);
  ASSERT_EQ(node2.data, 21);
  ASSERT_EQ(node2.next, &node1_next);
  ASSERT_EQ(node1.next, &node2_next);
}
