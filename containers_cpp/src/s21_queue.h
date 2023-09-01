#ifndef S21_CONTAINERS_SRC_S21_QUEUE_H
#define S21_CONTAINERS_SRC_S21_QUEUE_H

#include <exception>
#include <iostream>
#include <string>

#include "s21_list.h"

namespace s21 {
template <class T, class Container = s21::list<T>>
class queue {
 public:
  using value_type = T;
  using reference = value_type &;
  using const_reference = const reference;
  using size_type = std::size_t;
  using container_type = Container;

  queue() = default;

  explicit queue(const container_type &cont) : c_(cont) {}

  queue(const queue &other) { *this = other; }

  queue(queue &&other) { *this = std::move(other); }

  queue(std::initializer_list<value_type> const &items) : c_(items) {}

  queue &operator=(const queue &other) {
    c_ = other.c_;
    return *this;
  }

  queue &operator=(queue &&other) {
    c_ = std::move(other.c_);
    return *this;
  }

  queue &operator=(std::initializer_list<value_type> const &items) {
    c_ = std::move(container_type(items));
    return *this;
  }

  ~queue() noexcept { c_.clear(); }

  reference front() { return c_.front(); }

  const_reference front() const { return c_.front(); }

  reference back() { return c_.back(); }

  const_reference back() const { return c_.back(); }

  bool empty() const { return c_.empty(); }

  size_type size() const { return c_.size(); }

  void push(const_reference value) { c_.insert(c_.end(), value); }

  void push(value_type &&value) { c_.insert(c_.end(), std::move(value)); }

  template <class... Args>
  void insert_many_back(Args &&... args) {
    std::initializer_list ilist = {std::forward<Args>(args)...};
    for (auto el : ilist) {
      push(el);
    }
  }

  void pop() { c_.erase(c_.begin()); }

  void swap(queue &other) noexcept { std::swap(c_, other.c_); }

  template <class U, class C>
  friend bool operator==(const queue<U, C> &queue1, const queue<U, C> &queue2);

  template <class U, class C>
  friend bool operator!=(const queue<U, C> &queue1, const queue<U, C> &queue2);

  template <class U, class C>
  friend bool operator<(const queue<U, C> &queue1, const queue<U, C> &queue2);

  template <class U, class C>
  friend bool operator<=(const queue<U, C> &queue1, const queue<U, C> &queue2);

  template <class U, class C>
  friend bool operator>(const queue<U, C> &queue1, const queue<U, C> &queue2);

  template <class U, class C>
  friend bool operator>=(const queue<U, C> &queue1, const queue<U, C> &queue2);

 private:
  container_type c_{};
};

template <class T, class C>
bool operator==(const queue<T, C> &queue1, const queue<T, C> &queue2) {
  return queue1.c_ == queue2.c_;
}

template <class T, class C>
bool operator!=(const queue<T, C> &queue1, const queue<T, C> &queue2) {
  return queue1.c_ != queue2.c_;
}

template <class T, class C>
bool operator<(const queue<T, C> &queue1, const queue<T, C> &queue2) {
  return queue1.c_ < queue2.c_;
}

template <class T, class C>
bool operator<=(const queue<T, C> &queue1, const queue<T, C> &queue2) {
  return queue1.c_ <= queue2.c_;
}

template <class T, class C>
bool operator>(const queue<T, C> &queue1, const queue<T, C> &queue2) {
  return queue1.c_ > queue2.c_;
}

template <class T, class C>
bool operator>=(const queue<T, C> &queue1, const queue<T, C> &queue2) {
  return queue1.c_ >= queue2.c_;
}

template <class T, class C>
void swap(queue<T, C> &lhs, queue<T, C> &rhs) noexcept {
  lhs.swap(rhs);
}

}  // namespace s21

#endif  // S21_CONTAINERS_SRC_S21_QUEUE_H
