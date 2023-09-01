#ifndef S21_CONTAINERS_SRC_S21_RBTREE_H_
#define S21_CONTAINERS_SRC_S21_RBTREE_H_

namespace s21 {
enum Color { BLACK, RED };

template <class K, class T>
struct Node {
  using key_type = K;
  using value_type = T;

  Node() : color(RED), parent(nullptr), left(nullptr), right(nullptr) {}

  Node(const Node &another)
      : key(another.key),
        value(another.value),
        color(another.color),
        parent(another.parent),
        left(another.left),
        right(another.right) {}

  Node(key_type k, value_type v) {
    key = k;
    value = v;
  }

  ~Node() {}

  Node &operator=(const Node &other) {
    key = other.key;
    value = other.value;
    color = other.color;
    parent = other.parent;
    left = other.left;
    right = other.right;
    return *this;
  }

  bool operator==(const Node &other) const {
    return key == other.key && value == other.value && color == other.color &&
           parent == other.parent && left == other.left && right == other.right;
  }

  key_type key;
  value_type value;
  Color color;
  Node *parent;
  Node *left;
  Node *right;
};

namespace {
template <class K, class T>
class TreeConstIterator {
 public:
  using key_type = K;
  using value_type = T;
  using node_type = Node<key_type, value_type>;
  using reference = value_type &;
  using pointer = value_type *;

  TreeConstIterator() {
    ptr_ = nullptr;
    root_ = nullptr;
  }

  TreeConstIterator(const TreeConstIterator &other) {
    ptr_ = other.ptr_;
    root_ = other.root_;
  }

  TreeConstIterator(const TreeConstIterator &&other) {
    ptr_ = std::move(other.ptr_);
    root_ = std::move(other.root_);
  }

  TreeConstIterator(node_type *ptr) {
    ptr_ = ptr;
    root_ = ptr;
  }

  ~TreeConstIterator() {
    ptr_ = nullptr;
    root_ = nullptr;
  }

  TreeConstIterator &operator=(const TreeConstIterator &other) {
    ptr_ = other.ptr_;
    root_ = other.root_;
    return *this;
  }

  bool operator==(const TreeConstIterator &other) { return ptr_ == other.ptr_; }

  bool operator!=(const TreeConstIterator &other) { return ptr_ != other.ptr_; }

  reference operator*() { return ptr_->value; }

  TreeConstIterator &operator++() {
    TreeConstIterator last = end();
    last--;
    if (ptr_ && ptr_ != last.ptr_) {
      if (ptr_->right) {
        if (ptr_->right->left) {
          ptr_ = ptr_->right;
          while (ptr_->left) {
            ptr_ = ptr_->left;
          }
        } else {
          ptr_ = ptr_->right;
        }
      } else if (ptr_->parent) {
        while (ptr_ == ptr_->parent->right && ptr_->parent->parent) {
          ptr_ = ptr_->parent;
        }
        ptr_ = ptr_->parent;
      }
    } else {
      ptr_ = nullptr;
    }
    return *this;
  }

  TreeConstIterator &operator--() {
    if (ptr_ && ptr_ != begin().ptr_) {
      if (ptr_->left) {
        if (ptr_->left->right) {
          ptr_ = ptr_->left;
          while (ptr_->right) {
            ptr_ = ptr_->right;
          }
        } else {
          ptr_ = ptr_->left;
        }
      } else if (ptr_->parent) {
        while (ptr_ == ptr_->parent->left && ptr_->parent->parent) {
          ptr_ = ptr_->parent;
        }
        ptr_ = ptr_->parent;
      }
    } else if (!ptr_) {
      ptr_ = get_last();
    }
    return *this;
  }

  TreeConstIterator operator++(int) {
    TreeConstIterator it = *this;
    TreeConstIterator last = end();
    last--;
    if (ptr_ && ptr_ != last.ptr_) {
      if (ptr_->right) {
        if (ptr_->right->left) {
          ptr_ = ptr_->right;
          while (ptr_->left) {
            ptr_ = ptr_->left;
          }
        } else {
          ptr_ = ptr_->right;
        }
      } else if (ptr_->parent) {
        while (ptr_ == ptr_->parent->right && ptr_->parent->parent) {
          ptr_ = ptr_->parent;
        }
        ptr_ = ptr_->parent;
      }
    } else {
      ptr_ = nullptr;
    }
    return it;
  }

