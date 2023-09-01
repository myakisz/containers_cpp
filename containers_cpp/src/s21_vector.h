#ifndef S21_CONTAINERS_SRC_S21_VECTOR_H
#define S21_CONTAINERS_SRC_S21_VECTOR_H

#include <algorithm>
#include <stdexcept>
#include <utility>

namespace s21 {

using size_type = std::size_t;

namespace {
template <class T>
class VectorConstIterator {
 public:
  using value_type = const T;
  using reference = value_type &;
  using pointer = value_type *;
  using difference_type = std::ptrdiff_t;

  VectorConstIterator() noexcept { ptr = nullptr; }

  explicit VectorConstIterator(pointer other) noexcept { ptr = other; }

  VectorConstIterator(const VectorConstIterator &other) noexcept {
    ptr = other.ptr;
  }

  VectorConstIterator(VectorConstIterator &&other) noexcept {
    ptr = other.ptr;
    other.ptr = nullptr;
  }

  VectorConstIterator &operator=(pointer other) noexcept {
    ptr = other;
    return *this;
  }

  VectorConstIterator &operator=(const VectorConstIterator &other) noexcept {
    ptr = other.ptr;
    return *this;
  }

  VectorConstIterator &operator=(VectorConstIterator &&other) noexcept {
    std::swap(ptr, other.ptr);
    return *this;
  }

  ~VectorConstIterator() noexcept { ptr = nullptr; }

  pointer operator->() const noexcept { return ptr; }

  reference operator*() const noexcept { return *ptr; }

  reference operator[](size_type pos) const noexcept { return ptr[pos]; }

  VectorConstIterator operator+(
      const VectorConstIterator &other) const noexcept {
    return VectorConstIterator(ptr + other.ptr);
  }

  VectorConstIterator operator+(const difference_type offset) const noexcept {
    return VectorConstIterator(ptr + offset);
  }

  difference_type operator-(const VectorConstIterator &other) const noexcept {
    return ptr - other.ptr;
  }

  VectorConstIterator operator-(const difference_type offset) const noexcept {
    return ptr - offset;
  }

  VectorConstIterator &operator-=(const VectorConstIterator &other) noexcept {
    ptr -= other.ptr;
    return *this;
  }

  VectorConstIterator &operator-=(const difference_type offset) noexcept {
    ptr -= offset;
    return *this;
  }

  VectorConstIterator &operator++() noexcept {
    ++ptr;
    return *this;
  }

  VectorConstIterator &operator--() noexcept {
    --ptr;
    return *this;
  }

  VectorConstIterator operator++(int) noexcept {
    VectorConstIterator tmp = *this;
    ++ptr;
    return tmp;
  }

  VectorConstIterator operator--(int) noexcept {
    VectorConstIterator tmp = *this;
    --ptr;
    return tmp;
  }

  bool operator==(const VectorConstIterator &other) const noexcept {
    return ptr == other.ptr;
  }

  bool operator!=(const VectorConstIterator &other) const noexcept {
    return ptr != other.ptr;
  }

  bool operator<(const VectorConstIterator &other) const noexcept {
    return ptr < other.ptr;
  }

  bool operator<=(const VectorConstIterator &other) const noexcept {
    return ptr <= other.ptr;
  }

  bool operator>(const VectorConstIterator &other) const noexcept {
    return ptr > other.ptr;
  }

  bool operator>=(const VectorConstIterator &other) const noexcept {
    return ptr >= other.ptr;
  }

 protected:
  pointer ptr;
};

template <class T>
class VectorIterator : public VectorConstIterator<T> {
 public:
  using base = VectorConstIterator<T>;
  using value_type = T;
  using pointer = value_type *;

  explicit VectorIterator(pointer ptr) noexcept : base(ptr) {}
};
}  // namespace

template <class T>
class vector {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using pointer = T *;
  using const_pointer = const T *;
  using iterator = VectorIterator<value_type>;
  using const_iterator = VectorConstIterator<value_type>;

 public:
  vector() { nullify(); }

  explicit vector(size_type count, const_reference value) {
    init(count);
    std::fill(container_, container_ + count, value);
  }

  explicit vector(size_type count) : vector(count, value_type()) {}

  vector(const vector &v) {
    init(v.size());
    std::copy(v.container_, v.container_ + capacity_, container_);
  }

