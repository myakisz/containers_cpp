#ifndef S21_CONTAINERS_SRC_S21_SET_H
#define S21_CONTAINERS_SRC_S21_SET_H

#include "s21_rbtree.h"

namespace s21 {
template <class K, class Compare = std::less<K>>
class set {
 public:
  using key_type = K;
  using value_type = K;
  using node_type = Node<key_type, value_type>;
  using tree_type = tree<key_type, value_type>;
  using size_type = std::size_t;
  using iterator = TreeIterator<key_type, value_type>;
  using const_iterator = TreeConstIterator<key_type, value_type>;

  set() {}

  set(const set& other) { tree_ = other.tree_; }

  set(set&& other) {
    tree_ = std::move(other.tree_);
    other.clear();
  }

  set(std::initializer_list<value_type> init) { *this = init; }

  ~set() {
    if (tree_.get_root()) {
      tree_.clear();
    }
  }

  set& operator=(const set& other) {
    tree_ = other.tree_;
    return *this;
  }

  set& operator=(set&& other) noexcept {
    tree_ = std::move(other.tree_);
    return *this;
  }

  set& operator=(std::initializer_list<value_type> ilist) {
    for (auto it = ilist.begin(); it != ilist.end(); ++it) {
      insert(*it);
    }
    return *this;
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

  std::pair<iterator, bool> insert(const value_type& value) {
    return tree_.insert(value, value);
  }

  std::pair<iterator, bool> insert(value_type&& value) { return insert(value); }

  void insert(std::initializer_list<value_type> ilist) {
    for (auto it = ilist.begin(); it < ilist.end(); it++) {
      insert(*it);
    }
  }

  template <class... Args>
  std::pair<iterator, bool> insert_many(Args&&... args) {
    size_type starting_size = size();
    std::initializer_list ilist = {std::forward<Args>(args)...};
    auto it = ilist.begin();
    insert(ilist);
    if (size() == starting_size) {
      return std::make_pair(iterator(find(*it)), false);
    }
    return std::make_pair(iterator(find(*it)), true);
  }

  iterator erase(const_iterator pos) { return tree_.erase(pos); }

  iterator erase(const_iterator first, const_iterator last) {
    return tree_.erase(first, last);
  }

  size_type erase(const key_type& key) { return tree_.erase(key); }

  void swap(set& other) noexcept { tree_.swap(other.tree_); }

  node_type extract(const_iterator position) {
    return extract(position.get_key());
  }

  node_type extract(const key_type& k) {
    node_type n = tree_.extract(k);
    return n;
  }

  void merge(set& source) {
    iterator it = source.begin();
    for (size_type i = 0; i < source.size(); i++) {
      insert(it.get_key());
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

  tree_type* get_tree_ptr() noexcept { return &tree_; }

 protected:
  tree_type tree_;
};

template <class K>
bool operator==(const set<K>& lhs, const set<K>& rhs) {
  return lhs.get_tree() == rhs.get_tree();
}

template <class K>
bool operator!=(const set<K>& lhs, const set<K>& rhs) {
  return !(lhs == rhs);
}

template <class K>
bool operator<(const set<K>& lhs, const set<K>& rhs) {
  return lhs.get_tree() < rhs.get_tree();
}

template <class K>
bool operator<=(const set<K>& lhs, const set<K>& rhs) {
  return lhs.get_tree() <= rhs.get_tree();
}

template <class K>
bool operator>(const set<K>& lhs, const set<K>& rhs) {
  return lhs.get_tree() > rhs.get_tree();
}

template <class K>
bool operator>=(const set<K>& lhs, const set<K>& rhs) {
  return lhs.get_tree() >= rhs.get_tree();
}

}  // namespace s21

#endif  // S21_CONTAINERS_SRC_S21_SET_H
