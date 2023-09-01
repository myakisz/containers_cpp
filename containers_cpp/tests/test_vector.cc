#include <gtest/gtest.h>

#include <vector>

#include "s21_vector.h"

// ctors and dtors

TEST(test_vector, default_constructor) {
  s21::vector<std::string> v;
  ASSERT_EQ(0, v.size());
  ASSERT_EQ(0, v.capacity());
  ASSERT_TRUE(v.empty());
}

TEST(test_vector, count_value_constructor) {
  std::size_t n = 5;
  std::string val = std::string("Hello");
  s21::vector<std::string> v(n, val);

  ASSERT_EQ(n, v.size());
  ASSERT_EQ(8, v.capacity());
  for (std::size_t i = 0; i < n; ++i) {
    ASSERT_EQ(v[i], val);
  }

  n = 1;
  s21::vector<int> dv(n);
  ASSERT_EQ(n, dv.size());
  ASSERT_EQ(n, dv.capacity());
  for (std::size_t i = 0; i < n; ++i) {
    ASSERT_EQ(dv[i], int());
  }
}

TEST(test_vector, copy_constructor) {
  std::size_t n = 5;
  s21::vector<int> const v(n);
  s21::vector<int> c(v);

  ASSERT_EQ(v.size(), c.size());
  ASSERT_EQ(v.capacity(), c.capacity());
  for (std::size_t i = 0; i < n; ++i) {
    ASSERT_EQ(v[i], c[i]);
  }
}

TEST(test_vector, move_constructor) {
  std::size_t n = 3;
  int val = 2;
  s21::vector<int> v(n, val);
  s21::vector<int> m(std::move(v));

  ASSERT_EQ(m.size(), n);
  ASSERT_TRUE(m[0] == val);
  ASSERT_TRUE(m[0] == m[1]);
  ASSERT_TRUE(v.empty());
}

TEST(test_vector, ilist_constructor) {
  std::size_t n = 2;
  s21::vector<int> v({1, 2});
  s21::vector<int> empty({});

  ASSERT_EQ(0, empty.size());
  ASSERT_EQ(0, empty.capacity());

  ASSERT_EQ(n, v.size());
  ASSERT_EQ(n, v.capacity());
  ASSERT_EQ(v[0], 1);
  ASSERT_EQ(v[1], 2);
}

TEST(test_vector, copy_assignment) {
  std::size_t n = 2;
  s21::vector<int> v({1, 2});
  s21::vector<int> c;
  c = v;

  ASSERT_TRUE(n == v.size());
  ASSERT_TRUE(v.size() == c.size());
  ASSERT_TRUE(n == v.capacity());
  ASSERT_TRUE(v.capacity() == c.capacity());
  ASSERT_TRUE(c[0] == 1);
  ASSERT_TRUE(c[1] == 2);
}

TEST(test_vector, ilist_assignment) {
  std::size_t n = 5;
  s21::vector<int> v;
  v = {1, 2, 3, 4, 5};

  ASSERT_EQ(n, v.size());
  ASSERT_EQ(8, v.capacity());
  for (std::size_t i = 0; i < n; ++i) {
    ASSERT_EQ(v[i], i + 1);
  }

  v = {1, 2};
  ASSERT_EQ(2, v.size());
  ASSERT_EQ(2, v.capacity());
  for (std::size_t i = 0; i < 2; ++i) {
    ASSERT_EQ(v[i], i + 1);
  }
}

TEST(test_vector, assign) {
  std::vector<char> chars;
  std::size_t n;

  n = 5;
  chars.assign(n, 'a');
  for (std::size_t i = 0; i < n; ++i) {
    ASSERT_EQ(chars[i], 'a');
  }

  n = 6;
  const std::string extra(n, 'b');
  chars.assign(extra.begin(), extra.end());
  for (std::size_t i = 0; i < n; ++i) {
    ASSERT_EQ(chars[i], 'b');
  }

  chars.assign({'C', '+', '+', '1', '1'});
  ASSERT_EQ(chars[0], 'C');
  ASSERT_EQ(chars[1], chars[2]);
  ASSERT_EQ(chars[3], chars[4]);
}