  TreeConstIterator operator--(int) {
    TreeConstIterator it = *this;
    if (ptr_ && ptr_ != begin().ptr_) {
      if (ptr_->left) {
        if (ptr_->left->right) {
          ptr_ = ptr_->left;
          while (ptr_->right) {
            ptr_ = ptr_->right;
          }
        } else {
          ptr_ = ptr_->left;
        }
      } else if (ptr_->parent) {
        while (ptr_ == ptr_->parent->left && ptr_->parent->parent) {
          ptr_ = ptr_->parent;
        }
        ptr_ = ptr_->parent;
      }
    } else if (!ptr_) {
      ptr_ = get_last();
    }
    return it;
  }

  TreeConstIterator begin() {
    TreeConstIterator it(*this);
    it.ptr_ = it.root_;
    while (it.ptr_->left) {
      it.ptr_ = it.ptr_->left;
    }
    return it;
  }

  TreeConstIterator end() {
    TreeConstIterator it(*this);
    it.ptr_ = nullptr;
    return it;
  }

  key_type get_key() { return ptr_->key; }

  node_type *get_pointer() { return ptr_; }

  node_type *get_last() {
    ptr_ = root_;
    while (ptr_->right) {
      ptr_ = ptr_->right;
    }
    return ptr_;
  }

 protected:
  node_type *ptr_;
  node_type *root_;
};

template <class K, class T>
class TreeIterator : public TreeConstIterator<K, T> {
  using key_type = K;
  using value_type = T;
  using base = TreeConstIterator<key_type, value_type>;
  using node_type = Node<key_type, value_type>;

 public:
  TreeIterator(const base &other) : base(other) {}
};
}  // namespace

template <class K, class T>
class tree {
 public:
  using key_type = K;
  using value_type = T;
  using size_type = std::size_t;
  using node_type = Node<key_type, value_type>;
  using tree_type = tree<key_type, value_type>;
  using iterator = TreeIterator<key_type, value_type>;
  using const_iterator = TreeConstIterator<key_type, value_type>;

  tree() : root_(nullptr), size_(0), is_multi_(false) {}

  tree(bool is_multi) : root_(nullptr), size_(0), is_multi_(is_multi) {}

  tree(const tree &other) {
    root_ = copy_node(other.root_);
    size_ = other.size_;
    is_multi_ = other.is_multi_;
  }

  tree(tree &&other) {
    root_ = copy_node(other.root_);
    size_ = other.size_;
    is_multi_ = other.is_multi_;
    other.clear();
  }

  ~tree() noexcept {
    if (root_ != nullptr) clear_node(root_);
  }

  tree &operator=(const tree &other) {
    root_ = copy_node(other.root_);
    size_ = other.size_;
    is_multi_ = other.is_multi_;
    return *this;
  }

  tree &operator=(tree &&other) {
    root_ = copy_node(other.root_);
    size_ = other.size_;
    is_multi_ = other.is_multi_;
    return *this;
  }

  iterator begin() noexcept {
    iterator it(get_root());
    return it.begin();
  }

  const_iterator begin() const noexcept { return cbegin(); }

  const_iterator cbegin() const noexcept {
    const_iterator it(get_root());
    return it.begin();
  }

  iterator end() noexcept {
    iterator it(get_root());
    return it.end();
  }

  const_iterator end() const noexcept { return cend(); }

  const_iterator cend() const noexcept {
    const_iterator it(get_root());
    return it.end();
  }

  bool empty() const noexcept { return !size_; }

  size_type size() const noexcept { return size_; }

  size_type max_size() const noexcept {
    return std::numeric_limits<size_type>::max() /
           sizeof(tree<key_type, value_type>);
  }

  void clear() noexcept {
    clear_node(root_);
    root_ = nullptr;
    size_ = 0;
  }

