#include <gtest/gtest.h>

#include "s21_list.h"

TEST(test_list, init_default_list) {
  s21::list<int> lst;

  ASSERT_TRUE(lst.empty());
  ASSERT_EQ(lst.size(), 0);

  // don't do this
  // lst.front();
  // lst.back();

  lst.clear();
}

TEST(test_list, init_sized_list) {
  for (s21::size_type s = 1; s < 3; ++s) {
    s21::list<std::string> lst(s);
    ASSERT_FALSE(lst.empty());
    ASSERT_EQ(lst.size(), s);
    ASSERT_EQ(lst.front(), lst.back());
  }

  int value = 21;
  for (s21::size_type s = 1; s < 3; ++s) {
    s21::list<int> lst(s, value);
    ASSERT_FALSE(lst.empty());
    ASSERT_EQ(lst.size(), s);
    ASSERT_EQ(lst.front(), value);
    ASSERT_EQ(lst.back(), value);
  }
}

TEST(test_list, init_with_list_initialiser) {
  s21::list<int> lst0 = {};
  ASSERT_EQ(lst0.size(), 0);

  s21::list<int> lst1 = {1, 2, 3};
  ASSERT_EQ(lst1.size(), 3);
  ASSERT_EQ(lst1.front(), 1);
  ASSERT_EQ(lst1.back(), 3);

  //   s21::list<s21::list<int>> lst_ilst = {{1, 2}, {3, 4, 5}};
  //   s21::list<int> lst_front = {1, 2};
  //   s21::list<int> lst_back = {3, 4, 5};
  //   ASSERT_EQ(lst_ilst.size(), 2);
  //   ASSERT_EQ(lst_ilst.front(), lst_front);
  //   ASSERT_EQ(lst_ilst.back(), lst_back);
}

TEST(test_list, list_copy_constructor) {
  s21::list<int> lst{-1, 1};
  s21::list<int> lst_copy(lst);

  ASSERT_EQ(lst_copy.size(), 2);
  ASSERT_EQ(lst_copy.front(), -1);
  ASSERT_EQ(lst_copy.back(), 1);
}

TEST(test_list, list_move_constructor) {
  s21::list<int> lst{-1, 1};
  s21::list<int> lst_move(std::move(lst));

  ASSERT_EQ(lst_move.size(), 2);
  ASSERT_EQ(lst_move.front(), -1);
  ASSERT_EQ(lst_move.back(), 1);
  ASSERT_EQ(lst.size(), 0);
}

TEST(test_list, assignment_operators) {
  s21::list<int> lst{1, 2, 3};
  s21::list<int> alst;

  alst = lst;
  ASSERT_EQ(alst.size(), 3);
  ASSERT_EQ(alst.front(), 1);
  ASSERT_EQ(alst.back(), 3);

  alst = {-3, -2, -1};
  ASSERT_EQ(alst.size(), 3);
  ASSERT_EQ(alst.front(), -3);
  ASSERT_EQ(alst.back(), -1);

  alst = std::move(lst);
  ASSERT_EQ(alst.size(), 3);
  ASSERT_EQ(alst.front(), 1);
  ASSERT_EQ(alst.back(), 3);
  ASSERT_EQ(lst.size(), 3);
  ASSERT_EQ(lst.front(), -3);
  ASSERT_EQ(lst.back(), -1);
}

TEST(test_list, assign) {
  s21::list<char> chars;

  chars.assign(5, 'a');
  ASSERT_EQ(chars.size(), 5);
  for (auto el : chars) {
    ASSERT_EQ(el, 'a');
  }

  const std::string extra(6, 'b');
  chars.assign(extra.begin(), extra.end());
  ASSERT_EQ(chars.size(), 6);
  for (auto el : chars) {
    ASSERT_EQ(el, 'b');
  }

  chars.assign({
      'C',
      '1',
  });
  ASSERT_EQ(chars.size(), 2);
  ASSERT_EQ(chars.front(), 'C');
  ASSERT_EQ(chars.back(), '1');
}

TEST(test_list, push_pop_back) {
  s21::list<int> lst;

  lst.push_back(1);

  ASSERT_FALSE(lst.empty());
  ASSERT_EQ(lst.size(), 1);
  ASSERT_EQ(lst.back(), 1);

  lst.push_back(2);

  ASSERT_FALSE(lst.empty());
  ASSERT_EQ(lst.size(), 2);
  ASSERT_EQ(lst.back(), 2);

  lst.pop_back();
  ASSERT_FALSE(lst.empty());
  ASSERT_EQ(lst.size(), 1);
  ASSERT_EQ(lst.back(), 1);

  lst.pop_back();
  ASSERT_TRUE(lst.empty());
  ASSERT_EQ(lst.size(), 0);
  // ASSERT_EQ(lst.back(), 0); // no

  lst.pop_back();  // imp-def -> nothing is done
}

