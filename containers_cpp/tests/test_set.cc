#include <gtest/gtest.h>

#include "../src/s21_set.h"

TEST(test_set, create_default_set) {
  s21::set<int> s;
  ASSERT_TRUE(s.empty());
}

TEST(test_set, copy) {
  s21::set<int> s({1, 2, 3});
  s21::set<int> c(s);
  ASSERT_EQ(s.size(), 3);
  ASSERT_TRUE(s.contains(1));
  ASSERT_TRUE(s.contains(2));
  ASSERT_TRUE(s.contains(3));
  ASSERT_EQ(c.size(), 3);
  ASSERT_TRUE(c.contains(1));
  ASSERT_TRUE(c.contains(2));
  ASSERT_TRUE(c.contains(3));
}

TEST(test_set, copy_eq) {
  s21::set<int> s({1, 2, 3});
  s21::set<int> c = s;
  ASSERT_EQ(s.size(), 3);
  ASSERT_TRUE(s.contains(1));
  ASSERT_TRUE(s.contains(2));
  ASSERT_TRUE(s.contains(3));
  ASSERT_EQ(c.size(), 3);
  ASSERT_TRUE(c.contains(1));
  ASSERT_TRUE(c.contains(2));
  ASSERT_TRUE(c.contains(3));
}

TEST(test_set, move) {
  s21::set<int> s({1, 2, 3});
  s21::set<int> c(std::move(s));
  ASSERT_EQ(c.size(), 3);
  ASSERT_TRUE(c.contains(1));
  ASSERT_TRUE(c.contains(2));
  ASSERT_TRUE(c.contains(3));
  ASSERT_TRUE(s.empty());
}

TEST(test_set, move_eq) {
  s21::set<int> s({1, 2, 3});
  s21::set<int> c = std::move(s);
  ASSERT_EQ(c.size(), 3);
  ASSERT_TRUE(c.contains(1));
  ASSERT_TRUE(c.contains(2));
  ASSERT_TRUE(c.contains(3));
  ASSERT_TRUE(s.empty());
}

TEST(test_set, create_from_ilist) {
  s21::set<int> s({1, 2, 3});
  ASSERT_EQ(s.size(), 3);
  ASSERT_TRUE(s.contains(1));
  ASSERT_TRUE(s.contains(2));
  ASSERT_TRUE(s.contains(3));
}

TEST(test_set, begin) {
  s21::set<int> s;
  s.insert(61);
  s.insert(52);
  s.insert(85);
  s.insert(76);
  s.insert(93);
  s.insert(100);
  s.insert(50);
  s.insert(54);
  s.insert(51);
  s21::TreeIterator it = s.begin();
  ASSERT_EQ(*it, 50);
  ASSERT_EQ(s.size(), 9);
  it++;
  ASSERT_EQ(*it, 51);
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
  ASSERT_EQ(*it, 93);
  it++;
  ASSERT_EQ(*it, 100);
}

TEST(test_set, const_it_to_it) {
  s21::set<int> s({1, 2, 3});
  s21::TreeConstIterator const_it = s.cbegin();
  s21::TreeIterator it = const_it;
  ASSERT_EQ(*it, 1);
}

TEST(test_set, iteration) {
  s21::set<int> s({1, 2, 3});
  s21::TreeIterator it = s.begin();
  ASSERT_EQ(*it, 1);
  it++;
  ASSERT_EQ(*it, 2);
  it++;
  ASSERT_EQ(*it, 3);
  ASSERT_TRUE(s.contains(1));
  ASSERT_TRUE(s.contains(2));
  ASSERT_TRUE(s.contains(3));
  ASSERT_EQ(s.size(), 3);
}

TEST(test_set, iteration_chars) {
  s21::set<char> s({'1', '2', '3'});
  s21::TreeIterator it = s.begin();
  ASSERT_EQ(*it, '1');
  it++;
  ASSERT_EQ(*it, '2');
  it++;
  ASSERT_EQ(*it, '3');
  ASSERT_TRUE(s.contains('1'));
  ASSERT_TRUE(s.contains('2'));
  ASSERT_TRUE(s.contains('3'));
  ASSERT_EQ(s.size(), 3);
}

TEST(test_set, iteration_strings) {
  s21::set<std::string> s({"12", "345", "6789"});
  s21::TreeIterator it = s.begin();
  ASSERT_EQ(*it, "12");
  it++;
  ASSERT_EQ(*it, "345");
  it++;
  ASSERT_EQ(*it, "6789");
  ASSERT_TRUE(s.contains("12"));
  ASSERT_TRUE(s.contains("345"));
  ASSERT_TRUE(s.contains("6789"));
  ASSERT_EQ(s.size(), 3);
}

