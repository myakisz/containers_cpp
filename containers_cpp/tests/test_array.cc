#include <gtest/gtest.h>

#include "s21_array.h"

TEST(test_array, zero_sized) {
  const s21::size_type size = 0;
  s21::array<int, size> arr;  // arr init fails if size is not const
  ASSERT_FALSE(arr.data() == nullptr);
  ASSERT_TRUE(arr.empty());
  ASSERT_EQ(arr.size(), size);
  ASSERT_EQ(arr.max_size(), size);

  s21::size_type pos = 0;
  ASSERT_THROW(arr.at(pos), std::out_of_range);
  // ASSERT_THROW(arr[pos], std::out_of_range);  // no bound checking is done
  ASSERT_THROW(arr.front(), std::out_of_range);
  ASSERT_THROW(arr.back(), std::out_of_range);

  ASSERT_EQ(arr.begin(), arr.end());
  ASSERT_EQ(arr.cbegin(), arr.cend());
  for (auto el : arr) {
    (void)el;  // to suppress [-Werror=unused-variable]
    ASSERT_TRUE(false);
  }
}

TEST(test_array, non_zero_sized) {
  const s21::size_type size = 1;
  s21::array<int, size> arr;
  ASSERT_FALSE(arr.data() == nullptr);
  ASSERT_FALSE(arr.empty());
  ASSERT_EQ(arr.size(), size);
  ASSERT_EQ(arr.max_size(), size);

  s21::size_type pos = 0;
  ASSERT_EQ(arr.at(pos), 0);
  ASSERT_EQ(arr.front(), arr.back());
  ASSERT_EQ(arr.data()[pos], 0);
  arr.at(pos) = 21;
  ASSERT_EQ(arr.at(pos), 21);
  pos = size;
  ASSERT_THROW(arr.at(size), std::out_of_range);
  // ASSERT_THROW(arr[pos], std::out_of_range);  // no bound checking is done

  ASSERT_NE(arr.begin(), arr.end());
  ASSERT_NE(arr.cbegin(), arr.cend());
}

TEST(test_array, fill_param_constructor) {
  int value = 42;
  const s21::size_type size = 2;
  s21::array<int, size> arr(value);

  ASSERT_FALSE(arr.empty());
  ASSERT_EQ(arr.size(), size);
  ASSERT_EQ(arr.max_size(), size);
  ASSERT_EQ(arr.front(), value);
  ASSERT_EQ(arr.back(), value);
}

TEST(test_array, initializer_list) {
  s21::array<int, 1> arr1 = {1};  // equal sizes
  s21::array<int, 2> arr2 = {2};  // size 2 > osize 1
  try {
    s21::array<int, 3> arr3 = {1, 2, 3, 4};  // size 3 < size 4
  } catch (std::out_of_range const& exc) {
    ASSERT_TRUE(1);
  }
}

TEST(test_array, copy_constructor) {
  int value = 42;
  const s21::size_type size = 2;
  s21::array<int, size> arr{value};
  s21::array<int, size> copy_arr{arr};

  ASSERT_EQ(arr, copy_arr);
}

TEST(test_array, copy_assignment) {
  int value = 42;
  const s21::size_type size = 2;
  const s21::array<int, size> arr{value};
  s21::array<int, size> copy_arr = arr;

  ASSERT_EQ(arr, copy_arr);
}

TEST(test_array, move_constructor) {
  int value = 42;
  const s21::size_type size = 2;
  s21::array<int, size> arr{value};
  s21::array<int, size> copy_arr{arr};
  s21::array<int, size> move_arr = s21::array<int, size>(std::move(arr));

  ASSERT_EQ(move_arr, copy_arr);
}

TEST(test_array, move_assignment) {
  int value = 42;
  const s21::size_type size = 2;
  s21::array<int, size> arr{value};
  s21::array<int, size> copy_arr{arr};
  s21::array<int, size> move_arr = std::move(arr);

  ASSERT_EQ(move_arr, copy_arr);
}