  std::pair<iterator, bool> insert(const key_type &key,
                                   const value_type &value) {
    node_type *node = new node_type;
    node->key = key;
    node->value = value;
    if (root_ == nullptr) {
      root_ = node;
      node->color = BLACK;
      this->size_++;
      return std::make_pair(find(key), true);
    }
    node_type *curr = nullptr;
    auto *tmp = this->root_;
    while (tmp != nullptr) {
      curr = tmp;
      if (compare_keys(key, curr->key) == -1) {
        tmp = tmp->left;
      } else if (compare_keys(key, curr->key) == 1) {
        tmp = tmp->right;
      } else {
        if (is_multi_) {
          tmp = tmp->right;
          if (tmp) continue;
        } else {
          delete node;
          return std::make_pair(find(key), false);
        }
      }
    }
    node->parent = curr;
    if (compare_keys(key, curr->key) == -1)
      curr->left = node;
    else
      curr->right = node;
    update_tree_after_insert(curr, node);
    this->size_++;
    return std::make_pair(find(key), true);
  }

  iterator erase(const_iterator pos) {
    key_type key = pos.get_key();
    size_type c = count_same_key_before_pos(pos);
    if (*pos) {
      extract(key);
    }
    iterator it = lower_bound(key);
    for (size_type i = 0; i < c; i++) {
      it++;
    }
    return it;
  }

  iterator erase(const_iterator first, const_iterator last) {
    if (first == cbegin() && last == cend()) {
      clear();
      return end();
    } else {
      value_type val;
      size_type c;
      const_iterator const_it = last;
      if (last != cend()) {
        val = *last;
        c = count_same_key_before_pos(last);
      }
      while (*first != val) {
        first = erase(first);
        if (first == end()) {
          return end();
        }
      }
      if (*first == val) {
        for (size_type i = 0; i < c; i++) {
          first = erase(first);
        }
      }
      iterator it = first;
      return it;
    }
  }

  size_type erase(const key_type &key) {
    size_type c = count(key);
    for (size_type i = 0; i < c; i++) {
      extract(key);
    }
    return c;
  }

  void swap(tree &other) {
    std::swap(root_, other.root_);
    std::swap(size_, other.size_);
    std::swap(is_multi_, other.is_multi_);
  }

  node_type extract(const key_type &key) {
    node_type *node = find(key).get_pointer();
    node_type del_node;
    if (node != nullptr) {
      del_node.parent = node->parent;
      del_node.left = node->left;
      del_node.right = node->right;
      del_node.key = node->key;
      del_node.value = node->value;
      delete_node(node);
      this->size_--;
    }
    return del_node;
  }

  size_type count(const key_type &key) const {
    if (is_multi_) return count_multi(key);
    auto search = find(key);
    return search.get_pointer() ? 1 : 0;
  }

  size_type count_multi(const key_type &key) const {
    const_iterator it = cbegin();
    size_t res = 0;
    for (int i = 0; i < size_; i++) {
      if (*it == key) res++;
      if (i != size_ - 1) it++;
    }
    return res;
  }

  iterator find(const key_type &key) const {
    auto *curr = root_;
    node_type *search = nullptr;
    while (curr != nullptr) {
      if (compare_keys(key, curr->key) == -1) {
        curr = curr->left;
      } else if (compare_keys(key, curr->key) == 1) {
        curr = curr->right;
      } else {
        search = curr;
        break;
      }
    }
    return iterator(search);
  }

  bool contains(const key_type &key) const { return find(key) != nullptr; }

  std::pair<iterator, iterator> equal_range(const key_type &key) {
    return std::make_pair(lower_bound(key), upper_bound(key));
  }

  iterator lower_bound(const key_type &key) {
    iterator it = begin();
    for (size_type i = 0; i < size(); i++) {
      if (it.get_key() >= key) {
        return it;
      }
      it++;
    }
    return end();
  }

  const_iterator lower_bound(const key_type &key) const {
    const_iterator it = cbegin();
    for (size_type i = 0; i < size(); i++) {
      if (it.get_key() >= key) {
        return it;
      }
      it++;
    }
    return end();
  }

  iterator upper_bound(const key_type &key) {
    iterator it = begin();
    for (size_type i = 0; i < size(); i++) {
      if (it.get_key() > key) {
        return it;
      }
      it++;
    }
    return end();
  }