TEST(test_list, push_pop_front) {
  s21::list<int> lst;

  lst.push_front(1);

  ASSERT_FALSE(lst.empty());
  ASSERT_EQ(lst.size(), 1);
  ASSERT_EQ(lst.front(), 1);

  lst.push_front(2);

  ASSERT_FALSE(lst.empty());
  ASSERT_EQ(lst.size(), 2);
  ASSERT_EQ(lst.front(), 2);

  lst.pop_front();
  ASSERT_FALSE(lst.empty());
  ASSERT_EQ(lst.size(), 1);
  ASSERT_EQ(lst.back(), 1);

  lst.pop_front();
  ASSERT_TRUE(lst.empty());
  ASSERT_EQ(lst.size(), 0);
  // ASSERT_EQ(lst.front(), 0); // no

  lst.pop_front();  // imp-def -> nothing is done
}

TEST(test_list, list_comparisons) {
  s21::list<std::string> lst1{"hello", "world"};
  s21::list<std::string> lst_copy(lst1);
  s21::list<std::string> lst2{"hello", "C++"};

  ASSERT_EQ(lst1, lst_copy);
  ASSERT_FALSE(lst1 != lst_copy);
  ASSERT_NE(lst1, lst2);
}

TEST(test_list, to_string) {
  s21::list<double> lst0;
  s21::list<char> lst1{'A'};
  s21::list<std::string> lst2{"hello", "world"};
  s21::list<int> lst3{-1, 0, 1};

  ASSERT_EQ(s21::to_string(lst0), "[]");
  ASSERT_EQ(s21::to_string(lst1), "[A]");
  ASSERT_EQ(s21::to_string(lst2), "[hello, world]");
  ASSERT_EQ(s21::to_string(lst3), "[-1, 0, 1]");
}

TEST(test_list, list_iterator_comparisons) {
  s21::list<std::string> lst;

  ASSERT_EQ(lst.begin(), lst.end());
  ASSERT_EQ(lst.cbegin(), lst.cend());

  std::string value = "hello";
  lst.push_back(value);
  ASSERT_NE(lst.begin(), lst.end());
  ASSERT_EQ(*(lst.begin()), value);
  ASSERT_NE(lst.cbegin(), lst.cend());
  ASSERT_EQ(*(lst.cbegin()), value);
}

TEST(test_list, insert_in_empty) {
  s21::list<int> lst;

  auto it = lst.begin();
  lst.insert(it, 10);
  ASSERT_EQ(*(lst.begin()), 10);
  lst.insert(it, 20);
  it = lst.begin();
  ASSERT_EQ(*it, 10);
  it++;
  ASSERT_EQ(*it, 20);
}

TEST(test_list, inserts) {
  s21::list<int> c1;

  auto it = c1.begin();
  it = c1.insert(it, 100);
  ASSERT_EQ(*(c1.cbegin()), 100);

  it = c1.begin();
  it = c1.insert(it, 200);  // [200, 100]
  ASSERT_EQ(*it, *(c1.cbegin()));

  ++it;
  it = c1.insert(it, 2, 300);  // [200, 300, 300, 100]
  ASSERT_EQ(*(c1.cbegin()), 200);
  ASSERT_EQ(*it, 300);
  it++;
  ASSERT_EQ(*it, 300);
  it++;
  ASSERT_EQ(*it, 100);

  it = c1.begin();
  it = c1.insert(it, 0, 300);  // no changes
  ASSERT_EQ(it, c1.begin());

  it = c1.begin();
  it = c1.insert(it, {21, 42});
  ASSERT_EQ(*it, 21);
  it++;
  ASSERT_EQ(*it, 42);
}

TEST(test_list, erase) {
  s21::list<int> lst{0, 1, 2, 3};

  auto it1 = lst.erase(lst.begin());
  ASSERT_EQ(*it1, 1);
  it1 = lst.erase(lst.begin());
  ASSERT_EQ(*it1, 2);

  auto it2 = lst.erase(lst.begin(), lst.end());
  ASSERT_EQ(it2, lst.end());
}

TEST(test_list, reverse) {
  s21::list<int> lst{0, 1, 2, 3};

  lst.reverse();
  auto it = lst.begin();
  ASSERT_EQ(*it, 3);
  it++;
  ASSERT_EQ(*it, 2);
  it++;
  ASSERT_EQ(*it, 1);
  it++;
  ASSERT_EQ(*it, 0);
}

TEST(test_list, sort) {
  s21::list<int> lst{2, 0, 1, 3};
  lst.sort();
  auto it = lst.begin();
  ASSERT_EQ(*it, 0);
  it++;
  ASSERT_EQ(*it, 1);
  it++;
  ASSERT_EQ(*it, 2);
  it++;
  ASSERT_EQ(*it, 3);
}

TEST(test_list, sort_one_el) {
  s21::list<int> lst{2};
  lst.sort();
  auto it = lst.begin();
  ASSERT_EQ(*it, 2);
}

TEST(test_list, sort_descending) {
  s21::list<int> lst{9, 8, 7, 6};
  lst.sort();
  auto it = lst.begin();
  ASSERT_EQ(*it, 6);
  it++;
  ASSERT_EQ(*it, 7);
  it++;
  ASSERT_EQ(*it, 8);
  it++;
  ASSERT_EQ(*it, 9);
}