// element access

TEST(test_vector, at) {
  s21::vector<int> v({1, 2, 3, 4, 5});
  const std::string cval = "Hello";
  const s21::vector<std::string> cv{cval};

  ASSERT_EQ(v.at(0), 1);
  v.at(1) = -2;
  ASSERT_EQ(v.at(1), -2);

  ASSERT_THROW(v.at(6), std::out_of_range);

  ASSERT_EQ(cv.at(0), cval);
  ASSERT_THROW(cv.at(1), std::out_of_range);
  // cv.at(0) = "World"  // no way
}

TEST(test_vector, front_back) {
  s21::vector<int> v{1, 2};

  ASSERT_EQ(v.front(), 1);
  ASSERT_EQ(v.back(), 2);
}

TEST(test_vector, vector_data) {
  s21::vector<std::string> v{"Lol", "Kek"};
  std::string *ptr = v.data();

  for (auto it = v.begin(); it != v.end(); ++it) {
    ASSERT_EQ(*it, *ptr);
    ptr++;
  }
}

// capacity

TEST(test_vector, empty) {
  s21::vector<int> v;
  ASSERT_TRUE(v.empty());
  ASSERT_EQ(v.size(), 0);
}

TEST(test_vector, reserve) {
  s21::vector<int> v{1, 2, 3, 4, 5};

  v.reserve(10);
  ASSERT_EQ(v.capacity(), 16);
  ASSERT_EQ(v.size(), 5);
  ASSERT_EQ(v.front(), 1);
  ASSERT_EQ(v.back(), 5);

  v.reserve(2);
  ASSERT_EQ(v.capacity(), 16);
}

TEST(test_vector, shrink_to_fit) {
  s21::vector<int> v{1, 2, 3, 4, 5};

  v.shrink_to_fit();
  ASSERT_EQ(5, v.capacity());
  ASSERT_EQ(v.back(), 5);

  v.pop_back();
  v.shrink_to_fit();
  ASSERT_EQ(4, v.capacity());
  ASSERT_EQ(v.back(), 4);
}

// modifiers

TEST(test_vector, insert) {
  s21::vector<int> v({1, 2, 3, 4, 5});
  s21::VectorConstIterator i = v.cbegin();
  i++;
  ASSERT_EQ(*v.insert(i, 10), 10);
  ASSERT_EQ(v[0], 1);
  ASSERT_EQ(v[1], 10);
  ASSERT_EQ(v[2], 2);
  ASSERT_EQ(v[3], 3);
  ASSERT_EQ(v[4], 4);
  ASSERT_EQ(v[5], 5);
  ASSERT_EQ(v.size(), 6);
}

TEST(test_vector, insert_end) {
  s21::vector<int> v({1, 2, 3, 4, 5});
  s21::VectorConstIterator i = v.cend();
  ASSERT_EQ(*v.insert(i, 10), 10);
  ASSERT_EQ(v[0], 1);
  ASSERT_EQ(v[1], 2);
  ASSERT_EQ(v[2], 3);
  ASSERT_EQ(v[3], 4);
  ASSERT_EQ(v[4], 5);
  ASSERT_EQ(v[5], 10);
  ASSERT_EQ(v.size(), 6);
}

TEST(test_vector, insert_double_ref) {
  s21::vector<int> v({1, 2, 3, 4, 5});
  s21::VectorIterator i = v.begin();
  i++;
  ASSERT_EQ(*v.insert(i, std::move(10)), 10);
  ASSERT_EQ(v[0], 1);
  ASSERT_EQ(v[1], 10);
  ASSERT_EQ(v[2], 2);
  ASSERT_EQ(v[3], 3);
  ASSERT_EQ(v[4], 4);
  ASSERT_EQ(v[5], 5);
  ASSERT_EQ(v.size(), 6);
}

