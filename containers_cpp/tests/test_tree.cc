#include <gtest/gtest.h>

#include "../src/s21_rbtree.h"

TEST(test_rbtree, copy_node) {
  s21::Node<int, int> a(1, 2);
  s21::Node<int, int> b(a);
  ASSERT_EQ(a, b);
}

TEST(test_rbtree, copy_node_eq) {
  s21::Node<int, int> a(1, 2);
  s21::Node<int, int> b = a;
  ASSERT_EQ(a, b);
}

TEST(test_rbtree, copy) {
  s21::tree<int, int> a;
  a.insert(10, 0);
  a.insert(20, 0);
  s21::tree<int, int> b(a);
  ASSERT_TRUE(b.contains(10));
  ASSERT_EQ(b.size(), 2);
  ASSERT_EQ(a.get_root()->value, b.get_root()->value);
}

TEST(test_rbtree, copy_eq) {
  s21::tree<int, int> a;
  a.insert(10, 0);
  s21::tree<int, int> b = a;
  ASSERT_TRUE(b.contains(10));
  ASSERT_EQ(b.size(), 1);
  ASSERT_EQ(a.get_root()->value, b.get_root()->value);
}

TEST(test_rbtree, move) {
  s21::tree<int, int> a;
  a.insert(10, 0);
  s21::tree<int, int> b(std::move(a));
  ASSERT_TRUE(b.contains(10));
  ASSERT_EQ(b.size(), 1);
  ASSERT_EQ(a.size(), 0);
}

TEST(test_rbtree, move_eq) {
  s21::tree<int, int> a;
  a.insert(10, 0);
  s21::tree<int, int> b(std::move(a));
  ASSERT_TRUE(b.contains(10));
  ASSERT_EQ(b.size(), 1);
  ASSERT_EQ(a.size(), 0);
}

TEST(test_rbtree, size_of_empty_tree) {
  s21::tree<int, int> tree;
  ASSERT_EQ(tree.size(), 0);
  tree.insert(1, 1);
}

TEST(test_rbtree, insert_to_empty_tree) {
  s21::tree<char, char> tree;
  tree.insert('g', 'g');
  ASSERT_EQ(tree.get_root()->color, s21::BLACK);
  ASSERT_EQ(tree.get_root()->key, 'g');
  ASSERT_EQ(tree.get_root()->parent, nullptr);
  ASSERT_EQ(tree.get_root()->left, nullptr);
}

TEST(test_rbtree, insert_to_right) {
  s21::tree<int, int> tree;
  tree.insert(1, 1);
  tree.insert(2, 2);

  ASSERT_EQ(tree.get_root()->color, s21::BLACK);
  ASSERT_EQ(tree.get_root()->key, 1);
  ASSERT_EQ(tree.get_root()->parent, nullptr);
  ASSERT_EQ(tree.size(), 2);

  ASSERT_EQ(tree.get_root()->right->color, s21::RED);
  ASSERT_EQ(tree.get_root()->right->key, 2);
  ASSERT_EQ(tree.get_root()->right->parent, tree.get_root());
}

TEST(test_rbtree, insert_with_left_rotate) {
  s21::tree<int, int> tree;
  tree.insert(1, 1);
  tree.insert(2, 2);
  tree.insert(3, 3);

  ASSERT_EQ(tree.get_root()->color, s21::BLACK);
  ASSERT_EQ(tree.size(), 3);
  ASSERT_EQ(tree.get_root()->key, 2);

  ASSERT_EQ(tree.get_root()->left->color, s21::RED);
  ASSERT_EQ(tree.get_root()->left->key, 1);
  ASSERT_EQ(tree.get_root()->left->parent, tree.get_root());

  ASSERT_EQ(tree.get_root()->right->color, s21::RED);
  ASSERT_EQ(tree.get_root()->right->key, 3);
  ASSERT_EQ(tree.get_root()->right->parent, tree.get_root());
}

