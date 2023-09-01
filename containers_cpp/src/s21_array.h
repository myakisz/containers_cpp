#ifndef S21_CONTAINERS_SRC_S21_ARRAY_H_
#define S21_CONTAINERS_SRC_S21_ARRAY_H_

#include <exception>
#include <iostream>
#include <string>

namespace s21 {

using diff_type = std::ptrdiff_t;
using size_type = std::size_t;

namespace {
template <class T>
class const_array_iterator {
 public:
  using iterator_category = std::random_access_iterator_tag;
  using reference = const T&;
  using pointer = const T*;

 public:
  constexpr const_array_iterator() noexcept : ptr(nullptr) {}

  constexpr const_array_iterator(pointer other) noexcept : ptr(other) {}

  constexpr pointer operator->() const noexcept { return ptr; }

  constexpr reference operator*() const noexcept { return *ptr; }

  constexpr reference operator[](size_type pos) const noexcept {
    return this->operator->()[pos];
  }

  constexpr const_array_iterator& operator+(
      const const_array_iterator& other) const noexcept {
    return const_array_iterator(ptr + other.ptr);
  }

  constexpr const_array_iterator& operator+(
      const diff_type offset) const noexcept {
    return const_array_iterator(ptr + offset);
  }

  constexpr const_array_iterator& operator+=(
      const const_array_iterator& other) noexcept {
    ptr += other.ptr;
    return *this;
  }

  constexpr const_array_iterator& operator+=(const diff_type offset) noexcept {
    ptr += offset;
    return *this;
  }

  constexpr const_array_iterator& operator-(
      const const_array_iterator& other) const noexcept {
    return const_array_iterator(ptr - other.ptr);
  }

  constexpr const_array_iterator operator-(
      const diff_type offset) const noexcept {
    return const_array_iterator(ptr - offset);
  }

  constexpr const_array_iterator& operator-=(
      const const_array_iterator& other) noexcept {
    ptr -= other.ptr;
    return *this;
  }

  constexpr const_array_iterator& operator-=(const diff_type offset) noexcept {
    ptr -= offset;
    return *this;
  }

  constexpr const_array_iterator& operator++() noexcept {
    ++ptr;
    return *this;
  }

  constexpr const_array_iterator& operator--() noexcept {
    --ptr;
    return *this;
  }

  constexpr const_array_iterator operator++(int) noexcept {
    const_array_iterator tmp = *this;
    ++ptr;
    return tmp;
  }

  constexpr const_array_iterator operator--(int) noexcept {
    const_array_iterator tmp = *this;
    --ptr;
    return tmp;
  }

  constexpr bool operator==(const const_array_iterator& other) const noexcept {
    return ptr == other.ptr;
  }

  constexpr bool operator!=(const const_array_iterator& other) const noexcept {
    return ptr != other.ptr;
  }

  constexpr bool operator<(const const_array_iterator& other) const noexcept {
    return ptr < other.ptr;
  }

  constexpr bool operator<=(const const_array_iterator& other) const noexcept {
    return ptr <= other.ptr;
  }

  constexpr bool operator>(const const_array_iterator& other) const noexcept {
    return ptr > other.ptr;
  }

  constexpr bool operator>=(const const_array_iterator& other) const noexcept {
    return ptr >= other.ptr;
  }

 protected:
  pointer ptr;
};

template <class T>
class array_iterator : public const_array_iterator<T> {
  using base = const_array_iterator<T>;
  using reference = T&;
  using pointer = T*;

 public:
  constexpr array_iterator(pointer ptr) noexcept : base(ptr) {}

  constexpr pointer operator->() const noexcept {
    return const_cast<reference>(base::operator->());
  }

  constexpr reference operator*() const noexcept {
    return const_cast<reference>(base::operator*());
  }

  constexpr reference operator[](size_type pos) const noexcept {
    return const_cast<reference>(base::operator[](pos));
  }

  constexpr array_iterator operator+(const diff_type offset) const noexcept {
    array_iterator tmp = *this;
    tmp += offset;
    return tmp;
  }

