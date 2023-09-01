#ifndef S21_CONTAINERS_SRC_S21_STACK_H
#define S21_CONTAINERS_SRC_S21_STACK_H

#include <exception>
#include <iostream>
#include <string>

#include "s21_vector.h"

namespace s21 {
template <class T, class Container = s21::vector<T>>
class stack {
 public:
  using value_type = T;
  using reference = value_type &;
  using const_reference = const reference;
  using size_type = std::size_t;
  using container_type = Container;

  stack() = default;

  explicit stack(const container_type &cont) : c_(cont) {}

  stack(const stack &other) { *this = other; }

  stack(stack &&other) { *this = std::move(other); }

  stack(std::initializer_list<value_type> const &items) : c_(items) {}

  stack &operator=(const stack &other) {
    c_ = other.c_;
    return *this;
  }

  stack &operator=(stack &&other) {
    c_ = std::move(other.c_);
    return *this;
  }

  stack &operator=(std::initializer_list<value_type> const &items) {
    c_ = std::move(container_type(items));
    return *this;
  }

  ~stack() noexcept { c_.clear(); }

  reference top() {
    size_type len = size();
    if (len) {
      return c_[len - 1];
    }
    throw std::out_of_range("empty stack");
  }

  const_reference top() const {
    size_type len = size();
    if (len) {
      return c_[len - 1];
    }
    throw std::out_of_range("empty stack");
  }

  bool empty() const { return c_.empty(); }

  size_type size() const { return c_.size(); }

  void push(const_reference value) { c_.insert(c_.end(), value); }

  void push(value_type &&value) { c_.insert(c_.end(), std::move(value)); }

  template <class... Args>
  void insert_many_front(Args &&... args) {
    std::initializer_list ilist = {std::forward<Args>(args)...};
    for (auto el : ilist) {
      push(el);
    }
  }

  void pop() { c_.pop_back(); }

  void swap(stack &other) noexcept { std::swap(c_, other.c_); }

  template <class U, class C>
  friend bool operator==(const stack<U, C> &stack1, const stack<U, C> &stack2);

  template <class U, class C>
  friend bool operator!=(const stack<U, C> &stack1, const stack<U, C> &stack2);

  template <class U, class C>
  friend bool operator<(const stack<U, C> &stack1, const stack<U, C> &stack2);

  template <class U, class C>
  friend bool operator<=(const stack<U, C> &stack1, const stack<U, C> &stack2);

  template <class U, class C>
  friend bool operator>(const stack<U, C> &stack1, const stack<U, C> &stack2);

  template <class U, class C>
  friend bool operator>=(const stack<U, C> &stack1, const stack<U, C> &stack2);

 private:
  container_type c_{};
};

template <class T, class C>
bool operator==(const stack<T, C> &stack1, const stack<T, C> &stack2) {
  return stack1.c_ == stack2.c_;
}

template <class T, class C>
bool operator!=(const stack<T, C> &stack1, const stack<T, C> &stack2) {
  return stack1.c_ != stack2.c_;
}

template <class T, class C>
bool operator<(const stack<T, C> &stack1, const stack<T, C> &stack2) {
  return stack1.c_ < stack2.c_;
}

template <class T, class C>
bool operator<=(const stack<T, C> &stack1, const stack<T, C> &stack2) {
  return stack1.c_ <= stack2.c_;
}

template <class T, class C>
bool operator>(const stack<T, C> &stack1, const stack<T, C> &stack2) {
  return stack1.c_ > stack2.c_;
}

template <class T, class C>
bool operator>=(const stack<T, C> &stack1, const stack<T, C> &stack2) {
  return stack1.c_ >= stack2.c_;
}

template <class T, class C>
void swap(stack<T, C> &lhs, stack<T, C> &rhs) noexcept {
  lhs.swap(rhs);
}

}  // namespace s21

#endif  // S21_CONTAINERS_SRC_S21_STACK_H