TEST(test_vector, insert_count_last) {
  s21::vector<int> v({1, 2, 3, 4, 5});
  s21::VectorIterator i = v.begin();
  i++;
  i++;
  i++;
  i++;
  ASSERT_EQ(*v.insert(i, 3, 10), 10);
  ASSERT_EQ(v[0], 1);
  ASSERT_EQ(v[1], 2);
  ASSERT_EQ(v[2], 3);
  ASSERT_EQ(v[3], 4);
  ASSERT_EQ(v[4], 10);
  ASSERT_EQ(v[5], 10);
  ASSERT_EQ(v[6], 10);
  ASSERT_EQ(v[7], 5);
  ASSERT_EQ(v.size(), 8);
}

TEST(test_vector, insert_count_end) {
  s21::vector<int> v({1, 2, 3, 4, 5});
  s21::VectorConstIterator i = v.cend();
  ASSERT_EQ(*v.insert(i, 3, 10), 10);
  ASSERT_EQ(v[0], 1);
  ASSERT_EQ(v[1], 2);
  ASSERT_EQ(v[2], 3);
  ASSERT_EQ(v[3], 4);
  ASSERT_EQ(v[4], 5);
  ASSERT_EQ(v[5], 10);
  ASSERT_EQ(v[6], 10);
  ASSERT_EQ(v[7], 10);
  ASSERT_EQ(v.size(), 8);
}

TEST(test_vector, insert_mult) {
  s21::vector<int> v({1, 2, 3, 4, 5});
  s21::VectorIterator i = v.begin();
  i++;
  ASSERT_EQ(*v.insert(i, 3, 10), 10);
  ASSERT_EQ(v[0], 1);
  ASSERT_EQ(v[1], 10);
  ASSERT_EQ(v[2], 10);
  ASSERT_EQ(v[3], 10);
  ASSERT_EQ(v[4], 2);
  ASSERT_EQ(v[5], 3);
  ASSERT_EQ(v[6], 4);
  ASSERT_EQ(v[7], 5);
  ASSERT_EQ(v.size(), 8);
}

TEST(test_vector, insert_zero) {
  s21::vector<int> v({1, 2, 3, 4, 5});
  s21::VectorIterator i = v.begin();
  i++;
  ASSERT_EQ(*v.insert(i, 0, 10), 2);
  ASSERT_EQ(v[0], 1);
  ASSERT_EQ(v[1], 2);
  ASSERT_EQ(v[2], 3);
  ASSERT_EQ(v[3], 4);
  ASSERT_EQ(v[4], 5);
  ASSERT_EQ(v.size(), 5);
}

TEST(test_vector, insert_ilist) {
  s21::vector<int> v({1, 2, 3, 4, 5});
  s21::VectorIterator i = v.begin();
  i++;
  ASSERT_EQ(*v.insert(i, {10, 11, 12}), 10);
  ASSERT_EQ(v[0], 1);
  ASSERT_EQ(v[1], 10);
  ASSERT_EQ(v[2], 11);
  ASSERT_EQ(v[3], 12);
  ASSERT_EQ(v[4], 2);
  ASSERT_EQ(v[5], 3);
  ASSERT_EQ(v[6], 4);
  ASSERT_EQ(v[7], 5);
  ASSERT_EQ(v.size(), 8);
}

TEST(test_vector, insert_ilist_end) {
  s21::vector<int> v({1, 2, 3, 4, 5});
  s21::VectorIterator i = v.end();
  ASSERT_EQ(*v.insert(i, {10, 11, 12}), 10);
  ASSERT_EQ(v[0], 1);
  ASSERT_EQ(v[1], 2);
  ASSERT_EQ(v[2], 3);
  ASSERT_EQ(v[3], 4);
  ASSERT_EQ(v[4], 5);
  ASSERT_EQ(v[5], 10);
  ASSERT_EQ(v[6], 11);
  ASSERT_EQ(v[7], 12);
  ASSERT_EQ(v.size(), 8);
}