  const_iterator upper_bound(const key_type &key) const {
    const_iterator it = cbegin();
    for (size_type i = 0; i < size(); i++) {
      if (it.get_key() > key) {
        return it;
      }
      it++;
    }
    return end();
  }

  node_type *get_root() const noexcept { return root_; }

  bool get_is_multi() { return is_multi_; }

  void set_is_multi(bool is_multi) { this->is_multi_ = is_multi; }

 private:
  node_type *root_;
  int size_;
  bool is_multi_;

  node_type *copy_node(node_type *other, node_type *parent = NULL) {
    if (other == NULL) {
      return NULL;
    }
    node_type *new_node = new node_type;
    new_node->key = other->key;
    new_node->value = other->value;
    new_node->parent = parent;
    new_node->color = other->color;
    new_node->left = copy_node(other->left, new_node);
    new_node->right = copy_node(other->right, new_node);
    return new_node;
  }

  int compare_keys(const K &first, const K &second) const {
    int res = 0;
    if (first < second) res = -1;
    if (first > second) res = 1;
    return res;
  }

  size_type count_same_key_before_pos(const_iterator it) {
    if (!is_multi_) {
      return 0;
    }
    value_type val = *it;
    size_type count = -1;
    if (it == cbegin()) {
      return 0;
    }
    while (*it == val) {
      count++;
      it--;
      if (it == cbegin()) {
        count++;
        break;
      }
    }
    return count;
  }

  void clear_node(node_type *node) noexcept {
    if (node->left != nullptr) clear_node(node->left);
    if (node->right != nullptr) clear_node(node->right);
    delete node;
  }

  void delete_node(Node<K, T> *node) {
    if (node->left == nullptr && node->right == nullptr) {
      if (node->color == BLACK) rebalance_after_extract(node);
      if (node->parent->left == node)
        node->parent->left = nullptr;
      else
        node->parent->right = nullptr;
      delete node;
    } else {
      node_type *node_to_swap = nullptr;
      if (node->left != nullptr && node->right != nullptr)
        node_to_swap = get_node_to_swap(node);
      else
        node_to_swap = (node->left == nullptr) ? node->right : node->left;
      node->key = node_to_swap->key;
      node->value = node_to_swap->value;
      delete_node(node_to_swap);
    }
  }

  node_type *get_node_to_swap(const node_type *node) {
    node_type *max_left = node->left;
    node_type *min_right = node->right;
    int left_count = 0, right_count = 0;
    auto *curr = max_left;
    while (curr->right != nullptr) {
      max_left = curr->right;
      left_count++;
      curr = curr->right;
    }
    curr = min_right;
    while (curr->left != nullptr) {
      min_right = curr->left;
      right_count++;
      curr = curr->left;
    }
    return (left_count >= right_count) ? max_left : min_right;
  }

  void left_rotate(Node<key_type, value_type> *node) {
    auto temp = node->right;
    node->right = temp->left;
    if (temp->left != nullptr) temp->left->parent = node;
    temp->left = node;
    temp->parent = node->parent;
    node->parent = temp;
    if (root_ == node) {
      root_ = temp;
      return;
    }
    if (temp->parent->left == node)
      temp->parent->left = temp;
    else
      temp->parent->right = temp;
  }

  void right_rotate(node_type *node) {
    auto temp = node->left;
    node->left = temp->right;
    if (temp->right != nullptr) temp->right->parent = node;
    temp->right = node;
    temp->parent = node->parent;
    node->parent = temp;
    if (root_ == node) {
      root_ = temp;
      return;
    }
    if (temp->parent->left == node)
      temp->parent->left = temp;
    else
      temp->parent->right = temp;
  }

