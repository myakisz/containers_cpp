#include <gtest/gtest.h>

#include "../src/s21_multiset.h"

TEST(test_multiset, create_default_multiset) {
  s21::multiset<int> s;
  ASSERT_TRUE(s.get_tree().get_is_multi());
  ASSERT_TRUE(s.empty());
}

TEST(test_multiset, copy) {
  s21::multiset<int> s;
  ASSERT_TRUE(s.get_tree().get_is_multi());
  s.insert(1);
  s.insert(1);
  s21::multiset<int> c(s);
  ASSERT_TRUE(c.get_tree().get_is_multi());
  ASSERT_EQ(s.size(), 2);
  ASSERT_EQ(c.size(), 2);
  ASSERT_TRUE(c.contains(1));
}

TEST(test_multiset, copy_eq) {
  s21::multiset<int> s;
  s.insert(1);
  s.insert(2);
  s21::multiset<int> c = s;
  ASSERT_EQ(s.size(), 2);
  ASSERT_TRUE(s.contains(1));
  ASSERT_EQ(c.size(), 2);
  // ASSERT_EQ(c.count(1), 2);
  ASSERT_TRUE(s.get_tree().get_is_multi());
  ASSERT_TRUE(c.get_tree().get_is_multi());
}

TEST(test_multiset, move) {
  s21::multiset<int> s;
  s.insert(1);
  s.insert(1);
  s21::multiset<int> c(std::move(s));
  ASSERT_EQ(c.size(), 2);
  ASSERT_TRUE(c.contains(1));
  ASSERT_TRUE(s.empty());
  ASSERT_TRUE(c.get_tree().get_is_multi());
}

TEST(test_multiset, move_eq) {
  s21::multiset<int> s;
  s.insert(1);
  s.insert(1);
  s21::set<int> c = std::move(s);
  ASSERT_EQ(c.size(), 2);
  ASSERT_TRUE(c.contains(1));
  ASSERT_TRUE(c.get_tree().get_is_multi());
  ASSERT_TRUE(s.empty());
}

TEST(test_multiset, create_from_ilist) {
  s21::multiset<int> s({1, 1, 3});
  ASSERT_EQ(s.size(), 3);
  s21::TreeIterator it = s.cbegin();
  ASSERT_EQ(*it, 1);
  it++;
  ASSERT_EQ(*it, 1);
  it++;
  ASSERT_EQ(*it, 3);
  ASSERT_TRUE(s.get_tree().get_is_multi());
  ASSERT_EQ(s.count(1), 2);
}

TEST(test_multiset, begin) {
  s21::multiset<int> s;
  s.insert(61);
  s.insert(52);
  s.insert(85);
  s.insert(76);
  s.insert(52);
  s.insert(100);
  s.insert(50);
  s.insert(54);
  s.insert(52);
  s21::TreeIterator it = s.cbegin();
  ASSERT_EQ(*it, 50);
  ASSERT_EQ(s.size(), 9);
  it++;
  ASSERT_EQ(*it, 52);
  it++;
  ASSERT_EQ(*it, 52);
  it++;
  ASSERT_EQ(*it, 52);
  it++;
  ASSERT_EQ(*it, 54);
  it++;
  ASSERT_EQ(*it, 61);
  it++;
  ASSERT_EQ(*it, 76);
  it++;
  ASSERT_EQ(*it, 85);
  it++;
  ASSERT_EQ(*it, 100);
  ASSERT_EQ(s.count(52), 3);
}

TEST(test_multiset, end) {
  s21::multiset<int> s;
  s.insert(61);
  s.insert(100);
  s.insert(100);
  s.insert(50);
  s21::TreeIterator it = s.cend();
  it--;
  ASSERT_EQ(*it, 100);
  it--;
  ASSERT_EQ(*it, 100);
}

TEST(test_multiset, clear) {
  s21::multiset<int> s;
  s.insert(61);
  s.insert(100);
  s.insert(100);
  s.insert(50);
  s.clear();
  ASSERT_TRUE(s.empty());
}