TEST(test_array, ilist_assignment) {
  int value = 42;
  s21::array<int, 2> arr(value);
  arr = {
      1,
  };

  ASSERT_EQ(arr[0], 1);
  ASSERT_EQ(arr[1], 0);
}

TEST(test_array, fill) {
  int value1 = 21;
  const s21::size_type size = 2;

  s21::array<int, 0> arr0;
  arr0.fill(value1);  // does not ruins the execflow

  s21::array<int, size> arr1;
  arr1.fill(value1);
  ASSERT_EQ(arr1.front(), value1);
  ASSERT_EQ(arr1.back(), value1);
}

TEST(test_array, swap) {
  int value11 = 6, value12 = 12, value21 = 21, value22 = 42;
  const s21::size_type size = 2;
  s21::array<int, size> arr1 = {value11, value12};
  s21::array<int, size> arr2 = {value21, value22};

  arr1.swap(arr2);

  ASSERT_EQ(arr1.front(), value21);
  ASSERT_EQ(arr1.back(), value22);
  ASSERT_EQ(arr1.size(), size);

  ASSERT_EQ(arr2.front(), value11);
  ASSERT_EQ(arr2.back(), value12);
  ASSERT_EQ(arr2.size(), size);

  s21::swap(arr1, arr2);

  ASSERT_EQ(arr2.front(), value21);
  ASSERT_EQ(arr2.back(), value22);
  ASSERT_EQ(arr2.size(), size);

  ASSERT_EQ(arr1.front(), value11);
  ASSERT_EQ(arr1.back(), value12);
  ASSERT_EQ(arr1.size(), size);
}

TEST(test_array, operators) {
  int value1 = 21, value2 = 42;
  const s21::size_type size = 1;

  s21::array<int, size> arr1{value1};
  std::array<int, size> std_arr1{value1};

  s21::array<int, size> arr2{value2};
  std::array<int, size> std_arr2{value2};

  ASSERT_EQ(arr1, arr1);
  ASSERT_EQ(std_arr1, std_arr1);

  ASSERT_NE(arr1, arr2);
  ASSERT_NE(std_arr1, std_arr2);

  ASSERT_LT(arr1, arr2);
  ASSERT_LT(std_arr1, std_arr2);

  ASSERT_LE(arr1, arr2);
  ASSERT_LE(std_arr1, std_arr2);

  ASSERT_GT(arr2, arr1);
  ASSERT_GT(std_arr2, std_arr1);

  ASSERT_GE(arr2, arr1);
  ASSERT_GE(std_arr2, std_arr1);
}

// https://stackoverflow.com/questions/33399594/making-a-user-defined-class-stdto-string-able
TEST(test_array, string_repr) {
  std::ostringstream ss;

  s21::array<int, 0> arr0;
  ss << arr0;
  ASSERT_EQ(ss.str(), "{}");
  ss.str("");
  ss.clear();

  s21::array<int, 1> arr1;
  ss << arr1;
  ASSERT_EQ(ss.str(), "{0}");
  ss.str("");
  ss.clear();

  s21::array<int, 2> arr2;
  ss << arr2;
  ASSERT_EQ(ss.str(), "{0, 0}");
  ss.str("");
  ss.clear();
}

// tests from cpp_reference

TEST(test_array, at_operation) {
  std::array<int, 6> data = {1, 2, 4, 5, 5, 6};

  ASSERT_EQ(data.size(), 6);

  ASSERT_EQ(data.at(0), 1);

  data.at(1) = 88;
  ASSERT_EQ(data.at(1), 88);

  ASSERT_THROW(data.at(6) = 666, std::out_of_range);
}

TEST(test_array, brackets_operator) {
  std::array<int, 4> numbers{2, 4, 6, 8};

  ASSERT_EQ(numbers[0], 2);
  ASSERT_EQ(numbers[1], 4);

  numbers[0] = 5;
  ASSERT_EQ(numbers[0], 5);
}

