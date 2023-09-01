#ifndef S21_CONTAINERS_SRC_S21_LIST_H_
#define S21_CONTAINERS_SRC_S21_LIST_H_

#include <iostream>
#include <limits>
#include <sstream>
#include <string>

#include "s21_dnode.h"
#include "s21_set.h"

namespace s21 {

using difference_type = std::ptrdiff_t;
using size_type = std::size_t;

template <typename T>
class list;

namespace {

template <typename T>
class ListConstIterator {
  friend list<T>;
  using iterator_category = std::bidirectional_iterator_tag;
  using node = dnode<T>;

 public:
  ListConstIterator() noexcept : ptr(nullptr) {}

  explicit ListConstIterator(const node* other) noexcept : ptr(other) {}

  ListConstIterator(const ListConstIterator& other) noexcept : ptr(other.ptr) {}

  ListConstIterator(ListConstIterator&& other) noexcept {
    ptr = std::move(other.ptr);
    other.ptr = nullptr;
  }

  ListConstIterator& operator=(const node* other) noexcept {
    ptr = other;
    return *this;
  }

  ListConstIterator& operator=(const ListConstIterator& other) noexcept {
    ptr = other.ptr;
    return *this;
  }

  ListConstIterator& operator=(ListConstIterator&& other) noexcept {
    std::swap(ptr, other.ptr);
    return *this;
  }

  ~ListConstIterator() noexcept { ptr = nullptr; }

  const T& operator*() const noexcept { return ptr->data; }

  ListConstIterator& operator++() noexcept {
    ptr = ptr->next;
    return *this;
  }

  ListConstIterator& operator--() noexcept {
    ptr = ptr->prev;
    return *this;
  }

  ListConstIterator operator++(int) noexcept {
    ListConstIterator tmp = *this;
    ptr = ptr->next;
    return tmp;
  }

  ListConstIterator operator--(int) noexcept {
    ListConstIterator tmp = *this;
    ptr = ptr->prev;
    return tmp;
  }

  bool operator==(const ListConstIterator& other) const noexcept {
    return ptr == other.ptr;
  }

  bool operator!=(const ListConstIterator& other) const noexcept {
    return ptr != other.ptr;
  }

 protected:
  const node* ptr;
};

template <typename T>
class ListIterator : public ListConstIterator<T> {
  using base = ListConstIterator<T>;
  using node = dnode<T>;

 public:
  explicit ListIterator(const node* other) noexcept : base(other) {}

  T& operator*() noexcept { return const_cast<T&>(base::operator*()); }

  ListIterator& operator++() noexcept {
    base::operator++();
    return *this;
  }

  ListIterator& operator--() noexcept {
    base::operator--();
    return *this;
  }

  ListIterator operator++(int) noexcept {
    ListIterator tmp = *this;
    base::operator++();
    return tmp;
  }

  ListIterator operator--(int) noexcept {
    ListIterator tmp = *this;
    base::operator--();
    return tmp;
  }

 protected:
  node* ptr;
};

}  // namespace

template <typename T>
class list {
  using iterator = ListIterator<T>;
  using const_iterator = ListConstIterator<T>;
  using node = dnode<T>;

 public:
  list() : head_(nullptr), tail_(nullptr), len_(0) {}

  explicit list(size_type size, T value = T()) : list() {
    check_avail_size_for_nodes(size);
    for (size_type n = 0; n < size; ++n) {
      try {
        push_back(value);
      } catch (...) {
        clear_nodes(n + 1);
        throw;
      }
    }
  }

  list(const std::initializer_list<T>& items) : list() {
    check_avail_size_for_nodes(items.size());
    for (auto it = items.begin(); it != items.end(); ++it) {
      try {
        push_back(*it);
      } catch (...) {
        clear_nodes(size());
        throw;
      }
    }
  }

  list(const list& other) : list() {
    check_avail_size_for_nodes(other.size());
    for (auto it = other.cbegin(); it != other.cend(); ++it) {
      try {
        push_back(*it);
      } catch (...) {
        clear_nodes(size());
        throw;
      }
    }
  }

  list(list&& other) : list() {
    check_avail_size_for_nodes(other.size());
    swap(other);
  }

  list& operator=(const list& other) {
    if (this != &other) {
      list<T> tmp(other);
      swap(tmp);
    }
    return *this;
  }

  list& operator=(list&& other) {
    if (this != &other) {
      swap(other);
    }
    return *this;
  }

  list& operator=(std::initializer_list<T> ilist) {
    list<T> tmp(ilist);
    swap(tmp);
    return *this;
  }

  ~list() noexcept { clear(); }

  void assign(size_type count, const T& value) {
    clear();
    *this = std::move(list(count, value));
  }

  template <class InputIterator>
  void assign(InputIterator first, InputIterator last) {
    clear();
    while (first != last) {
      push_back(*first);
      ++first;
    }
  }