TEST(test_vector, insert_ilist_empty) {
  s21::vector<int> v({1, 2, 3, 4, 5});
  s21::VectorConstIterator i = v.cbegin();
  i++;
  ASSERT_EQ(*v.insert(i, {}), 2);
  ASSERT_EQ(v[0], 1);
  ASSERT_EQ(v[1], 2);
  ASSERT_EQ(v[2], 3);
  ASSERT_EQ(v[3], 4);
  ASSERT_EQ(v[4], 5);
  ASSERT_EQ(v.size(), 5);
}

TEST(test_vector, vector_erase) {
  s21::vector<int> v({1, 2, 3, 4, 5});
  s21::VectorConstIterator i = v.cbegin();
  i++;
  ASSERT_EQ(*v.erase(i), 3);
  ASSERT_EQ(v[0], 1);
  ASSERT_EQ(v[1], 3);
  ASSERT_EQ(v[2], 4);
  ASSERT_EQ(v[3], 5);
  ASSERT_EQ(v.size(), 4);
}

TEST(test_vector, vector_erase_last) {
  s21::vector<int> v({1, 2});
  s21::VectorConstIterator i = v.cbegin();

  i++;
  auto it = v.erase(i);
  ASSERT_EQ(it, v.cend());
  ASSERT_EQ(v[0], 1);
  ASSERT_EQ(v.size(), 1);
}

TEST(test_vector, vector_erase_mult) {
  s21::vector<int> v({1, 2, 3, 4, 5});
  s21::VectorConstIterator i = v.cbegin();
  i++;
  s21::VectorConstIterator j = i;
  j++;
  j++;
  ASSERT_EQ(*v.erase(i, j), 4);
  ASSERT_EQ(v[0], 1);
  ASSERT_EQ(v[1], 4);
  ASSERT_EQ(v[2], 5);
  ASSERT_EQ(v.size(), 3);
}

TEST(test_vector, vector_erase_more) {
  s21::vector<int> v({1, 2, 3, 4, 5});
  s21::VectorConstIterator i = v.cbegin();
  s21::VectorConstIterator j = v.cbegin();
  j++;
  j++;
  j++;
  j++;
  ASSERT_EQ(*v.erase(i, j), 5);
  ASSERT_EQ(v[0], 5);
  ASSERT_EQ(v.size(), 1);
}

TEST(test_vector, vector_erase_to_the_end) {
  s21::vector<int> v({1, 2, 3, 4, 5});
  s21::VectorConstIterator i = v.cbegin();
  s21::VectorConstIterator j = v.cend();

  i++;
  auto it = v.erase(i, j);
  ASSERT_EQ(it, v.cend());
  ASSERT_EQ(v[0], 1);
  ASSERT_EQ(v.size(), 1);
}

TEST(test_vector, vector_erase_all) {
  s21::vector<int> v({1, 2, 3, 4, 5});
  s21::VectorConstIterator i = v.cbegin();
  s21::VectorConstIterator j = v.cend();
  ASSERT_EQ(v.erase(i, j), v.begin());
  ASSERT_TRUE(v.empty());
}

TEST(test_vector, vector_erase_less) {
  s21::vector<int> v({1, 2, 3, 4, 5});
  s21::VectorIterator i = v.begin();
  s21::VectorIterator j = v.begin();
  j++;
  j++;
  j++;
  ASSERT_EQ(*v.erase(i, j), 4);
  ASSERT_EQ(v[0], 4);
  ASSERT_EQ(v[1], 5);
  ASSERT_EQ(v.size(), 2);
}

TEST(test_vector, erase_zero) {
  s21::vector<int> v({1, 2, 3, 4, 5});
  s21::VectorIterator i = v.begin();
  ASSERT_EQ(*v.erase(i, i), 1);
  ASSERT_EQ(v.size(), 5);
}