TEST(test_rbtree, insert_with_swap_color) {
  s21::tree<int, int> tree;
  tree.insert(61, 0);
  tree.insert(50, 0);
  tree.insert(85, 0);
  tree.insert(76, 0);

  ASSERT_EQ(tree.size(), 4);
  ASSERT_EQ(tree.get_root()->key, 61);
  ASSERT_EQ(tree.get_root()->color, s21::BLACK);

  ASSERT_EQ(tree.get_root()->left->key, 50);
  ASSERT_EQ(tree.get_root()->left->color, s21::BLACK);

  ASSERT_EQ(tree.get_root()->right->key, 85);
  ASSERT_EQ(tree.get_root()->right->color, s21::BLACK);

  ASSERT_EQ(tree.get_root()->right->left->key, 76);
  ASSERT_EQ(tree.get_root()->right->left->color, s21::RED);
}

TEST(test_rbtree, find_nullptr) {
  s21::tree<int, int> tree;
  tree.insert(1, 0);
  ASSERT_EQ(tree.find(2).get_pointer(), nullptr);
}

TEST(test_rbtree, find_success) {
  s21::tree<int, int> tree;
  tree.insert(1, 0);
  ASSERT_EQ(tree.find(1).get_key(), 1);
}

TEST(test_rbtree, contains_true) {
  s21::tree<int, int> tree;
  tree.insert(1, 0);
  ASSERT_EQ(tree.contains(1), true);
}

TEST(test_rbtree, contains_false) {
  s21::tree<int, int> tree;
  tree.insert(2, 0);
  tree.insert(3, 0);
  tree.insert(10, 0);
  ASSERT_EQ(tree.contains(1), false);
}

TEST(test_rbtree, swap) {
  s21::tree<int, int> a;
  s21::tree<int, int> b;
  a.insert(1, 1);
  a.insert(2, 2);
  b.insert(4, 4);
  a.swap(b);
  ASSERT_TRUE(b.contains(1));
  ASSERT_TRUE(a.contains(4));
}

TEST(test_rbtree, erase_nothing) {
  s21::tree<int, int> tree;
  ASSERT_EQ(tree.erase(1), 0);
}

TEST(test_rbtree, extract_nullptr) {
  s21::tree<int, int> tree;
  tree.insert(2, 0);
  auto node = tree.extract(1);
  ASSERT_EQ(node.parent, nullptr);
  ASSERT_EQ(tree.size(), 1);
}

TEST(test_rbtree, extract_red_without_child) {
  s21::tree<int, int> tree;
  tree.insert(2, 0);
  tree.insert(3, 0);
  auto node = tree.extract(3);
  ASSERT_EQ(node.key, 3);
  ASSERT_EQ(tree.size(), 1);
}

TEST(test_rbtree, extract_node_with_two_children) {
  s21::tree<int, int> tree;
  tree.insert(61, 0);
  tree.insert(52, 0);
  tree.insert(85, 0);
  tree.insert(76, 0);
  tree.insert(93, 0);
  tree.insert(100, 0);
  ASSERT_EQ(tree.get_root()->key, 61);
  ASSERT_EQ(tree.get_root()->color, s21::BLACK);
  ASSERT_EQ(tree.get_root()->left->key, 52);
  ASSERT_EQ(tree.get_root()->left->color, s21::BLACK);
  ASSERT_EQ(tree.get_root()->right->key, 85);
  ASSERT_EQ(tree.get_root()->right->color, s21::RED);
  ASSERT_EQ(tree.get_root()->right->left->key, 76);
  ASSERT_EQ(tree.get_root()->right->left->color, s21::BLACK);
  ASSERT_EQ(tree.get_root()->right->right->key, 93);
  ASSERT_EQ(tree.get_root()->right->right->color, s21::BLACK);
  ASSERT_EQ(tree.get_root()->right->right->right->key, 100);
  tree.insert(90, 0);
  auto node = tree.extract(85);
  ASSERT_EQ(node.key, 85);
  ASSERT_EQ(tree.size(), 6);
  ASSERT_EQ(tree.get_root()->right->key, 90);
}