TEST(test_multiset, insert_one) {
  s21::multiset<int> s({1, 1, 3});
  ASSERT_EQ(*std::get<0>(s.insert(1)), 1);
  ASSERT_EQ(s.count(1), 3);
  ASSERT_EQ(std::get<1>(s.insert(3)), true);
  ASSERT_EQ(s.count(3), 2);
}

TEST(test_multiset, insert_ilist) {
  s21::multiset<int> s({1, 1, 3});
  ASSERT_EQ(s.size(), 3);
  s.insert({1, 1, 3});
  ASSERT_EQ(s.size(), 6);
  ASSERT_EQ(s.count(1), 4);
  ASSERT_EQ(s.count(3), 2);
}

TEST(test_multiset, insert_many) {
  s21::multiset<int> s({1, 1, 3});
  ASSERT_EQ(1, (*std::get<0>(s.insert_many(1, 1, 3))));
  ASSERT_EQ(s.count(1), 4);
  ASSERT_EQ(s.count(3), 2);
}

TEST(test_multiset, erase_at_pos) {
  s21::multiset<int> s({1, 1, 1, 3});
  s21::TreeConstIterator it = s.cbegin();
  it++;
  auto it2 = s.erase(it);
  ASSERT_EQ(s.count(1), 2);
  ASSERT_EQ(*it2, 1);
  it2++;
  ASSERT_EQ(*it2, 3);
}

TEST(test_multiset, erase_at_pos_2) {
  s21::multiset<int> s({1, 1, 1, 3});
  s21::TreeConstIterator it = s.cbegin();
  auto it2 = s.erase(it);
  ASSERT_EQ(s.count(1), 2);
  ASSERT_EQ(*it2, 1);
  it2++;
  ASSERT_EQ(*it2, 1);
  it2++;
  ASSERT_EQ(*it2, 3);
}

TEST(test_multiset, erase_at_pos_3) {
  s21::multiset<int> s({1, 1, 1, 3});
  s21::TreeConstIterator it = s.cbegin();
  it++;
  it++;
  auto it2 = s.erase(it);
  ASSERT_EQ(s.count(1), 2);
  ASSERT_EQ(*it2, 3);
}

TEST(test_multiset, erase_at_pos_4) {
  s21::multiset<int> s({1, 2, 3, 4});
  s21::TreeConstIterator it = s.cbegin();
  it++;
  it++;
  auto it2 = s.erase(it);
  ASSERT_EQ(s.count(1), 1);
  ASSERT_EQ(s.count(2), 1);
  ASSERT_EQ(s.count(3), 0);
  ASSERT_EQ(s.count(4), 1);
  ASSERT_EQ(*it2, 4);
}

TEST(test_multiset, erase_at_pos_last) {
  s21::multiset<int> s({1, 1, 1});
  s21::TreeConstIterator it = s.cbegin();
  it++;
  it++;
  auto it2 = s.erase(it);
  ASSERT_EQ(s.count(1), 2);
  it2--;
  ASSERT_EQ(*it2, 1);
}

TEST(test_multiset, erase_at_pos_last_2) {
  s21::multiset<int> s({1, 2, 3});
  s21::TreeConstIterator it = s.cbegin();
  it++;
  it++;
  auto it2 = s.erase(it);
  ASSERT_EQ(s.count(1), 1);
  ASSERT_EQ(s.count(2), 1);
  ASSERT_EQ(s.count(3), 0);
  it2--;
  ASSERT_EQ(*it2, 2);
}

TEST(test_multiset, erase_from_key) {
  s21::multiset<int> s({1, 1, 1, 3});
  auto count = s.erase(1);
  ASSERT_EQ(s.count(1), 0);
  ASSERT_EQ(count, 3);
}

TEST(test_multiset, erase_from_key_2) {
  s21::multiset<int> s({1, 1, 1, 3});
  auto count = s.erase(3);
  ASSERT_EQ(s.count(1), 3);
  ASSERT_EQ(s.count(3), 0);
  ASSERT_EQ(count, 1);
}