  void assign(std::initializer_list<T> ilist) {
    clear();
    for (auto el : ilist) {
      push_back(el);
    }
  }

  T& front() noexcept { return const_cast<T&>(head_->data); }

  const T& front() const noexcept { return head_->data; }

  T& back() noexcept { return const_cast<T&>(tail_->data); }

  const T& back() const noexcept { return tail_->data; }

  iterator begin() noexcept { return iterator(head_); }

  const_iterator begin() const noexcept { return const_iterator(head_); }

  const_iterator cbegin() const noexcept { return const_iterator(head_); }

  iterator end() noexcept { return iterator(nullptr); }

  const_iterator end() const noexcept { return const_iterator(nullptr); }

  const_iterator cend() const noexcept { return const_iterator(nullptr); }

  bool empty() const noexcept { return !len_; }

  size_type size() const noexcept { return len_; }

  size_type max_size() const noexcept {
    return std::numeric_limits<size_type>::max() / sizeof(node);
  }

  void clear() noexcept {
    clear_nodes(len_);
    nullify();
  }

  iterator insert(const_iterator pos, const T& value) {
    auto curr = const_cast<node*>(pos.ptr);
    if (!curr) {
      push_back(value);
      return end();
    }
    auto new_node = new node(value);
    auto prev = curr->detach_prev();
    if (prev) {
      prev->attach_next(new_node);
    } else {
      head_ = new_node;
    }
    new_node->attach_next(curr);
    len_++;
    return iterator(new_node);
  }

  iterator insert(const_iterator pos, T&& value) {
    T&& m_value = std::move(value);
    return insert(pos, m_value);
  }

  iterator insert(const_iterator pos, size_type count, const T& value) {
    auto it = pos;
    for (size_type c = 0; c < count; ++c) {
      it = insert(it, value);
    }
    return iterator(it.ptr);
  }

  iterator insert(const_iterator pos, std::initializer_list<T> items) {
    auto it = pos;
    for (auto el : items) {
      it = insert(pos, el);
    }
    return iterator(begin());
  }

  template <class... Args>
  iterator insert_many(const_iterator pos, Args&&... args) {
    std::initializer_list ilist = {std::forward<Args>(args)...};
    return insert(pos, ilist);
  }

  template <class... Args>
  void insert_many_back(Args&&... args) {
    std::initializer_list ilist = {std::forward<Args>(args)...};
    insert(end(), ilist);
  }

  template <class... Args>
  void insert_many_front(Args&&... args) {
    std::initializer_list ilist = {std::forward<Args>(args)...};
    insert(begin(), ilist);
  }

  iterator erase(const_iterator pos) {
    auto curr = const_cast<node*>(pos.ptr);
    if (curr == head_) {
      pop_front();
      return begin();
    }
    if (curr == tail_) {
      pop_back();
      return end();
    }
    auto prev = curr->prev;
    auto next = curr->next;
    prev->attach_next(next);
    delete curr;
    len_--;
    return iterator(next);
  }

  iterator erase(const_iterator first, const_iterator last) {
    const_iterator it = first;
    while (first != last) {
      ++first;
      it = erase(it);
    }
    return iterator(it.ptr);
  }

  void push_back(const T& value) {
    auto last = new node(value);
    if (tail_) {
      tail_->attach_next(last);
      tail_ = last;
    } else {
      head_ = tail_ = last;
    }
    len_++;
  }

  void push_back(T&& value) {
    T&& m_value = std::move(value);
    push_back(m_value);
  }

  void pop_back() {
    if (tail_) {
      auto prev_tail = tail_->detach_prev();
      delete tail_;
      tail_ = prev_tail;
      len_--;
      if (!len_) {
        nullify();
      }
    }
  }

  void push_front(const T& value) {
    auto first = new node(value);
    if (head_) {
      head_->attach_prev(first);
      head_ = first;
    } else {
      head_ = tail_ = first;
    }
    len_++;
  }

  void push_front(T&& value) {
    T&& m_value = std::move(value);
    push_front(m_value);
  }

  void pop_front() {
    if (head_) {
      auto head_next = head_->detach_next();
      delete head_;
      head_ = head_next;
      len_--;
      if (!len_) {
        nullify();
      }
    }
  }

  void resize(size_type count) {
    size_type siz = size();
    if (count != siz) {
      if (count > siz) {
        list lst = list(count - siz);
        for (auto node : lst) {
          push_back(node.data);
        }
      } else {
        for (size_type nc = siz; nc > count; --nc) {
          pop_back();
        }
      }
    }
  }

  void swap(list& other) noexcept {
    std::swap(head_, other.head_);
    std::swap(tail_, other.tail_);
    std::swap(len_, other.len_);
  }

  void merge(list& other) {
    auto it = begin();
    auto it_other = other.begin();

    while (it != end() || it_other != other.end()) {
      if (it == end() || (it_other != other.end() && *it > *it_other)) {
        insert(it, *it_other);
        it_other++;
      } else if (it_other == other.end() || (it != end() && *it <= *it_other)) {
        it++;
      }
    }
  }