TEST(test_list, sort_equal) {
  s21::list<int> lst{9, 8, 7, 7};
  lst.sort();
  auto it = lst.begin();
  ASSERT_EQ(*it, 7);
  it++;
  ASSERT_EQ(*it, 7);
  it++;
  ASSERT_EQ(*it, 8);
  it++;
  ASSERT_EQ(*it, 9);
}

TEST(test_list, merge) {
  s21::list<int> lst1{1, 3};
  s21::list<int> lst2{2, 4};
  lst1.merge(lst2);
  auto it = lst1.begin();
  ASSERT_EQ(*it, 1);
  it++;
  ASSERT_EQ(*it, 2);
  it++;
  ASSERT_EQ(*it, 3);
  it++;
  ASSERT_EQ(*it, 4);
}

TEST(test_list, merge_equal) {
  s21::list<int> lst1{1, 3};
  s21::list<int> lst2{1, 3};
  lst1.merge(lst2);
  auto it = lst1.begin();
  ASSERT_EQ(*it, 1);
  it++;
  ASSERT_EQ(*it, 1);
  it++;
  ASSERT_EQ(*it, 3);
  it++;
  ASSERT_EQ(*it, 3);
}

TEST(test_list, splice_to_empty) {
  s21::list<int> lst1;
  s21::list<int> lst2{4, 5};
  auto pos = lst1.cbegin();
  lst1.splice(pos, lst2);
  auto it = lst1.begin();
  ASSERT_EQ(*it, 4);
  it++;
  ASSERT_EQ(*it, 5);
}

TEST(test_list, splice_to_the_end) {
  s21::list<int> lst1{1, 2};
  s21::list<int> lst2{3};
  auto pos = lst1.cbegin();
  pos++;
  lst1.splice(pos, lst2);
  auto it = lst1.begin();
  ASSERT_EQ(*it, 1);
  it++;
  ASSERT_EQ(*it, 2);
  it++;
  ASSERT_EQ(*it, 3);
  ASSERT_EQ(lst1.front(), 1);
  ASSERT_EQ(lst1.back(), 3);
}

TEST(test_list, splice_to_the_middle) {
  s21::list<int> lst1{1, 3};
  s21::list<int> lst2{2};
  auto pos = lst1.cbegin();
  lst1.splice(pos, lst2);
  auto it = lst1.begin();
  ASSERT_EQ(*it, 1);
  it++;
  ASSERT_EQ(*it, 2);
  it++;
  ASSERT_EQ(*it, 3);
  ASSERT_EQ(lst1.front(), 1);
  ASSERT_EQ(lst1.back(), 3);
}

TEST(test_list, unique_without_dublicates) {
  s21::list<int> lst1{1, 3};
  lst1.unique();
  auto it = lst1.begin();
  ASSERT_EQ(*it, 1);
  it++;
  ASSERT_EQ(*it, 3);
}

TEST(test_list, unique_with_dublicates) {
  s21::list<int> lst1{1, 1, 3};
  lst1.unique();
  auto it = lst1.begin();
  ASSERT_EQ(lst1.size(), 2);
  ASSERT_EQ(*it, 1);
  it++;
  ASSERT_EQ(*it, 3);
}

TEST(test_list, insert_many_to_head) {
  s21::list<int> lst1{3};
  auto it = lst1.begin();
  lst1.insert_many(it, 1, 2);

  it = lst1.begin();
  ASSERT_EQ(*it, 1);
  it++;
  ASSERT_EQ(*it, 2);
  it++;
  ASSERT_EQ(*it, 3);
}

TEST(test_list, insert_many_to_the_middle) {
  s21::list<int> lst1{1, 4};
  auto it = lst1.begin();
  it++;
  lst1.insert_many(it, 2, 3);

  it = lst1.begin();
  ASSERT_EQ(*it, 1);
  it++;
  ASSERT_EQ(*it, 2);
  it++;
  ASSERT_EQ(*it, 3);
  it++;
  ASSERT_EQ(*it, 4);
}

TEST(test_list, insert_many_tail) {
  s21::list<int> lst1{1};
  auto it = lst1.begin();
  it++;
  lst1.insert_many(it, 2, 3);

  it = lst1.begin();
  ASSERT_EQ(*it, 1);
  it++;
  ASSERT_EQ(*it, 2);
  it++;
  ASSERT_EQ(*it, 3);
}

TEST(test_list, insert_many_back) {
  s21::list<int> lst1{1};
  lst1.insert_many_back(2, 3);

  auto it = lst1.begin();
  ASSERT_EQ(*it, 1);
  it++;
  ASSERT_EQ(*it, 2);
  it++;
  ASSERT_EQ(*it, 3);
}

TEST(test_list, insert_many_front) {
  s21::list<int> lst1{3};
  lst1.insert_many_front(1, 2);

  auto it = lst1.begin();
  ASSERT_EQ(*it, 1);
  it++;
  ASSERT_EQ(*it, 2);
  it++;
  ASSERT_EQ(*it, 3);
}
