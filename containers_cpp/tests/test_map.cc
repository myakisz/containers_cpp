#include <gtest/gtest.h>

#include "../src/s21_map.h"

TEST(test_map, create_default_set) {
  s21::map<int, int> m;
  ASSERT_TRUE(m.empty());
}

TEST(test_map, copy) {
  s21::map<int, int> m(
      {std::make_pair(1, 1), std::make_pair(2, 1), std::make_pair(3, 1)});
  s21::map<int, int> c(m);
  ASSERT_EQ(c.size(), 3);
  ASSERT_TRUE(c.contains(1));
  ASSERT_TRUE(c.contains(2));
  ASSERT_TRUE(c.contains(3));
}

TEST(test_map, copy_eq) {
  s21::map<int, int> m(
      {std::make_pair(1, 1), std::make_pair(2, 1), std::make_pair(3, 1)});
  s21::map<int, int> c = m;
  ASSERT_EQ(c.size(), 3);
  ASSERT_TRUE(c.contains(1));
  ASSERT_TRUE(c.contains(2));
  ASSERT_TRUE(c.contains(3));
}

TEST(test_map, move) {
  s21::map<int, int> m(
      {std::make_pair(1, 1), std::make_pair(2, 1), std::make_pair(3, 1)});
  s21::map<int, int> c(std::move(m));
  ASSERT_EQ(c.size(), 3);
  ASSERT_TRUE(c.contains(1));
  ASSERT_TRUE(c.contains(2));
  ASSERT_TRUE(c.contains(3));
  ASSERT_TRUE(m.empty());
}

TEST(test_map, move_eq) {
  s21::map<int, int> m(
      {std::make_pair(1, 1), std::make_pair(2, 1), std::make_pair(3, 1)});
  s21::map<int, int> c = std::move(m);
  ASSERT_EQ(c.size(), 3);
  ASSERT_TRUE(c.contains(1));
  ASSERT_TRUE(c.contains(2));
  ASSERT_TRUE(c.contains(3));
  ASSERT_TRUE(m.empty());
}

TEST(test_map, create_from_ilist) {
  s21::map<int, int> m(
      {std::make_pair(1, 1), std::make_pair(2, 1), std::make_pair(3, 1)});
  ASSERT_EQ(m.size(), 3);
  ASSERT_TRUE(m.contains(1));
  ASSERT_TRUE(m.contains(2));
  ASSERT_TRUE(m.contains(3));
}

TEST(test_map, create_from_ilist_eq) {
  s21::map<int, int> m = {std::make_pair(1, 1), std::make_pair(2, 1),
                          std::make_pair(3, 1)};
  ASSERT_EQ(m.size(), 3);
  ASSERT_TRUE(m.contains(1));
  ASSERT_TRUE(m.contains(2));
  ASSERT_TRUE(m.contains(3));
}

TEST(test_map, at) {
  s21::map<int, int> m(
      {std::make_pair(1, 4), std::make_pair(2, 5), std::make_pair(3, 6)});
  ASSERT_EQ(m.at(1), 4);
  ASSERT_EQ(m.at(2), 5);
  ASSERT_EQ(m.at(3), 6);
  try {
    m.at(4);
  } catch (...) {
  }
}

TEST(test_map, square_braces_insert) {
  s21::map<int, int> m(
      {std::make_pair(1, 4), std::make_pair(2, 5), std::make_pair(3, 6)});
  ASSERT_EQ(m.size(), 3);
  ASSERT_EQ(m[1], 4);
  ASSERT_EQ(m[2], 5);
  ASSERT_EQ(m[3], 6);
  ASSERT_EQ(m[4], NULL);
}

TEST(test_map, iteration) {
  s21::map<int, int> m(
      {std::make_pair(1, 1), std::make_pair(2, 2), std::make_pair(3, 3)});
  s21::TreeIterator it = m.begin();
  ASSERT_EQ(*it, 1);
  it++;
  ASSERT_EQ(*it, 2);
  it++;
  ASSERT_EQ(*it, 3);
}

TEST(test_map, iteration_from_the_end) {
  s21::map<int, int> s;
  s.insert(61, 61);
  s.insert(52, 52);
  s.insert(85, 85);
  s.insert(76, 76);
  s.insert(93, 93);
  s.insert(100, 100);
  s.insert(50, 50);
  s.insert(54, 54);
  s21::TreeConstIterator it = s.cend();
  it--;
  ASSERT_EQ(s.size(), 8);
  ASSERT_EQ(*it, 100);
  it--;
  ASSERT_EQ(*it, 93);
  it--;
  ASSERT_EQ(*it, 85);
  it--;
  ASSERT_EQ(*it, 76);
  it--;
  ASSERT_EQ(*it, 61);
  it--;
  ASSERT_EQ(*it, 54);
  it--;
  ASSERT_EQ(*it, 52);
  it--;
  ASSERT_EQ(*it, 50);
}