TEST(test_rbtree, extract_node_with_two_children_2) {
  s21::tree<int, int> tree;
  tree.insert(10, 0);
  tree.insert(5, 0);
  tree.insert(30, 0);
  tree.insert(3, 0);
  tree.insert(7, 0);
  tree.insert(20, 0);
  tree.insert(38, 0);
  tree.insert(32, 0);
  tree.insert(41, 0);
  tree.insert(35, 0);

  tree.extract(30);

  ASSERT_EQ(tree.get_root()->key, 10);
  ASSERT_EQ(tree.get_root()->right->key, 38);
  ASSERT_EQ(tree.get_root()->right->right->key, 41);
  ASSERT_EQ(tree.get_root()->right->left->key, 32);
  ASSERT_EQ(tree.get_root()->right->left->right->key, 35);
  ASSERT_EQ(tree.get_root()->right->left->right->color, s21::BLACK);
  ASSERT_EQ(tree.size(), 9);
}

TEST(test_rbtree, extract_black_node_with_one_child) {
  s21::tree<int, int> tree;
  tree.insert(61, 0);
  tree.insert(52, 0);
  tree.insert(85, 0);
  tree.insert(76, 0);
  tree.insert(93, 0);
  tree.insert(100, 0);

  auto node = tree.extract(93);
  ASSERT_EQ(node.key, 93);
  ASSERT_EQ(tree.size(), 5);
  ASSERT_EQ(tree.find(85).get_pointer()->right->key, 100);
}

TEST(test_rbtree, extract_root_with_two_children) {
  s21::tree<int, int> tree;
  tree.insert(2, 0);
  tree.insert(1, 0);
  tree.insert(3, 0);

  auto node = tree.extract(2);
  ASSERT_EQ(node.key, 2);
  ASSERT_EQ(tree.get_root()->key, 1);
  ASSERT_EQ(tree.size(), 2);
}

TEST(test_rbtree, extract_black_node_without_children_1) {
  s21::tree<int, int> tree;
  tree.insert(2, 0);
  tree.insert(1, 0);
  tree.insert(4, 0);
  tree.insert(3, 0);
  tree.insert(5, 0);

  auto node = tree.extract(1);
  ASSERT_EQ(node.key, 1);
  ASSERT_EQ(tree.size(), 4);
  ASSERT_EQ(tree.get_root()->key, 4);
  ASSERT_EQ(tree.get_root()->color, s21::BLACK);
  ASSERT_EQ(tree.get_root()->right->key, 5);
  ASSERT_EQ(tree.get_root()->right->color, s21::BLACK);
  ASSERT_EQ(tree.get_root()->left->key, 2);
  ASSERT_EQ(tree.get_root()->left->color, s21::BLACK);
  ASSERT_EQ(tree.get_root()->left->right->key, 3);
  ASSERT_EQ(tree.get_root()->left->right->color, s21::RED);
}

TEST(test_rbtree, extract_black_node_without_children_2) {
  s21::tree<int, int> tree;
  tree.insert(4, 0);
  tree.insert(2, 0);
  tree.insert(5, 0);
  tree.insert(3, 0);
  tree.insert(1, 0);

  auto node = tree.extract(5);
  ASSERT_EQ(node.key, 5);
  ASSERT_EQ(tree.size(), 4);
  ASSERT_EQ(tree.get_root()->key, 2);
  ASSERT_EQ(tree.get_root()->color, s21::BLACK);
  ASSERT_EQ(tree.get_root()->left->key, 1);
  ASSERT_EQ(tree.get_root()->left->color, s21::BLACK);
  ASSERT_EQ(tree.get_root()->right->key, 4);
  ASSERT_EQ(tree.get_root()->right->color, s21::BLACK);
  ASSERT_EQ(tree.get_root()->right->left->key, 3);
  ASSERT_EQ(tree.get_root()->right->left->color, s21::RED);
}