TEST(test_vector, push_back) {
  s21::vector<std::string> v;

  v.push_back(std::move("1"));
  ASSERT_EQ(1, v.size());
  ASSERT_EQ(1, v.capacity());

  v.push_back("-2");
  ASSERT_EQ(v.back(), "-2");
  ASSERT_EQ(2, v.size());
  ASSERT_EQ(2, v.capacity());

  std::string val = "3";
  v.push_back(val);
  ASSERT_EQ(v.back(), val);
  ASSERT_EQ(v.size(), 3);
  ASSERT_EQ(v.capacity(), 4);
}

TEST(test_vector, pop_back) {
  s21::vector<int> v{1, 2, 3};

  ASSERT_EQ(v.size(), 3);
  ASSERT_EQ(v.capacity(), 4);

  v.pop_back();
  ASSERT_EQ(v.size(), 2);
  ASSERT_EQ(v.capacity(), 2);

  v.pop_back();
  ASSERT_EQ(v.size(), 1);
  ASSERT_EQ(v.capacity(), 1);

  v.pop_back();
  ASSERT_EQ(v.size(), 0);
  ASSERT_EQ(v.capacity(), 0);
}

TEST(test_vector, resize) {
  s21::vector<int> v{1, 2, 3, 4, 5};

  v.resize(2);

  ASSERT_EQ(v.front(), 1);
  ASSERT_EQ(v.back(), 2);

  ASSERT_EQ(v.capacity(), 8);
  ASSERT_EQ(v.size(), 2);

  v.resize(4);

  ASSERT_EQ(v.front(), 1);
  ASSERT_EQ(v.back(), 0);

  ASSERT_EQ(v.capacity(), 4);
  ASSERT_EQ(v.size(), 4);

  v.resize(0);
  ASSERT_EQ(v.capacity(), 4);
  ASSERT_EQ(v.size(), 0);
}

TEST(test_vector, swap) {
  s21::vector<int> a{1, 2, 3, 4, 5};
  s21::vector<int> a_copy = a;

  s21::vector<int> b{6, 7, 8, 9, 10};
  s21::vector<int> b_copy = b;

  a.swap(b);

  ASSERT_EQ(a, b_copy);
  ASSERT_EQ(b, a_copy);
}

// vector comparison

TEST(test_vector, eq_ne) {
  s21::vector<int> a{1};
  s21::vector<int> b{1};

  ASSERT_EQ(a, b);
  a.push_back(1);
  ASSERT_NE(a, b);
  b.push_back(2);
  ASSERT_NE(b, a);
  a[1] = 2;
  ASSERT_EQ(b, a);
}

TEST(test_vector, lt) {
  s21::vector<int> a{1, 2, 3};
  s21::vector<int> b(a);

  ASSERT_FALSE(a < b);  // {1, 2, 3} < {1, 2, 3}
  a[0] = 0;
  ASSERT_LT(a, b);  // {0, 2, 3} < {1, 2, 3}
  b.pop_back();
  ASSERT_LT(a, b);  // {0, 2, 3} < {1, 2}
  a.pop_back();
  ASSERT_LT(a, b);  // {0, 2} < {1, 2}
  a[0] = 1;
  a[1] = 1;
  ASSERT_LT(a, b);  // {1, 1} < {1, 2}
  a[1] = 3;
  ASSERT_FALSE(a < b);  // {1, 3} < {1, 2}
  a.push_back(4);
  b[1] = 4;
  ASSERT_LT(a, b);  // {1, 3, 4} < {1, 4}
  b[1] = 3;
  ASSERT_FALSE(a < b);  // {1, 3, 4} < {1, 3}
}