TEST(test_map, clear) {
  s21::map<int, int> m(
      {std::make_pair(1, 1), std::make_pair(2, 1), std::make_pair(3, 1)});
  ASSERT_EQ(m.size(), 3);
  m.clear();
  ASSERT_EQ(m.size(), 0);
  ASSERT_TRUE(m.empty());
}

TEST(test_map, insert_pair) {
  s21::map<int, int> m;
  ASSERT_TRUE(m.empty());
  ASSERT_EQ(*std::get<0>(m.insert(std::make_pair(1, 5))), 5);
  ASSERT_TRUE(m.contains(1));
  ASSERT_EQ(m.size(), 1);
}

TEST(test_map, insert_pair_moved) {
  s21::map<int, int> m;
  ASSERT_TRUE(m.empty());
  ;
  ASSERT_EQ(*std::get<0>(m.insert(std::move(std::make_pair(1, 5)))), 5);
  ASSERT_TRUE(m.contains(1));
  ASSERT_EQ(m.size(), 1);
}

TEST(test_map, insert) {
  s21::map<int, int> m;
  ASSERT_TRUE(m.empty());
  m.insert(1, 5);
  ASSERT_EQ(*std::get<0>(m.insert(1, 5)), 5);
  ASSERT_TRUE(m.contains(1));
  ASSERT_EQ(m.size(), 1);
}

TEST(test_map, insert_not_unique) {
  s21::map<int, int> m;
  ASSERT_TRUE(m.empty());
  ASSERT_EQ(*std::get<0>(m.insert(1, 5)), 5);
  ASSERT_TRUE(m.contains(1));
  ASSERT_EQ(m.size(), 1);
  ASSERT_EQ(*std::get<0>(m.insert(1, 6)), 5);
  ASSERT_EQ(m.size(), 1);
}

TEST(test_map, insert_ilist) {
  s21::map<int, int> s;
  ASSERT_TRUE(s.empty());
  s.insert({std::make_pair(1, 1), std::make_pair(2, 1), std::make_pair(3, 1)});
  ASSERT_TRUE(s.contains(1));
  ASSERT_TRUE(s.contains(2));
  ASSERT_TRUE(s.contains(3));
  ASSERT_EQ(s.size(), 3);
}

TEST(test_map, insert_or_assign) {
  s21::map<int, int> m;
  ASSERT_EQ(*std::get<0>(m.insert(1, 5)), 5);
  ASSERT_TRUE(m.contains(1));
  ASSERT_EQ(m.size(), 1);
  ASSERT_EQ(std::get<1>(m.insert_or_assign(2, 6)), true);
  ASSERT_EQ(m.size(), 2);
  ASSERT_EQ(std::get<1>(m.insert_or_assign(1, 7)), false);
  s21::TreeIterator it = m.find(1);
  ASSERT_EQ(*it, 7);
}

TEST(test_map, insert_or_assign_moved) {
  s21::map<int, int> m;
  ASSERT_EQ(*std::get<0>(m.insert(1, 5)), 5);
  ASSERT_TRUE(m.contains(1));
  ASSERT_EQ(m.size(), 1);
  m.insert_or_assign(2, std::move(6));
  ASSERT_EQ(*std::get<0>(m.insert_or_assign(2, std::move(6))), 6);
  ASSERT_EQ(m.size(), 2);
  m.insert_or_assign(std::move(1), std::move(7));
  ASSERT_EQ(*std::get<0>(m.insert_or_assign(std::move(1), std::move(7))), 7);
  s21::TreeConstIterator it = m.find(1);
  ASSERT_EQ(*it, 7);
}

TEST(test_map, insert_many) {
  s21::map<int, int> s;
  ASSERT_TRUE(s.empty());
  s21::TreeConstIterator it = std::get<0>(s.insert_many(
      std::make_pair(1, 1), std::make_pair(2, 1), std::make_pair(3, 1)));
  ASSERT_EQ(*it, 1);
  ASSERT_TRUE(s.contains(1));
  ASSERT_TRUE(s.contains(2));
  ASSERT_TRUE(s.contains(3));
  ASSERT_EQ(s.size(), 3);
}

TEST(test_map, insert_many_false) {
  s21::map<int, int> m(
      {std::make_pair(1, 1), std::make_pair(2, 1), std::make_pair(3, 1)});
  ASSERT_EQ(false, (std::get<1>(m.insert_many(std::make_pair(1, 1),
                                              std::make_pair(2, 1),
                                              std::make_pair(3, 1)))));
}