  constexpr array_iterator operator+(
      const array_iterator& other) const noexcept {
    array_iterator tmp = *this;
    tmp += other;
    return tmp;
  }

  constexpr array_iterator& operator+=(const diff_type offset) noexcept {
    base::operator+=(offset);
    return *this;
  }

  constexpr array_iterator& operator+=(const array_iterator& other) noexcept {
    base::operator+=(other);
    return *this;
  }

  constexpr array_iterator operator-(const diff_type offset) const noexcept {
    array_iterator tmp = *this;
    tmp -= offset;
    return tmp;
  }

  constexpr array_iterator operator-(
      const array_iterator& other) const noexcept {
    array_iterator tmp = *this;
    tmp -= other;
    return tmp;
  }

  constexpr array_iterator& operator-=(const diff_type offset) noexcept {
    base::operator-=(offset);
    return *this;
  }

  constexpr array_iterator& operator-=(const array_iterator& other) noexcept {
    base::operator-=(other);
    return *this;
  }

  constexpr array_iterator& operator++() noexcept {
    base::operator++();
    return *this;
  }

  constexpr array_iterator& operator--() noexcept {
    base::operator--();
    return *this;
  }

  constexpr array_iterator operator++(int) noexcept {
    array_iterator tmp = *this;
    base::operator++();
    return tmp;
  }

  constexpr array_iterator operator--(int) noexcept {
    array_iterator tmp = *this;
    base::operator--();
    return tmp;
  }
};
}  // namespace

template <class T, size_type N>
class array {
 public:
  using reference = T&;
  using const_reference = T const&;
  using pointer = T*;
  using const_pointer = T const*;
  using iterator = array_iterator<T>;
  using const_iterator = const_array_iterator<T>;

 public:
  constexpr array() { fill(0); }

  constexpr explicit array(T value) { fill(value); }

  constexpr array(const std::initializer_list<T>& items) : array() {
    check_length(items.size());
    auto it = begin();
    for (auto element : items) {
      *it = element;
      it++;
    }
  }

  constexpr array(array<T, N> const& other) noexcept {
    std::copy(other.arr, other.arr + N, arr);
  }

  constexpr array(array<T, N>&& other) noexcept {
    std::move(other.arr, other.arr + N, arr);
  }

  constexpr array& operator=(const std::initializer_list<T>& items) {
    check_length(items.size());
    fill(0);
    std::copy(items.begin(), items.end(), arr);
    return *this;
  }

  constexpr array& operator=(array const& other) {
    if (this != &other) {
      std::copy(other);
    }
    return *this;
  }

  constexpr array& operator=(array&& other) {
    if (this != &other) {
      std::move(other);
    }
    return *this;
  }

  ~array() = default;

  constexpr reference at(size_type pos) {
    check_pos(pos);
    return arr[pos];
  }

  constexpr const_reference at(size_type pos) const {
    check_pos(pos);
    return arr[pos];
  }

  constexpr reference operator[](size_type pos) { return arr[pos]; }

  constexpr const_reference operator[](size_type pos) const { return arr[pos]; }

  constexpr reference front() { return at(0); }

  constexpr const_reference front() const { return front(); }

  constexpr reference back() {
    size_type pos = (N) ? N - 1 : 0;
    return at(pos);
  }

  constexpr const_reference back() const { return back(); }

  constexpr pointer data() noexcept { return arr; }

  constexpr const_pointer data() const noexcept {
    return const_cast<const_pointer>(arr);
  }

  constexpr iterator begin() noexcept { return iterator(arr); }

  constexpr const_iterator begin() const noexcept {
    return const_iterator(arr);
  }

  constexpr const_iterator cbegin() const noexcept {
    return const_iterator(arr);
  }

  constexpr iterator end() noexcept { return iterator(arr + N); }

  constexpr const_iterator end() const noexcept {
    return const_iterator(arr + N);
  }

  constexpr const_iterator cend() const noexcept {
    return const_iterator(arr + N);
  }