TEST(test_vector, le) {
  s21::vector<int> a{1, 2, 3};
  s21::vector<int> b(a);

  ASSERT_LE(a, b);  // {1, 2, 3} <= {1, 2, 3}
  a[0] = 0;
  ASSERT_LE(a, b);  // {0, 2, 3} <= {1, 2, 3}
  b.pop_back();
  ASSERT_LE(a, b);  // {0, 2, 3} <= {1, 2}
  a.pop_back();
  ASSERT_LE(a, b);  // {0, 2} <= {1, 2}
  a[0] = 1;
  a[1] = 1;
  ASSERT_LE(a, b);  // {1, 1} <= {1, 2}
  a[1] = 3;
  ASSERT_FALSE(a <= b);  // {1, 3} <= {1, 2}
  a.push_back(4);
  b[1] = 4;
  ASSERT_LE(a, b);  // {1, 3, 4} <= {1, 4}
  b[1] = 3;
  ASSERT_GT(a, b);
  ASSERT_FALSE(a <= b);  // {1, 3, 4} <= {1, 3}
}

TEST(test_vector, gt) {
  s21::vector<int> a{1, 2, 3};
  s21::vector<int> b(a);

  ASSERT_FALSE(a > b);  // {1, 2, 3} > {1, 2, 3}
  a[2] = 4;
  ASSERT_GT(a, b);  // {1, 2, 4} > {1, 2, 3}
  b.pop_back();
  ASSERT_GT(a, b);  // {1, 2, 4} > {1, 2}
  b[1] = 3;
  ASSERT_FALSE(a > b);  // {1, 2, 4} > {1, 3}
  a.pop_back();
  ASSERT_FALSE(a > b);  // {1, 2} > {1, 3}
  a.pop_back();
  a[0] = 2;
  ASSERT_GT(a, b);  // {2} > {1, 3}
}

TEST(test_vector, ge) {
  s21::vector<int> a{1, 2, 3};
  s21::vector<int> b(a);

  ASSERT_GE(a, b);  // {1, 2, 3} >= {1, 2, 3}
  a[2] = 4;
  ASSERT_GE(a, b);  // {1, 2, 4} >= {1, 2, 3}
  b.pop_back();
  ASSERT_GE(a, b);  // {1, 2, 4} >= {1, 2}
  b[1] = 3;
  ASSERT_FALSE(a >= b);  // {1, 2, 4} >= {1, 3}
  a.pop_back();
  ASSERT_FALSE(a >= b);  // {1, 2} >= {1, 3}
  a.pop_back();
  a[0] = 2;
  ASSERT_GE(a, b);  // {2} >= {1, 3}
}

// iterators

TEST(test_vector, iterators) {
  s21::vector<char> empty;
  ASSERT_EQ(empty.begin(), empty.cend());

  s21::vector<int> mv{1};
  std::vector<int> sv{1};

  auto mit = mv.begin();
  auto sit = sv.begin();

  ASSERT_EQ(*mit, *(sv.begin()));
  ASSERT_EQ(*sit, *(mv.begin()));

  mit++;
  sit++;
  ASSERT_NE(sit, sv.begin());
  ASSERT_NE(mit, mv.begin());

  mit--;
  sit--;
  ASSERT_EQ(*mit, *(sv.begin()));
  ASSERT_EQ(*sit, *(mv.begin()));

  ASSERT_EQ(--(mv.cend()), mv.begin());
}

TEST(test_vector, insert_many_to_head) {
  s21::vector<int> lst1{3};
  auto it = lst1.begin();
  lst1.insert_many(it, 1, 2);

  it = lst1.begin();
  ASSERT_EQ(*it, 1);
  it++;
  ASSERT_EQ(*it, 2);
  it++;
  ASSERT_EQ(*it, 3);
}

TEST(test_vector, insert_many_to_the_middle) {
  s21::vector<int> lst1{1, 4};
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

TEST(test_vector, insert_many_tail) {
  s21::vector<int> lst1{1};
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

TEST(test_vector, insert_many_back) {
  s21::vector<int> lst1{1};
  lst1.insert_many_back(2, 3);

  auto it = lst1.begin();
  ASSERT_EQ(*it, 1);
  it++;
  ASSERT_EQ(*it, 2);
  it++;
  ASSERT_EQ(*it, 3);
}