TEST(test_rbtree, extract_black_node_without_children_3) {
  s21::tree<int, int> tree;
  tree.insert(4, 0);
  tree.insert(2, 0);
  tree.insert(6, 0);
  tree.insert(5, 0);

  auto node = tree.extract(2);
  ASSERT_EQ(node.key, 2);
  ASSERT_EQ(tree.size(), 3);
  ASSERT_EQ(tree.get_root()->key, 5);
  ASSERT_EQ(tree.get_root()->color, s21::BLACK);
  ASSERT_EQ(tree.get_root()->left->key, 4);
  ASSERT_EQ(tree.get_root()->left->color, s21::BLACK);
  ASSERT_EQ(tree.get_root()->right->key, 6);
  ASSERT_EQ(tree.get_root()->right->color, s21::BLACK);
}

TEST(test_rbtree, extract_black_node_without_children_4) {
  s21::tree<int, int> tree;
  tree.insert(4, 0);
  tree.insert(2, 0);
  tree.insert(6, 0);
  tree.insert(3, 0);

  auto node = tree.extract(6);
  ASSERT_EQ(node.key, 6);
  ASSERT_EQ(tree.size(), 3);
  ASSERT_EQ(tree.get_root()->key, 3);
  ASSERT_EQ(tree.get_root()->color, s21::BLACK);
  ASSERT_EQ(tree.get_root()->left->key, 2);
  ASSERT_EQ(tree.get_root()->left->color, s21::BLACK);
  ASSERT_EQ(tree.get_root()->right->key, 4);
  ASSERT_EQ(tree.get_root()->right->color, s21::BLACK);
}

TEST(test_rbtree, extract_black_node_without_children_5) {
  s21::tree<int, int> tree;
  tree.insert(2, 0);
  tree.insert(1, 0);
  tree.insert(4, 0);
  tree.insert(3, 0);
  tree.extract(3);
  tree.extract(1);

  ASSERT_EQ(tree.size(), 2);
  ASSERT_EQ(tree.get_root()->key, 2);
  ASSERT_EQ(tree.get_root()->color, s21::BLACK);
  ASSERT_EQ(tree.get_root()->right->key, 4);
  ASSERT_EQ(tree.get_root()->right->color, s21::RED);
}

TEST(test_rbtree, extract_black_node_without_children_6) {
  s21::tree<int, int> tree;
  tree.insert(10, 0);
  tree.insert(5, 0);
  tree.insert(11, 0);
  tree.insert(3, 0);
  tree.insert(7, 0);
  tree.insert(1, 0);
  tree.extract(1);
  tree.extract(7);

  ASSERT_EQ(tree.size(), 4);
  ASSERT_EQ(tree.get_root()->key, 10);
  ASSERT_EQ(tree.get_root()->color, s21::BLACK);
  ASSERT_EQ(tree.get_root()->right->key, 11);
  ASSERT_EQ(tree.get_root()->right->color, s21::BLACK);
  ASSERT_EQ(tree.get_root()->left->key, 5);
  ASSERT_EQ(tree.get_root()->left->color, s21::BLACK);
  ASSERT_EQ(tree.get_root()->left->left->key, 3);
  ASSERT_EQ(tree.get_root()->left->left->color, s21::RED);
}

TEST(test_rbtree, clear_tree) {
  s21::tree<int, int> tree;
  tree.insert(10, 0);

  tree.clear();
  ASSERT_EQ(tree.get_root(), nullptr);
  ASSERT_EQ(tree.size(), 0);
}