TEST(test_map, erase) {
  s21::map<int, int> m;
  m.insert(1, 5);
  m.insert(2, 6);
  ASSERT_EQ(*m.erase(m.find(1)), 6);
  ASSERT_EQ(m.size(), 1);
  ASSERT_FALSE(m.contains(1));
}

TEST(test_map, erase_mult) {
  s21::map<int, int> s;
  s.insert(61, 61);
  s.insert(52, 52);
  s.insert(85, 85);
  s.insert(76, 76);
  s.insert(93, 93);
  s.insert(100, 100);
  s.insert(50, 50);
  s.insert(54, 54);
  s21::TreeConstIterator first = s.cbegin();
  s21::TreeConstIterator last = s.cbegin();
  first++;
  last++;
  last++;
  last++;
  ASSERT_EQ(*s.erase(first, last), 61);
  ASSERT_EQ(s.size(), 6);
  ASSERT_TRUE(s.contains(61));
  ASSERT_FALSE(s.contains(52));
  ASSERT_TRUE(s.contains(85));
  ASSERT_TRUE(s.contains(76));
  ASSERT_TRUE(s.contains(93));
  ASSERT_TRUE(s.contains(100));
  ASSERT_TRUE(s.contains(50));
  ASSERT_FALSE(s.contains(54));
}

TEST(test_map, erase_from_key) {
  s21::map<int, int> s;
  s.insert(61, 61);
  s.insert(52, 52);
  s.insert(85, 85);
  s.insert(76, 76);
  s.insert(93, 93);
  s.insert(100, 100);
  s.insert(50, 50);
  s.insert(54, 54);
  ASSERT_EQ(s.erase(93), 1);
  ASSERT_EQ(s.size(), 7);
  ASSERT_FALSE(s.contains(93));
}

TEST(test_map, swap) {
  s21::map<int, int> a(
      {std::make_pair(1, 1), std::make_pair(2, 1), std::make_pair(3, 1)});
  s21::map<int, int> b(
      {std::make_pair(4, 1), std::make_pair(5, 1), std::make_pair(6, 1)});
  a.swap(b);
  ASSERT_EQ(a.size(), 3);
  ASSERT_EQ(b.size(), 3);
  ASSERT_TRUE(b.contains(1));
  ASSERT_TRUE(b.contains(2));
  ASSERT_TRUE(b.contains(3));
  ASSERT_TRUE(a.contains(4));
  ASSERT_TRUE(a.contains(5));
  ASSERT_TRUE(a.contains(6));
}

TEST(test_map, extract_from_key) {
  s21::map<int, int> s;
  s.insert(61, 61);
  s.insert(52, 52);
  s.insert(85, 85);
  s.insert(76, 76);
  s.insert(93, 93);
  s.insert(100, 100);
  s.insert(50, 50);
  s.insert(54, 54);
  s21::Node n = s.extract(93);
  ASSERT_EQ(n.value, 93);
  ASSERT_EQ(s.size(), 7);
  ASSERT_FALSE(s.contains(93));
}

TEST(test_map, extract_from_pos) {
  s21::map<int, int> s;
  s.insert(61, 61);
  s.insert(52, 52);
  s.insert(85, 85);
  s.insert(76, 76);
  s.insert(93, 93);
  s.insert(100, 100);
  s.insert(50, 50);
  s.insert(54, 54);
  s21::TreeConstIterator it = s.begin();
  it++;
  s21::Node n = s.extract(it);
  ASSERT_EQ(n.value, 52);
  ASSERT_EQ(s.size(), 7);
  ASSERT_FALSE(s.contains(52));
}

TEST(test_map, merge) {
  s21::map<int, int> a(
      {std::make_pair(1, 1), std::make_pair(2, 1), std::make_pair(3, 1)});
  s21::map<int, int> b(
      {std::make_pair(4, 1), std::make_pair(5, 1), std::make_pair(6, 1)});
  a.merge(b);
  ASSERT_EQ(a.size(), 6);
  ASSERT_TRUE(a.contains(1));
  ASSERT_TRUE(a.contains(2));
  ASSERT_TRUE(a.contains(3));
  ASSERT_TRUE(a.contains(4));
  ASSERT_TRUE(a.contains(5));
  ASSERT_TRUE(a.contains(6));
}

TEST(test_map, count) {
  s21::map<int, int> s;
  s.insert(1, 1);
  ASSERT_EQ(s.count(1), 1);
  ASSERT_EQ(s.count(4), 0);
}