TEST(test_array, array_iteration) {
  int value = 12, ovalue = 21;
  const s21::size_type size = 2;
  s21::array<int, size> arr(value);

  s21::size_type icount = 0;
  // element-wise
  for (auto el : arr) {
    ASSERT_EQ(el, value);
    icount++;
  }
  ASSERT_EQ(size, icount);

  // pointer arithmetics
  icount = 0;
  for (auto it = arr.begin(), end = arr.end(); it != end; ++it) {
    ASSERT_EQ(*it, value);
    *it = ovalue;
    ASSERT_EQ(*it, arr[icount]);
    icount++;
  }
  ASSERT_EQ(size, icount);

  // backwards
  icount = 0;
  for (auto it = arr.end() - 1, start = arr.begin(); it >= start; --it) {
    ASSERT_EQ(*it, ovalue);
    *it = ovalue;
    ASSERT_EQ(arr[size - icount - 1], ovalue);
    icount++;
  }
  ASSERT_EQ(size, icount);
}

TEST(test_array, const_array_iteration) {
  int value = 42;
  const s21::size_type size = 2;
  const s21::array<int, size> arr(value);

  s21::size_type icount = 0;
  // element-wise
  for (auto el : arr) {
    ASSERT_EQ(el, value);
    icount++;
  }
  ASSERT_EQ(size, icount);

  // pointer arithmetics
  icount = 0;
  for (auto it = arr.cbegin(), end = arr.cend(); it < end; it++) {
    ASSERT_EQ(*it, value);
    icount++;
  }
  ASSERT_EQ(size, icount);

  // backwards
  icount = 0;
  for (auto it = arr.cend() - 1, start = arr.cbegin(); it >= start; it--) {
    ASSERT_EQ(*it, value);
    icount++;
  }
  ASSERT_EQ(size, icount);
}

TEST(test_array, empty_array_iterators) {
  const s21::size_type size = 0;
  s21::array<int, size> empty;

  ASSERT_EQ(empty.begin(), empty.end());
  ASSERT_EQ(empty.cbegin(), empty.cend());
}

TEST(test_array, non_empty_array_iterators) {
  const s21::size_type size = 2;
  s21::array<int, size> arr = {5, 4};

  auto start = arr.begin(), end = arr.end() - 1;
  auto cstart = arr.cbegin(), cend = arr.cend() - 1;

  ASSERT_NE(start, end);
  ASSERT_NE(start, end);

  ASSERT_EQ(*start, *cstart);
  ASSERT_EQ(*end, *cend);

  ASSERT_EQ(*start, 5);
  ASSERT_EQ(start[0], 5);
  ASSERT_EQ(*end, 4);
  ASSERT_EQ(start[size - 1], 4);

  ASSERT_EQ(*(start + 1), *end);
  ASSERT_EQ(*(end - 1), *start);

  // [de/in]crementing

  end--;
  ASSERT_EQ(*end, *start);
  end++;
  ASSERT_EQ(*end, *(arr.end() - 1));

  --end;
  ASSERT_EQ(*end, *start);
  ++end;
  ASSERT_EQ(*end, *(arr.end() - 1));

  start++;
  ASSERT_EQ(*end, *start);
  start--;
  ASSERT_EQ(*start, *arr.begin());

  ++start;
  ASSERT_EQ(*end, *start);
  --start;
  ASSERT_EQ(*start, *arr.begin());

  // comparing iterators themselves
  ASSERT_EQ(start, start);
  ASSERT_NE(start, end);
  ASSERT_LT(start, end);
  ASSERT_GE(end, start);
}

// vector comparison

TEST(test_array, eq_ne) {
  s21::array<int, 2> a{1};
  s21::array<int, 2> b{1};

  ASSERT_EQ(a, b);

  a[1] = 1;
  b[1] = 2;
  ASSERT_NE(a, b);

  a[1] = 2;
  ASSERT_EQ(b, a);
}