TEST(test_rbtree, is_equal) {
  s21::tree<int, int> tree;
  s21::tree<int, int> other;
  tree.insert(1, 0);
  other.insert(1, 0);
  ASSERT_EQ(tree, other);
}

TEST(test_rbtree, is_equal_false) {
  s21::tree<int, int> tree;
  s21::tree<int, int> other;
  tree.insert(1, 0);
  other.insert(1, 0);
  tree.insert(2, 0);
  other.insert(3, 0);
  ASSERT_FALSE(tree == other);
}

TEST(test_rbtree, is_not_equal) {
  s21::tree<int, int> tree;
  s21::tree<int, int> other;
  tree.insert(2, 0);
  other.insert(1, 0);
  ASSERT_TRUE(tree != other);
}

TEST(test_rbtree, is_not_equal_false) {
  s21::tree<int, int> tree;
  s21::tree<int, int> other;
  tree.insert(1, 0);
  other.insert(1, 0);
  tree.insert(2, 0);
  other.insert(2, 0);
  ASSERT_FALSE(tree != other);
}

TEST(test_rbtree, is_less) {
  s21::tree<int, int> tree;
  s21::tree<int, int> other;
  tree.insert(1, 0);
  other.insert(2, 0);
  ASSERT_TRUE(tree < other);
}

TEST(test_rbtree, is_less_false) {
  s21::tree<int, int> tree;
  s21::tree<int, int> other;
  tree.insert(3, 0);
  other.insert(2, 0);
  ASSERT_FALSE(tree < other);
}

TEST(test_rbtree, is_less_false_2) {
  s21::tree<int, int> tree;
  s21::tree<int, int> other;
  tree.insert(2, 0);
  other.insert(2, 0);
  ASSERT_FALSE(tree < other);
}

TEST(test_rbtree, is_less_or_eq) {
  s21::tree<int, int> tree;
  s21::tree<int, int> other;
  tree.insert(1, 0);
  other.insert(2, 0);
  ASSERT_TRUE(tree <= other);
}

TEST(test_rbtree, is_less_or_eq_2) {
  s21::tree<int, int> tree;
  s21::tree<int, int> other;
  tree.insert(2, 0);
  other.insert(2, 0);
  ASSERT_TRUE(tree <= other);
}

TEST(test_rbtree, is_less_or_eq_false) {
  s21::tree<int, int> tree;
  s21::tree<int, int> other;
  tree.insert(3, 0);
  other.insert(2, 0);
  ASSERT_FALSE(tree <= other);
}

TEST(test_rbtree, is_greater) {
  s21::tree<int, int> tree;
  s21::tree<int, int> other;
  tree.insert(2, 0);
  other.insert(1, 0);
  ASSERT_TRUE(tree > other);
}

TEST(test_rbtree, is_greater_false) {
  s21::tree<int, int> tree;
  s21::tree<int, int> other;
  tree.insert(2, 0);
  other.insert(3, 0);
  ASSERT_FALSE(tree > other);
}

TEST(test_rbtree, is_greated_false_2) {
  s21::tree<int, int> tree;
  s21::tree<int, int> other;
  tree.insert(2, 0);
  other.insert(2, 0);
  ASSERT_FALSE(tree > other);
}

TEST(test_rbtree, is_greater_or_eq) {
  s21::tree<int, int> tree;
  s21::tree<int, int> other;
  tree.insert(2, 0);
  other.insert(1, 0);
  ASSERT_TRUE(tree >= other);
}

TEST(test_rbtree, is_greater_or_eq_2) {
  s21::tree<int, int> tree;
  s21::tree<int, int> other;
  tree.insert(2, 0);
  other.insert(2, 0);
  ASSERT_TRUE(tree >= other);
}

TEST(test_rbtree, is_greater_or_eq_false) {
  s21::tree<int, int> tree;
  s21::tree<int, int> other;
  tree.insert(2, 0);
  other.insert(3, 0);
  ASSERT_FALSE(tree >= other);
}