  vector(vector &&v) {
    size_ = capacity_ = v.size();
    container_ = v.container_;
    v.nullify();
  }

  vector(std::initializer_list<value_type> ilist) {
    init(ilist.size());
    std::copy(ilist.begin(), ilist.end(), container_);
  }

  ~vector() { deallocate(); }

  vector &operator=(const vector &other) {
    vector v(other);
    swap(v);
    return *this;
  }

  vector &operator=(vector &&other) noexcept {
    if (this != &other) {
      swap(other);
    }
    return *this;
  }

  vector &operator=(std::initializer_list<T> ilist) {
    if (size_ != ilist.size()) {
      delete[] container_;
      init(ilist.size());
    }
    std::copy(ilist.begin(), ilist.end(), container_);
    return *this;
  }

  void assign(size_type count, const_reference value) {
    *this = std::move(s21::vector(count, value));
  }

  void assign(std::initializer_list<T> ilist) { *this = ilist; }

  reference at(size_type pos) {
    if (pos >= size_) {
      throw std::out_of_range("Index out of range");
    }
    return operator[](pos);
  };

  const_reference at(size_type pos) const {
    if (pos >= size_) {
      throw std::out_of_range("Index out of range");
    }
    return operator[](pos);
  }

  reference operator[](size_type pos) { return container_[pos]; }

  const_reference operator[](size_type pos) const { return container_[pos]; }

  reference front() { return operator[](0); }

  const_reference front() const { return operator[](0); }

  reference back() { return operator[](size_ - 1); }

  const_reference back() const { return operator[](size_ - 1); }

  pointer data() noexcept { return container_; }

  const_pointer data() const noexcept { return container_; }

  iterator begin() noexcept { return iterator(container_); }

  const_iterator begin() const noexcept { return const_iterator(container_); }

  const_iterator cbegin() const noexcept { return const_iterator(container_); }

  iterator end() noexcept { return iterator(container_ + size_); }

  const_iterator end() const noexcept {
    return const_iterator(container_ + size_);
  }

  const_iterator cend() const noexcept {
    return const_iterator(container_ + size_);
  }

  bool empty() const noexcept { return begin() == end(); }

  size_type size() const noexcept { return size_; }

  size_type max_size() const noexcept {
    return std::numeric_limits<size_type>::max() / sizeof(vector<value_type>);
  }

  void reserve(size_type new_cap) {
    if (new_cap > max_size()) {
      throw std::length_error("capacity exceeds max size");
    }
    if (new_cap > capacity_) {
      recap(new_cap);
    }
  }

  size_type capacity() const noexcept { return capacity_; }

  void shrink_to_fit() { capacity_ = size_; }

  void clear() noexcept { size_ = 0; }

  iterator insert(const_iterator pos, const T &value) noexcept {
    return insert(pos, 1, value);
  }

  iterator insert(const_iterator pos, const T &&value) noexcept {
    return insert(pos, 1, std::move(value));
  }

  iterator insert(const_iterator pos, size_type count,
                  const T &value) noexcept {
    size_type position = &(*pos) - container_;
    if (position != size_) {
      s21::vector<value_type> result(*this);
      if (size_ + count >= capacity_) {
        result.reserve(size_ + count);
      }
      result.size_ += count;
      for (size_type i = position; i < position + count; i++) {
        if (i < size_) {
          result.container_[i + count] = result.container_[i];
        }
        result.container_[i] = value;
      }
      for (size_type i = position + count; i < result.size_; i++) {
        result.container_[i] = container_[i - count];
      }
      swap(result);
    } else {
      for (size_type i = 0; i < count; i++) {
        push_back(value);
      }
    }
    iterator it(position + container_);
    return it;
  }

  iterator insert(const_iterator pos, std::initializer_list<T> ilist) noexcept {
    size_type position = &(*pos) - container_;
    int count = 0;
    for (auto it = ilist.begin(); it < ilist.end(); it++) {
      const_iterator insert_it(const_cast<value_type *>(position + container_));
      for (int i = 0; i < count; i++) {
        insert_it++;
      }
      if (position == size_) {
        push_back(*it);
      } else {
        insert(insert_it, 1, *it);
      }
      count++;
    }
    iterator r_it(position + container_);
    return r_it;
  }

