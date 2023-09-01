#ifndef S21_CONTAINERS_SRC_S21_MAP_H
#define S21_CONTAINERS_SRC_S21_MAP_H

#include "s21_rbtree.h"

namespace s21 {
template <class K, class T, class Compare = std::less<K>>
class map {
 public:
  using key_type = K;
  using value_type = T;
  using pair_type = std::pair<const key_type, T>;
  using size_type = std::size_t;
  using iterator = TreeIterator<key_type, value_type>;
  using const_iterator = TreeConstIterator<key_type, value_type>;
  using node_type = Node<key_type, value_type>;
  using tree_type = tree<key_type, value_type>;
  using reference = T&;

  map() {}

  map(const map& other) { tree_ = other.tree_; }

  map(map&& other) {
    tree_ = std::move(other.tree_);
    other.clear();
  }

  map(std::initializer_list<pair_type> const& items) { *this = items; }

  ~map() {}

  map& operator=(const map& other) {
    tree_ = other.tree_;
    return *this;
  }

  map& operator=(map&& other) noexcept {
    tree_ = std::move(other.tree_);
    return *this;
  }

  map& operator=(std::initializer_list<pair_type> ilist) {
    for (auto it = ilist.begin(); it != ilist.end(); ++it) {
      insert(*it);
    }
    return *this;
  }

  reference at(const key_type& key) {
    if (!contains(key)) {
      throw std::out_of_range("Key doesn't exist");
    }
    return *find(key);
  }

  const reference at(const key_type& key) const {
    if (!contains(key)) {
      throw std::out_of_range("Key doesn't exist");
    }
    return *find(key);
  }

  reference operator[](const key_type& key) {
    if (!contains(key)) {
      insert(key, value_type());
    }
    return *find(key);
  }

  reference operator[](key_type& key) {
    if (!contains(key)) {
      insert(key, value_type());
    }
    return *find(key);
  }

  iterator begin() noexcept { return tree_.begin(); }

  const_iterator begin() const noexcept { return cbegin(); }

  const_iterator cbegin() const noexcept { return tree_.cbegin(); }

  iterator end() noexcept { return tree_.end(); }

  const_iterator end() const noexcept { return cend(); }

  const_iterator cend() const noexcept { return tree_.cend(); }

  bool empty() const noexcept { return tree_.empty(); }

  size_type size() const noexcept { return tree_.size(); }

  size_type max_size() const noexcept { return tree_.max_size(); }

  void clear() noexcept { tree_.clear(); }

  std::pair<iterator, bool> insert(const pair_type& value) {
    return insert(std::get<0>(value), std::get<1>(value));
  }

  std::pair<iterator, bool> insert(pair_type&& value) { return insert(value); }

  std::pair<iterator, bool> insert(const key_type& key, const value_type& obj) {
    return tree_.insert(key, obj);
  }

  void insert(std::initializer_list<pair_type> ilist) {
    for (auto it = ilist.begin(); it < ilist.end(); it++) {
      insert(*it);
    }
  }

  std::pair<iterator, bool> insert_or_assign(const key_type& k, const T& obj) {
    if (contains(k)) {
      iterator it = find(k);
      *it = obj;
      return std::make_pair(find(k), false);
    }
    return insert(k, obj);
  }

  std::pair<iterator, bool> insert_or_assign(key_type& k, T&& obj) {
    return insert_or_assign(k, obj);
  }

  std::pair<iterator, bool> insert_or_assign(key_type&& k, T&& obj) {
    return insert_or_assign(k, obj);
  }

  template <class... Args>
  std::pair<iterator, bool> insert_many(Args&&... args) {
    size_type starting_size = size();
    std::initializer_list ilist = {std::forward<Args>(args)...};
    auto it = ilist.begin();
    for (it = ilist.begin(); it < ilist.end(); it++) {
      insert(*it);
    }
    if (size() == starting_size) {
      return std::make_pair(iterator(find(std::get<0>(*ilist.begin()))), false);
    }
    return std::make_pair(iterator(find(std::get<0>(*ilist.begin()))), true);
  }

  iterator erase(const_iterator pos) { return tree_.erase(pos); }

  iterator erase(const_iterator first, const_iterator last) {
    return tree_.erase(first, last);
  }

  size_type erase(const key_type& key) { return tree_.erase(key); }

  void swap(map& other) noexcept { tree_.swap(other.tree_); }

  node_type extract(const_iterator position) {
    return extract(position.get_key());
  }

  node_type extract(const key_type& k) {
    node_type n = tree_.extract(k);
    return n;
  }

  void merge(map& source) {
    iterator it = source.begin();
    for (size_type i = 0; i < source.size(); i++) {
      insert(it.get_key(), *it);
      it++;
    }
  }

  size_type count(const key_type& key) const { return tree_.count(key); }

  iterator find(const key_type& key) { return iterator(tree_.find(key)); }

  const_iterator find(const key_type& key) const { return tree_.find(key); }

  bool contains(const key_type& key) const { return tree_.contains(key); }

  std::pair<iterator, iterator> equal_range(const key_type& key) {
    return tree_.equal_range(key);
  }

  iterator lower_bound(const key_type& key) { return tree_.lower_bound(key); }

  const_iterator lower_bound(const key_type& key) const {
    return tree_.lower_bound(key);
  }

  iterator upper_bound(const key_type& key) { return tree_.upper_bound(key); }

  const_iterator upper_bound(const key_type& key) const {
    return tree_.upper_bound(key);
  }

  tree_type get_tree() const noexcept { return tree_; }

 protected:
  tree_type tree_;
};

template <class K, class T>
bool operator==(const map<K, T>& lhs, const map<K, T>& rhs) {
  return lhs.get_tree() == rhs.get_tree();
}

template <class K, class T>
bool operator!=(const map<K, T>& lhs, const map<K, T>& rhs) {
  return !(lhs == rhs);
}

template <class K, class T>
bool operator<(const map<K, T>& lhs, const map<K, T>& rhs) {
  return lhs.get_tree() < rhs.get_tree();
}

template <class K, class T>
bool operator<=(const map<K, T>& lhs, const map<K, T>& rhs) {
  return lhs.get_tree() <= rhs.get_tree();
}

template <class K, class T>
bool operator>(const map<K, T>& lhs, const map<K, T>& rhs) {
  return lhs.get_tree() > rhs.get_tree();
}

template <class K, class T>
bool operator>=(const map<K, T>& lhs, const map<K, T>& rhs) {
  return lhs.get_tree() >= rhs.get_tree();
}

}  // namespace s21

#endif  // S21_CONTAINERS_SRC_S21_MAP_H