  void splice(const_iterator pos, list& other) {
    if (empty()) {
      *this = other;
      return;
    }
    while (!other.empty()) {
      pos = insert(++pos, other.front());
      other.pop_front();
    }
  }

  void unique() {
    s21::set<T> set_with_data;
    auto it = begin();

    while (it != end()) {
      if (set_with_data.contains(*it)) {
        it = erase(it);
      } else {
        set_with_data.insert(*it);
        it++;
      }
    }
  }

  void reverse() {
    auto curr = head_;
    while (curr != nullptr) {
      curr->reverse();
      curr = curr->prev;
    }

    auto tmp = head_;
    head_ = tail_;
    tail_ = tmp;
  }

  void sort() {
    if (head_ == nullptr || head_->next == nullptr) return;

    s21::list<T> other;
    auto it = begin();
    size_t len = len_;

    for (size_t i = 0; i < len; i++) {
      if (i % 2 == 0) {
        it++;
      } else {
        other.push_back(*it);
        it = erase(it);
      }
    }
    sort();
    other.sort();
    this->merge(other);
  }

  template <class U>
  friend std::ostream& operator<<(std::ostream& os, list<U> const& lst);

  template <class U>
  friend bool operator==(const list<U>& lhs, const list<U>& rhs);

  template <class U>
  friend bool operator!=(const list<U>& lhs, const list<U>& rhs);

  template <class U>
  friend bool operator<(const list<U>& lhs, const list<U>& rhs);

  template <class U>
  friend bool operator<=(const list<U>& lhs, const list<U>& rhs);

  template <class U>
  friend bool operator>(const list<U>& lhs, const list<U>& rhs);

  template <class U>
  friend bool operator>=(const list<U>& lhs, const list<U>& rhs);

 private:
  void nullify() noexcept {
    head_ = nullptr;
    tail_ = nullptr;
    len_ = 0;
  }

  void clear_nodes(size_type nodes) noexcept {
    if (nodes) {
      for (size_type n = 0; n < nodes; ++n) {
        pop_front();
      }
    }
  }

  void check_avail_size_for_nodes(size_type nodes) const {
    size_type reclaimed = (size() + nodes) * sizeof(node);
    if (reclaimed >= max_size()) {
      std::string errmsg = "reclaimed size (";
      errmsg += std::to_string(reclaimed);
      errmsg += ") exceeds the max_size (";
      errmsg += std::to_string(max_size()) + ")";
      throw std::out_of_range(errmsg);
    }
  }

  node* head_;
  node* tail_;
  size_type len_;
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const list<T>& lst) {
  os << "[";
  auto an = lst.cbegin();
  for (auto n = lst.cbegin(), e = lst.cend(); n != e; ++n) {
    os << *n;
    ++an;
    if (an != e) {
      os << ", ";
    }
  }
  os << "]";
  return os;
}

template <typename T>
std::string to_string(list<T> const& lst) {
  std::ostringstream os;
  os << lst;
  return os.str();
}

template <typename T>
bool operator==(const list<T>& lhs, const list<T>& rhs) {
  if (lhs.size() != rhs.size()) return false;
  auto lit = lhs.cbegin();
  for (auto rit = rhs.cbegin(); rit != rhs.cend(); ++rit) {
    if (*lit != *rit) return false;
    ++lit;
  }
  return true;
}

template <typename T>
bool operator!=(const list<T>& lhs, const list<T>& rhs) {
  return !(lhs == rhs);
}

template <class T>
bool operator<(const list<T>& lhs, const list<T>& rhs) {
  size_type min_size = std::min(lhs.size(), rhs.size());
  auto lit = lhs.cbegin();
  auto rit = rhs.cbegin();
  for (size_type idx = 0; idx < min_size; ++idx) {
    if (*lit < *rit) {
      return true;
    } else if (*lit > *rit) {
      return false;
    }
    lit++;
    rit++;
  }
  return lhs.size() < rhs.size();
}

template <class T>
bool operator<=(const list<T>& lhs, const list<T>& rhs) {
  return !(lhs > rhs);
}

template <class T>
bool operator>(const list<T>& lhs, const list<T>& rhs) {
  size_type min_size = std::min(lhs.size(), rhs.size());
  auto lit = lhs.cbegin();
  auto rit = rhs.cbegin();
  for (size_type idx = 0; idx < min_size; ++idx) {
    if (*lit > *rit) {
      return true;
    } else if (*lit < *rit) {
      return false;
    }
    lit++;
    rit++;
  }
  return lhs.size() > rhs.size();
}

template <class T>
bool operator>=(const list<T>& lhs, const list<T>& rhs) {
  return !(lhs < rhs);
}

};  // namespace s21

#endif  // S21_CONTAINERS_SRC_S21_LIST_H_