  template <class... Args>
  iterator insert_many(const_iterator pos, Args &&... args) {
    std::initializer_list ilist = {std::forward<Args>(args)...};
    return insert(pos, ilist);
  }

  template <class... Args>
  void insert_many_back(Args &&... args) {
    std::initializer_list ilist = {std::forward<Args>(args)...};
    auto pos = end();
    insert(pos, ilist);
  }

  iterator erase(const_iterator pos) noexcept {
    size_type position = &(*pos) - container_;
    if (position == size_ - 1) {
      size_--;
      return end();
    }
    for (size_type i = position; i < size_ - 1; i++) {
      container_[i] = container_[i + 1];
    }
    size_--;
    iterator it(position + container_);
    return it;
  }

  iterator erase(const_iterator first, const_iterator last) noexcept {
    size_type first_position = &(*first) - container_;
    size_type diff = &(*last) - container_ - first_position;
    if (last == cend()) {
      size_ -= diff;
      return end();
    }
    for (size_type i = first_position; i < size_ - diff; i++) {
      container_[i] = container_[i + diff];
    }
    size_ -= diff;
    iterator it(first_position + container_);
    return it;
  }

  void push_back(const T &value) {
    if (size_ == capacity_) {
      size_type new_size = (size_) ? (size_ * 2) : 1;
      recap(new_size);
    }
    container_[size_] = value;
    size_++;
  }

  void push_back(const T &&value) { push_back(value); }

  void pop_back() {
    size_--;
    if (size_ == capacity_ / 2) {
      recap(size_);
    }
  }

  void resize(size_type count) { resize(count, value_type()); }

  void resize(size_type count, const value_type &value) {
    if (count > size_) {
      recap(count);
      std::fill(container_ + size_, container_ + count, value);
    }
    size_ = count;
  }

  void swap(vector &other) noexcept {
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
    std::swap(container_, other.container_);
  }

  template <class U>
  friend bool operator==(const vector<U> &lhs, const vector<U> &rhs);

  template <class U>
  friend bool operator!=(const vector<U> &lhs, const vector<U> &rhs);

  template <class U>
  friend bool operator<(const vector<U> &lhs, const vector<U> &rhs);

  template <class U>
  friend bool operator<=(const vector<U> &lhs, const vector<U> &rhs);

  template <class U>
  friend bool operator>(const vector<U> &lhs, const vector<U> &rhs);

  template <class U>
  friend bool operator>=(const vector<U> &lhs, const vector<U> &rhs);

 private:
  void nullify() noexcept {
    size_ = capacity_ = 0;
    container_ = nullptr;
  }

  void init(size_type size) {
    nullify();
    size_ = size;
    recap(size);
  }

  void deallocate() noexcept {
    if (container_) {
      delete[] container_;
      container_ = nullptr;
    }
  }

  void recap() { recap(size_); }

  void recap(size_type new_cap) {
    if (!new_cap) {
      deallocate();
      nullify();
      return;
    }
    size_type old_cap = capacity_;
    if (new_cap - 1) {
      new_cap -= 1;
      while (new_cap & (new_cap - 1)) {
        new_cap &= (new_cap - 1);
      }
      new_cap <<= 1;
    }
    if (new_cap > max_size()) {
      throw std::length_error("capacity exceeds max size");
    }
    capacity_ = new_cap;
    pointer new_container = new value_type[capacity_];
    std::copy(container_, container_ + std::min(old_cap, capacity_),
              new_container);
    deallocate();
    container_ = new_container;
  }

  size_type size_;
  size_type capacity_;
  pointer container_;
};

template <class T>
bool operator==(const vector<T> &lhs, const vector<T> &rhs) {
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

template <class T>
bool operator!=(const vector<T> &lhs, const vector<T> &rhs) {
  return !(lhs == rhs);
}

template <class T>
bool operator<(const vector<T> &lhs, const vector<T> &rhs) {
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

template <class T>
bool operator<=(const vector<T> &lhs, const vector<T> &rhs) {
  return !(lhs > rhs);
}

template <class T>
bool operator>(const vector<T> &lhs, const vector<T> &rhs) {
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

template <class T>
bool operator>=(const vector<T> &lhs, const vector<T> &rhs) {
  return !(lhs < rhs);
}

}  // namespace s21

#endif  // S21_CONTAINERS_SRC_S21_VECTOR_H