TEST(test_multiset, erase_mult) {
  s21::multiset<int> s({1, 1, 1, 3});
  s21::TreeConstIterator first = s.cbegin();
  s21::TreeConstIterator last = s.cbegin();
  last++;
  last++;
  auto it = s.erase(first, last);
  ASSERT_EQ(s.count(1), 1);
  ASSERT_EQ(s.count(3), 1);
  ASSERT_EQ(s.size(), 2);
  ASSERT_EQ(*it, 1);
}

TEST(test_multiset, erase_mult_end) {
  s21::multiset<int> s({1, 1, 1, 3});
  s21::TreeConstIterator first = s.cbegin();
  s21::TreeConstIterator last = s.cend();
  first++;
  auto it = s.erase(first, last);
  ASSERT_EQ(s.count(1), 1);
  ASSERT_EQ(s.count(3), 0);
  ASSERT_EQ(s.size(), 1);
  it--;
  ASSERT_EQ(*it, 1);
}

TEST(test_multiset, swap) {
  s21::multiset<int> a({1, 1});
  s21::multiset<int> b({2, 2});
  a.swap(b);
  ASSERT_TRUE(b.contains(1));
  ASSERT_TRUE(a.contains(2));
}

TEST(test_multiset, extract_from_pos) {
  s21::multiset<int> s({1, 1, 1, 3});
  s21::TreeConstIterator it = s.cbegin();
  it++;
  it++;
  s21::Node n = s.extract(it);
  ASSERT_EQ(n.value, 1);
  ASSERT_EQ(s.count(1), 2);
}

TEST(test_multiset, extract_from_key) {
  s21::multiset<int> s({1, 1, 1, 3});
  s21::Node n = s.extract(1);
  ASSERT_EQ(n.value, 1);
  ASSERT_EQ(s.count(1), 2);
}

TEST(test_multiset, count) {
  s21::multiset<int> s({1, 1, 1, 3});
  ASSERT_EQ(s.count(1), 3);
  ASSERT_EQ(s.count(3), 1);
  ASSERT_EQ(s.count(4), 0);
  s.erase(3);
  ASSERT_EQ(s.count(3), 0);
}

TEST(test_multiset, merge_with_set) {
  s21::multiset<int> s({1, 1, 1, 3});
  s21::set<int> a({1, 2, 3});
  s.merge(a);
  ASSERT_EQ(s.count(1), 4);
  ASSERT_EQ(s.count(2), 1);
  ASSERT_EQ(s.count(3), 2);
  ASSERT_EQ(s.size(), 7);
}

TEST(test_multiset, merge_with_multiset) {
  s21::multiset<int> s({1, 1});
  s21::multiset<int> a({2, 2});
  s.merge(a);
  ASSERT_EQ(s.count(1), 2);
  ASSERT_EQ(s.count(2), 2);
  ASSERT_EQ(s.size(), 4);
}

TEST(test_multiset, find) {
  s21::multiset<int> s({1, 1, 1, 3});
  auto it = s.find(1);
  it++;
  ASSERT_EQ(*it, 1);
  it++;
  ASSERT_EQ(*it, 3);
}

TEST(test_multiset, upper_bound) {
  s21::multiset<int> s;
  s.insert(2);
  s.insert(2);
  s.insert(3);
  s.insert(3);
  s.insert(4);
  auto it = s.upper_bound(2);
  ASSERT_EQ(it.get_key(), 3);
  it++;
  ASSERT_EQ(it.get_key(), 3);
}

TEST(test_multiset, lower_bound) {
  s21::multiset<int> s;
  s.insert(1);
  s.insert(2);
  s.insert(2);
  s.insert(3);
  auto it = s.lower_bound(2);
  ASSERT_EQ(it.get_key(), 2);
  it--;
  ASSERT_EQ(it.get_key(), 1);
}

TEST(test_multiset, equal_range) {
  s21::multiset<int> s;
  s.insert(1);
  s.insert(2);
  s.insert(2);
  s.insert(3);
  auto p = s.equal_range(2);
  ASSERT_EQ(p.first.get_key(), 2);
  ASSERT_EQ(p.second.get_key(), 3);
  auto it = p.first;
  it--;
  ASSERT_EQ(it.get_key(), 1);
}