TEST(test_set, iteration_from_the_end) {
  s21::set<int> s;
  s.insert(61);
  s.insert(52);
  s.insert(85);
  s.insert(76);
  s.insert(93);
  s.insert(100);
  s.insert(50);
  s.insert(54);
  s21::TreeIterator it = s.end();
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

TEST(test_set, mega_iteration) {
  s21::set<int> s({61, 85, 52, 76, 100, 50, 55, 54, 56});
  s21::TreeConstIterator it = s.cbegin();
  ASSERT_EQ(*it, 50);
  it++;
  ASSERT_EQ(*it, 52);
  it++;
  ASSERT_EQ(*it, 54);
  it++;
  ASSERT_EQ(*it, 55);
  it++;
  ASSERT_EQ(*it, 56);
  it++;
  ASSERT_EQ(*it, 61);
  it++;
  ASSERT_EQ(*it, 76);
  it++;
  ASSERT_EQ(*it, 85);
  it++;
  ASSERT_EQ(*it, 100);
}

TEST(test_set, mega_iteration_back) {
  s21::set<int> s({61, 85, 52, 76, 100, 50, 55, 54, 56});
  s21::TreeIterator it = s.end();
  it--;
  ASSERT_EQ(*it, 100);
  it--;
  ASSERT_EQ(*it, 85);
  it--;
  ASSERT_EQ(*it, 76);
  it--;
  ASSERT_EQ(*it, 61);
  it--;
  ASSERT_EQ(*it, 56);
  it--;
  ASSERT_EQ(*it, 55);
  it--;
  ASSERT_EQ(*it, 54);
  it--;
  ASSERT_EQ(*it, 52);
  it--;
  ASSERT_EQ(*it, 50);
}

TEST(test_set, super_mega_iteration) {
  s21::set<int> s({100, 50,  150, 25,  175, 75,  125, 20,  40,  60, 90,
                   110, 140, 190, 160, 10,  23,  30,  45,  55,  65, 80,
                   95,  105, 115, 130, 145, 155, 180, 170, 200, 43, 147});
  s21::TreeIterator it = s.begin();
  ASSERT_EQ(*it, 10);
  it++;
  ASSERT_EQ(*it, 20);
  it++;
  ASSERT_EQ(*it, 23);
  it++;
  ASSERT_EQ(*it, 25);
  it++;
  ASSERT_EQ(*it, 30);
  it++;
  ASSERT_EQ(*it, 40);
  it++;
  ASSERT_EQ(*it, 43);
  it++;
  ASSERT_EQ(*it, 45);
  it++;
  ASSERT_EQ(*it, 50);
  it++;
  ASSERT_EQ(*it, 55);
  it++;
  ASSERT_EQ(*it, 60);
  it++;
  ASSERT_EQ(*it, 65);
  it++;
  ASSERT_EQ(*it, 75);
  it++;
  ASSERT_EQ(*it, 80);
  it++;
  ASSERT_EQ(*it, 90);
  it++;
  ASSERT_EQ(*it, 95);
  it++;
  ASSERT_EQ(*it, 100);
  it++;
  ASSERT_EQ(*it, 105);
  it++;
  ASSERT_EQ(*it, 110);
  it++;
  ASSERT_EQ(*it, 115);
  it++;
  ASSERT_EQ(*it, 125);
  it++;
  ASSERT_EQ(*it, 130);
  it++;
  ASSERT_EQ(*it, 140);
  it++;
  ASSERT_EQ(*it, 145);
  it++;
  ASSERT_EQ(*it, 147);
  it++;
  ASSERT_EQ(*it, 150);
  it++;
  ASSERT_EQ(*it, 155);
  it++;
  ASSERT_EQ(*it, 160);
  it++;
  ASSERT_EQ(*it, 170);
  it++;
  ASSERT_EQ(*it, 175);
  it++;
  ASSERT_EQ(*it, 180);
  it++;
  ASSERT_EQ(*it, 190);
  it++;
  ASSERT_EQ(*it, 200);
}

TEST(test_set, super_mega_iteration_back) {
  s21::set<int> s({100, 50,  150, 25,  175, 75,  125, 20,  40,  60, 90,
                   110, 140, 190, 160, 10,  23,  30,  45,  55,  65, 80,
                   95,  105, 115, 130, 145, 155, 180, 170, 200, 43, 147});
  s21::TreeConstIterator it = s.cend();
  it--;
  ASSERT_EQ(*it, 200);
  it--;
  ASSERT_EQ(*it, 190);
  it--;
  ASSERT_EQ(*it, 180);
  it--;
  ASSERT_EQ(*it, 175);
  it--;
  ASSERT_EQ(*it, 170);
  it--;
  ASSERT_EQ(*it, 160);
  it--;
  ASSERT_EQ(*it, 155);
  it--;
  ASSERT_EQ(*it, 150);
  it--;
  ASSERT_EQ(*it, 147);
  it--;
  ASSERT_EQ(*it, 145);
  it--;
  ASSERT_EQ(*it, 140);
  it--;
  ASSERT_EQ(*it, 130);
  it--;
  ASSERT_EQ(*it, 125);
  it--;
  ASSERT_EQ(*it, 115);
  it--;
  ASSERT_EQ(*it, 110);
  it--;
  ASSERT_EQ(*it, 105);
  it--;
  ASSERT_EQ(*it, 100);
  it--;
  ASSERT_EQ(*it, 95);
  it--;
  ASSERT_EQ(*it, 90);
  it--;
  ASSERT_EQ(*it, 80);
  it--;
  ASSERT_EQ(*it, 75);
  it--;
  ASSERT_EQ(*it, 65);
  it--;
  ASSERT_EQ(*it, 60);
  it--;
  ASSERT_EQ(*it, 55);
  it--;
  ASSERT_EQ(*it, 50);
  it--;
  ASSERT_EQ(*it, 45);
  it--;
  ASSERT_EQ(*it, 43);
  it--;
  ASSERT_EQ(*it, 40);
  it--;
  ASSERT_EQ(*it, 30);
  it--;
  ASSERT_EQ(*it, 25);
  it--;
  ASSERT_EQ(*it, 23);
  it--;
  ASSERT_EQ(*it, 20);
  it--;
  ASSERT_EQ(*it, 10);
  it--;
  ASSERT_EQ(*it, 10);
}

TEST(test_set, insert_pair) {
  s21::set<int> s;
  ASSERT_TRUE(s.empty());
  ASSERT_EQ(*std::get<0>(s.insert(5)), 5);
  ASSERT_TRUE(s.contains(5));
  ASSERT_EQ(s.size(), 1);
}

TEST(test_set, insert_ilist) {
  s21::set<int> s;
  ASSERT_TRUE(s.empty());
  s.insert({1, 2, 3});
  ASSERT_TRUE(s.contains(1));
  ASSERT_TRUE(s.contains(2));
  ASSERT_TRUE(s.contains(3));
  ASSERT_EQ(s.size(), 3);
}

TEST(test_set, insert_not_unique) {
  s21::set<int> s;
  ASSERT_TRUE(s.empty());
  ASSERT_EQ(std::get<1>(s.insert(5)), true);
  ASSERT_TRUE(s.contains(5));
  ASSERT_EQ(s.size(), 1);
  ASSERT_EQ(*std::get<0>(s.insert(5)), 5);
  ASSERT_EQ(s.size(), 1);
}

TEST(test_set, insert_many) {
  s21::set<int> s;
  ASSERT_TRUE(s.empty());
  ASSERT_EQ(1, (*std::get<0>(s.insert_many(1, 2, 3))));
  ASSERT_TRUE(s.contains(1));
  ASSERT_TRUE(s.contains(2));
  ASSERT_TRUE(s.contains(3));
  ASSERT_EQ(s.size(), 3);
}

TEST(test_set, insert_many_false) {
  s21::set<int> s({1, 2, 3});
  ASSERT_EQ(false, (std::get<1>(s.insert_many(1, 2, 3))));
}

TEST(test_set, erase_at_const_pos) {
  s21::set<int> s;
  s.insert(61);
  s.insert(52);
  s.insert(85);
  s.insert(76);
  s.insert(93);
  s.insert(100);
  s.insert(50);
  s.insert(54);
  s21::TreeConstIterator it = s.find(52);
  it = s.erase(it);
  ASSERT_EQ(*it, 54);
  ASSERT_EQ(s.size(), 7);
}

TEST(test_set, erase_last_at_const_pos) {
  s21::set<int> s;
  s.insert(61);
  s.insert(52);
  s.insert(85);
  s.insert(76);
  s.insert(93);
  s.insert(100);
  s.insert(50);
  s.insert(54);
  s21::TreeConstIterator it = s.find(100);
  s21::TreeIterator it2 = s.erase(it);
  it2--;
  ASSERT_EQ(*it2, 93);
  ASSERT_EQ(s.size(), 7);
  ASSERT_FALSE(s.contains(100));
}

TEST(test_set, erase_mult) {
  s21::set<int> s;
  s.insert(61);
  s.insert(52);
  s.insert(85);
  s.insert(76);
  s.insert(93);
  s.insert(100);
  s.insert(50);
  s.insert(54);
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

TEST(test_set, erase_to_the_end) {
  s21::set<int> s;
  s.insert(61);
  s.insert(52);
  s.insert(85);
  s.insert(76);
  s.insert(93);
  s.insert(100);
  s.insert(50);
  s.insert(54);
  s21::TreeConstIterator first = s.cbegin();
  first++;
  s21::TreeConstIterator last = s.cend();
  s21::TreeIterator it2 = s.erase(first, last);
  it2--;
  ASSERT_EQ(*it2, 50);
  ASSERT_EQ(s.size(), 1);
}

TEST(test_set, erase_all) {
  s21::set<int> s;
  s.insert(61);
  s.insert(52);
  s.insert(85);
  s.insert(76);
  s.insert(93);
  s.insert(100);
  s.insert(50);
  s.insert(54);
  s21::TreeConstIterator first = s.cbegin();
  s21::TreeConstIterator last = s.cend();
  s.erase(first, last);
  ASSERT_EQ(s.size(), 0);
}

TEST(test_set, erase_from_key) {
  s21::set<int> s;
  s.insert(61);
  s.insert(52);
  s.insert(85);
  s.insert(76);
  s.insert(93);
  s.insert(100);
  s.insert(50);
  s.insert(54);
  ASSERT_EQ(s.erase(93), 1);
  ASSERT_EQ(s.size(), 7);
  ASSERT_FALSE(s.contains(93));
}

TEST(test_set, swap) {
  s21::set<int> a({1, 2});
  s21::set<int> b({4});
  a.swap(b);
  ASSERT_TRUE(b.contains(1));
  ASSERT_TRUE(a.contains(4));
}

TEST(test_set, extract_from_key) {
  s21::set<int> s;
  s.insert(61);
  s.insert(52);
  s.insert(85);
  s.insert(76);
  s.insert(93);
  s.insert(100);
  s.insert(50);
  s.insert(54);
  s21::Node n = s.extract(93);
  ASSERT_EQ(n.value, 93);
  ASSERT_EQ(s.size(), 7);
  ASSERT_FALSE(s.contains(93));
}

TEST(test_set, extract_from_pos) {
  s21::set<int> s;
  s.insert(61);
  s.insert(52);
  s.insert(85);
  s.insert(76);
  s.insert(93);
  s.insert(100);
  s.insert(50);
  s.insert(54);
  s21::TreeConstIterator it = s.cbegin();
  it++;
  s21::Node n = s.extract(it);
  ASSERT_EQ(n.value, 52);
  ASSERT_EQ(s.size(), 7);
  ASSERT_FALSE(s.contains(52));
}

TEST(test_set, merge) {
  s21::set<int> a({1, 2, 3});
  s21::set<int> b({3, 4, 5});
  a.merge(b);
  ASSERT_EQ(a.size(), 5);
  s21::TreeIterator it = a.begin();
  ASSERT_EQ(*it, 1);
  it++;
  ASSERT_EQ(*it, 2);
  it++;
  ASSERT_EQ(*it, 3);
  it++;
  ASSERT_EQ(*it, 4);
  it++;
  ASSERT_EQ(*it, 5);
}

TEST(test_set, clear) {
  s21::set<int> s({1, 2, 3});
  s.clear();
  ASSERT_EQ(s.size(), 0);
  ASSERT_TRUE(s.empty());
}

TEST(test_set, count) {
  s21::set<int> s({1, 2, 3});
  ASSERT_EQ(s.size(), 3);
  ASSERT_EQ(s.count(1), 1);
  ASSERT_EQ(s.count(4), 0);
}

TEST(test_set, find) {
  s21::set<int> s;
  s.insert(61);
  s.insert(52);
  s.insert(85);
  s.insert(76);
  s.insert(93);
  s.insert(100);
  s.insert(50);
  s.insert(54);
  s21::TreeIterator it = s.find(100);
  ASSERT_EQ(*it, 100);
}

TEST(test_set, lower_bound) {
  s21::set<int> s;
  s.insert(61);
  s.insert(52);
  s.insert(85);
  s.insert(76);
  s.insert(93);
  s.insert(100);
  s.insert(50);
  s.insert(54);
  s21::TreeIterator it = s.lower_bound(60);
  ASSERT_EQ(*it, 61);
  s21::TreeIterator it2 = s.lower_bound(101);
  it2--;
  ASSERT_EQ(*it2, 100);
}

TEST(test_set, upper_bound) {
  s21::set<int> s;
  s.insert(61);
  s.insert(52);
  s.insert(85);
  s.insert(76);
  s.insert(93);
  s.insert(100);
  s.insert(50);
  s.insert(54);
  s21::TreeIterator it = s.upper_bound(61);
  ASSERT_EQ(*it, 76);
}

TEST(test_set, upper_bound_end) {
  s21::set<int> s;
  s.insert(61);
  s.insert(52);
  s.insert(85);
  s.insert(76);
  s.insert(93);
  s.insert(100);
  s.insert(50);
  s.insert(54);
  s21::TreeIterator it = s.upper_bound(1000);
  it--;
  ASSERT_EQ(*it, 100);
}

TEST(test_set, is_equal) {
  s21::set<int> set;
  s21::set<int> other;
  set.insert(1);
  other.insert(1);
  ASSERT_EQ(set, other);
}

TEST(test_set, is_equal_false) {
  s21::set<int> set;
  s21::set<int> other;
  set.insert(1);
  other.insert(1);
  set.insert(2);
  other.insert(3);
  ASSERT_FALSE(set == other);
}

TEST(test_set, is_not_equal) {
  s21::set<int> set;
  s21::set<int> other;
  set.insert(2);
  other.insert(1);
  ASSERT_TRUE(set != other);
}

TEST(test_set, is_not_equal_false) {
  s21::set<int> set;
  s21::set<int> other;
  set.insert(1);
  other.insert(1);
  set.insert(2);
  other.insert(2);
  ASSERT_FALSE(set != other);
}

TEST(test_set, is_less) {
  s21::set<int> set;
  s21::set<int> other;
  set.insert(1);
  other.insert(2);
  ASSERT_TRUE(set < other);
}

TEST(test_set, is_less_false) {
  s21::set<int> set;
  s21::set<int> other;
  set.insert(3);
  other.insert(2);
  ASSERT_FALSE(set < other);
}

TEST(test_set, is_less_false_2) {
  s21::set<int> set;
  s21::set<int> other;
  set.insert(2);
  other.insert(2);
  ASSERT_FALSE(set < other);
}

TEST(test_set, is_less_or_eq) {
  s21::set<int> set;
  s21::set<int> other;
  set.insert(1);
  other.insert(2);
  ASSERT_TRUE(set <= other);
}

TEST(test_set, is_less_or_eq_2) {
  s21::set<int> set;
  s21::set<int> other;
  set.insert(2);
  other.insert(2);
  ASSERT_TRUE(set <= other);
}

TEST(test_set, is_less_or_eq_false) {
  s21::set<int> set;
  s21::set<int> other;
  set.insert(3);
  other.insert(2);
  ASSERT_FALSE(set <= other);
}

TEST(test_set, is_greater) {
  s21::set<int> set;
  s21::set<int> other;
  set.insert(2);
  other.insert(1);
  ASSERT_TRUE(set > other);
}

TEST(test_set, is_greater_false) {
  s21::set<int> set;
  s21::set<int> other;
  set.insert(2);
  other.insert(3);
  ASSERT_FALSE(set > other);
}

TEST(test_set, is_greated_false_2) {
  s21::set<int> set;
  s21::set<int> other;
  set.insert(2);
  other.insert(2);
  ASSERT_FALSE(set > other);
}

TEST(test_set, is_greater_or_eq) {
  s21::set<int> set;
  s21::set<int> other;
  set.insert(2);
  other.insert(1);
  ASSERT_TRUE(set >= other);
}

TEST(test_set, is_greater_or_eq_2) {
  s21::set<int> set;
  s21::set<int> other;
  set.insert(2);
  other.insert(2);
  ASSERT_TRUE(set >= other);
}

TEST(test_set, is_greater_or_eq_false) {
  s21::set<int> set;
  s21::set<int> other;
  set.insert(2);
  other.insert(3);
  ASSERT_FALSE(set >= other);
}