TEST(test_map, find_null) {
  s21::map<int, int> s;
  s.insert(1, 1);
  ASSERT_EQ(s.find(2).get_pointer(), nullptr);
}

TEST(test_map, lower_bound) {
  s21::map<int, int> s;
  s.insert(61, 1);
  s.insert(52, 1);
  s.insert(85, 1);
  s.insert(76, 1);
  s.insert(93, 1);
  s.insert(100, 1);
  s.insert(50, 1);
  s.insert(54, 1);
  s21::TreeIterator it = s.lower_bound(60);
  ASSERT_EQ(it.get_key(), 61);
}

TEST(test_map, upper_bound) {
  s21::map<int, int> s;
  s.insert(61, 1);
  s.insert(52, 1);
  s.insert(85, 1);
  s.insert(76, 1);
  s.insert(93, 1);
  s.insert(100, 1);
  s.insert(50, 1);
  s.insert(54, 1);
  s21::TreeIterator it = s.upper_bound(61);
  ASSERT_EQ(it.get_key(), 76);
}

TEST(test_map, is_equal) {
  s21::map<int, int> map;
  s21::map<int, int> other;
  map.insert(1, 0);
  other.insert(1, 0);
  ASSERT_EQ(map, other);
}

TEST(test_map, is_equal_false) {
  s21::map<int, int> map;
  s21::map<int, int> other;
  map.insert(1, 0);
  other.insert(1, 0);
  map.insert(2, 0);
  other.insert(3, 0);
  ASSERT_FALSE(map == other);
}

TEST(test_map, is_not_equal) {
  s21::map<int, int> map;
  s21::map<int, int> other;
  map.insert(2, 0);
  other.insert(1, 0);
  ASSERT_TRUE(map != other);
}

TEST(test_map, is_not_equal_false) {
  s21::map<int, int> map;
  s21::map<int, int> other;
  map.insert(1, 0);
  other.insert(1, 0);
  map.insert(2, 0);
  other.insert(2, 0);
  ASSERT_FALSE(map != other);
}

TEST(test_map, is_less) {
  s21::map<int, int> map;
  s21::map<int, int> other;
  map.insert(1, 0);
  other.insert(2, 0);
  ASSERT_TRUE(map < other);
}

TEST(test_map, is_less_false) {
  s21::map<int, int> map;
  s21::map<int, int> other;
  map.insert(3, 0);
  other.insert(2, 0);
  ASSERT_FALSE(map < other);
}

TEST(test_map, is_less_false_2) {
  s21::map<int, int> map;
  s21::map<int, int> other;
  map.insert(2, 0);
  other.insert(2, 0);
  ASSERT_FALSE(map < other);
}

TEST(test_map, is_less_or_eq) {
  s21::map<int, int> map;
  s21::map<int, int> other;
  map.insert(1, 0);
  other.insert(2, 0);
  ASSERT_TRUE(map <= other);
}

TEST(test_map, is_less_or_eq_2) {
  s21::map<int, int> map;
  s21::map<int, int> other;
  map.insert(2, 0);
  other.insert(2, 0);
  ASSERT_TRUE(map <= other);
}

TEST(test_map, is_less_or_eq_false) {
  s21::map<int, int> map;
  s21::map<int, int> other;
  map.insert(3, 0);
  other.insert(2, 0);
  ASSERT_FALSE(map <= other);
}

TEST(test_map, is_greater) {
  s21::map<int, int> map;
  s21::map<int, int> other;
  map.insert(2, 0);
  other.insert(1, 0);
  ASSERT_TRUE(map > other);
}

TEST(test_map, is_greater_false) {
  s21::map<int, int> map;
  s21::map<int, int> other;
  map.insert(2, 0);
  other.insert(3, 0);
  ASSERT_FALSE(map > other);
}

TEST(test_map, is_greated_false_2) {
  s21::map<int, int> map;
  s21::map<int, int> other;
  map.insert(2, 0);
  other.insert(2, 0);
  ASSERT_FALSE(map > other);
}

TEST(test_map, is_greater_or_eq) {
  s21::map<int, int> map;
  s21::map<int, int> other;
  map.insert(2, 0);
  other.insert(1, 0);
  ASSERT_TRUE(map >= other);
}

TEST(test_map, is_greater_or_eq_2) {
  s21::map<int, int> map;
  s21::map<int, int> other;
  map.insert(2, 0);
  other.insert(2, 0);
  ASSERT_TRUE(map >= other);
}

TEST(test_map, is_greater_or_eq_false) {
  s21::map<int, int> map;
  s21::map<int, int> other;
  map.insert(2, 0);
  other.insert(3, 0);
  ASSERT_FALSE(map >= other);
}