  void rebalance_after_extract(node_type *node) {
    if (node == root_) return;
    auto *parent = node->parent;
    bool is_left = (node == parent->left);
    auto *sibling = is_left ? parent->right : parent->left;

    if (sibling->color == BLACK) {
      if ((sibling->left != nullptr && sibling->left->color == RED) ||
          (sibling->right != nullptr && sibling->right->color == RED)) {
        rebalance_when_one_child_is_red(node, parent, is_left);
      } else {
        int parent_color = parent->color;
        sibling->color = RED;
        parent->color = BLACK;
        if (parent_color == BLACK) rebalance_after_extract(parent);
      }
    } else {
      parent->color = RED;
      sibling->color = BLACK;
      is_left ? left_rotate(parent) : right_rotate(parent);
      rebalance_after_extract(node);
    }
  }

  void rebalance_when_one_child_is_red(node_type *node, node_type *parent,
                                       bool is_left) {
    auto *sibling = is_left ? parent->right : parent->left;
    if ((is_left && sibling->right != nullptr &&
         sibling->right->color == RED) ||
        (!is_left && sibling->left != nullptr && sibling->left->color == RED)) {
      sibling->color = parent->color;
      parent->color = BLACK;
      is_left ? sibling->right->color = BLACK : sibling->left->color = BLACK;
      is_left ? left_rotate(parent) : right_rotate(parent);
    } else {
      is_left ? sibling->left->color = BLACK : sibling->right->color = BLACK;
      sibling->color = RED;
      is_left ? right_rotate(sibling) : left_rotate(sibling);
      rebalance_when_one_child_is_red(node, parent, is_left);
    }
  }

  void update_tree_after_insert(node_type *curr, node_type *node) {
    while (curr->color == RED && curr->parent != nullptr) {
      bool is_right = (curr == curr->parent->right);
      auto *uncle = (is_right) ? curr->parent->left : curr->parent->right;

      if (uncle != nullptr && uncle->color == RED) {
        curr->color = BLACK;
        uncle->color = BLACK;
        if (curr->parent != root_) curr->parent->color = RED;
        curr = curr->parent;
        if (curr->parent == nullptr || curr->parent->color == BLACK) break;
      } else {
        if ((is_right && node == curr->left) ||
            (!is_right && node == curr->right)) {
          is_right ? right_rotate(curr) : left_rotate(curr);
          curr = node;
        }
        curr->color = BLACK;
        curr->parent->color = RED;
        is_right ? left_rotate(curr->parent) : right_rotate(curr->parent);
      }
    }
  }
};  // namespace s21

template <class K, class T>
bool operator==(const tree<K, T> &lhs, const tree<K, T> &rhs) {
  if (lhs.size() != rhs.size()) {
    return false;
  }
  s21::TreeConstIterator lit = lhs.begin();
  s21::TreeConstIterator rit = rhs.begin();
  for (std::size_t i = 0; i < lhs.size(); i++) {
    if (lit.get_key() != rit.get_key() || *lit != *rit) {
      return false;
    }
    if (i < rhs.size() - 1) {
      lit++;
      rit++;
    }
  }
  return true;
}

template <class K, class T>
bool operator!=(const tree<K, T> &lhs, const tree<K, T> &rhs) {
  return !(lhs == rhs);
}

template <class K, class T>
bool operator<(const tree<K, T> &lhs, const tree<K, T> &rhs) {
  if (lhs.size() < rhs.size()) {
    return true;
  } else if (lhs.size() > rhs.size()) {
    return false;
  } else {
    s21::TreeConstIterator lit = lhs.begin();
    s21::TreeConstIterator rit = rhs.begin();
    for (std::size_t i = 0; i < lhs.size(); i++) {
      if (lit.get_key() > rit.get_key()) {
        return false;
      } else if (lit.get_key() < rit.get_key()) {
        return true;
      }
      if (i < rhs.size() - 1) {
        lit++;
        rit++;
      }
    }
    return false;
  }
}

template <class K, class T>
bool operator<=(const tree<K, T> &lhs, const tree<K, T> &rhs) {
  return lhs == rhs || lhs < rhs;
}

template <class K, class T>
bool operator>(const tree<K, T> &lhs, const tree<K, T> &rhs) {
  return !(lhs <= rhs);
}

template <class K, class T>
bool operator>=(const tree<K, T> &lhs, const tree<K, T> &rhs) {
  return lhs == rhs || lhs > rhs;
}

}  // namespace s21

#endif  // S21_CONTAINERS_SRC_S21_RBTREE_H_