  constexpr bool empty() const noexcept { return !N; }

  constexpr size_type size() const noexcept { return N; }

  constexpr size_type max_size() const noexcept { return N; }

  void fill(const_reference value) { std::fill(arr, arr + N, value); }

  void swap(array& other) noexcept { std::swap(arr, other.arr); }

  template <class U, size_type L>
  friend bool operator==(array<U, L> const& lhs, array<U, L> const& rhs);

  template <class U, size_type L>
  friend bool operator!=(array<U, L> const& lhs, array<U, L> const& rhs);

  template <class U, size_type L>
  friend bool operator<(array<U, L> const& lhs, array<U, L> const& rhs);

  template <class U, size_type L>
  friend bool operator<=(array<U, L> const& lhs, array<U, L> const& rhs);

  template <class U, size_type L>
  friend bool operator>(array<U, L> const& lhs, array<U, L> const& rhs);

  template <class U, size_type L>
  friend bool operator>=(array<U, L> const& lhs, array<U, L> const& rhs);

  template <class U, size_type L>
  friend std::ostream& operator<<(std::ostream& os, array<U, L> const& arr);

 private:
  constexpr void check_length(size_type osize) const {
    if (osize > N) {
      std::string errmsg = "other.size (";
      errmsg += std::to_string(osize);
      errmsg += ") > this.size (";
      errmsg += std::to_string(N) + ")";
      throw std::out_of_range(errmsg);
    }
  }

  constexpr void check_pos(size_type pos) const {
    if (!(pos < N)) {
      std::string errmsg = "pos = ";
      errmsg += std::to_string(N);
      errmsg += " is out of range";
      throw std::out_of_range(errmsg);
    }
  }

  T arr[N];
};

template <class T, size_type N>
bool operator==(array<T, N> const& lhs, array<T, N> const& rhs) {
  if (lhs.size() != rhs.size()) {
    return false;
  }
  for (size_type i = 0; i < lhs.size(); i++) {
    if (lhs[i] != rhs[i]) {
      return false;
    }
  }
  return true;
}

template <class T, size_type N>
bool operator!=(array<T, N> const& lhs, array<T, N> const& rhs) {
  return !(lhs == rhs);
}

template <class T, size_type N>
bool operator<(array<T, N> const& lhs, array<T, N> const& rhs) {
  size_type min_size = std::min(lhs.size(), rhs.size());
  for (size_type idx = 0; idx < min_size; ++idx) {
    if (lhs[idx] < rhs[idx]) {
      return true;
    } else if (lhs[idx] > rhs[idx]) {
      return false;
    }
  }
  return lhs.size() < rhs.size();
}

template <class T, size_type N>
bool operator<=(array<T, N> const& lhs, array<T, N> const& rhs) {
  return !(lhs > rhs);
}

template <class T, size_type N>
bool operator>(array<T, N> const& lhs, array<T, N> const& rhs) {
  size_type min_size = std::min(lhs.size(), rhs.size());
  for (size_type idx = 0; idx < min_size; ++idx) {
    if (lhs[idx] > rhs[idx]) {
      return true;
    } else if (lhs[idx] < rhs[idx]) {
      return false;
    }
  }
  return lhs.size() > rhs.size();
}

template <class T, size_type N>
bool operator>=(array<T, N> const& lhs, array<T, N> const& rhs) {
  return !(lhs < rhs);
}

template <class T, size_type N>
std::ostream& operator<<(std::ostream& os, array<T, N> const& arr) {
  os << "{";
  auto last = arr.cend() - 1;
  for (auto c = arr.cbegin(), e = arr.cend(); c != e; ++c) {
    os << *c;
    if (c < last) {
      os << ", ";
    }
  }
  os << "}";
  return os;
}

template <class T, size_type N>
void swap(array<T, N>& lhs, array<T, N>& rhs) noexcept {
  lhs.swap(rhs);
}

};  // namespace s21

#endif  // S21_CONTAINERS_SRC_S21_ARRAY_H_