TEST(test_array, lt) {
  s21::array<int, 10> a{1, 2, 3};
  s21::array<int, 10> b(a);

  ASSERT_FALSE(a < b);  // {1, 2, 3} < {1, 2, 3}
  a[0] = 0;
  ASSERT_LT(a, b);  // {0, 2, 3} < {1, 2, 3}
  b[2] = 0;
  ASSERT_LT(a, b);  // {0, 2, 3} < {1, 2, 0}
  a[2] = 0;
  ASSERT_LT(a, b);  // {0, 2, 0} < {1, 2, 0}
  a[0] = 1;
  a[1] = 1;
  ASSERT_LT(a, b);  // {1, 1, 0} < {1, 2, 0}
  a[1] = 3;
  ASSERT_FALSE(a < b);  // {1, 3, 0} < {1, 2, 0}
  a[2] = 4;
  b[1] = 4;
  ASSERT_LT(a, b);  // {1, 3, 4} < {1, 4, 0}
  b[1] = 3;
  ASSERT_FALSE(a < b);  // {1, 3, 4} < {1, 3, 0}
}

TEST(test_array, le) {
  s21::array<int, 10> a{1, 2, 3};
  s21::array<int, 10> b(a);

  ASSERT_FALSE(a < b);  // {1, 2, 3} <= {1, 2, 3}
  a[0] = 0;
  ASSERT_LE(a, b);  // {0, 2, 3} <= {1, 2, 3}
  b[2] = 0;
  ASSERT_LE(a, b);  // {0, 2, 3} <= {1, 2, 0}
  a[2] = 0;
  ASSERT_LE(a, b);  // {0, 2, 0} <= {1, 2, 0}
  a[0] = 1;
  a[1] = 1;
  ASSERT_LE(a, b);  // {1, 1, 0} <= {1, 2, 0}
  a[1] = 3;
  ASSERT_FALSE(a < b);  // {1, 3, 0} <= {1, 2, 0}
  a[2] = 4;
  b[1] = 4;
  ASSERT_LE(a, b);  // {1, 3, 4} <= {1, 4, 0}
  b[1] = 3;
  ASSERT_FALSE(a < b);  // {1, 3, 4} <= {1, 3, 0}
}

TEST(test_array, gt) {
  s21::array<int, 10> a{1, 2, 3};
  s21::array<int, 10> b(a);

  ASSERT_FALSE(a > b);  // {1, 2, 3} > {1, 2, 3}
  a[2] = 4;
  ASSERT_GT(a, b);  // {1, 2, 4} > {1, 2, 3}
  b[2] = 0;
  ASSERT_GT(a, b);  // {1, 2, 4} > {1, 2, 0}
  b[1] = 3;
  ASSERT_FALSE(a >= b);  // {1, 2, 4} > {1, 3, 0}
  a[2] = 0;
  ASSERT_FALSE(a >= b);  // {1, 2, 0} > {1, 3, 0}
  a[1] = 0;
  a[0] = 2;
  ASSERT_GT(a, b);  // {2, 0, 0} > {1, 3, 0}
}

TEST(test_array, ge) {
  s21::array<int, 10> a{1, 2, 3};
  s21::array<int, 10> b(a);

  ASSERT_GE(a, b);  // {1, 2, 3} >= {1, 2, 3}
  a[2] = 4;
  ASSERT_GE(a, b);  // {1, 2, 4} >= {1, 2, 3}
  b[2] = 0;
  ASSERT_GE(a, b);  // {1, 2, 4} >= {1, 2, 0}
  b[1] = 3;
  ASSERT_FALSE(a >= b);  // {1, 2, 4} >= {1, 3, 0}
  a[2] = 0;
  ASSERT_FALSE(a >= b);  // {1, 2, 0} >= {1, 3, 0}
  a[1] = 0;
  a[0] = 2;
  ASSERT_GE(a, b);  // {2, 0, 0} >= {1, 3, 0}
}
