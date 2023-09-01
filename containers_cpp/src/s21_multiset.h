#ifndef S21_CONTAINERS_SRC_S21_MULTISET_H
#define S21_CONTAINERS_SRC_S21_MULTISET_H

#include "s21_set.h"

namespace s21 {
template <class Key, class Compare = std::less<Key>>
class multiset : public s21::set<Key, Compare> {
  using key_type = Key;
  using value_type = Key;
  using base = s21::set<key_type, Compare>;
  using size_type = std::size_t;
  using iterator = TreeIterator<key_type, value_type>;
  using const_iterator = TreeConstIterator<key_type, value_type>;

 public:
  multiset() : base() { this->get_tree_ptr()->set_is_multi(true); }

  multiset(const multiset& other) : base(other) {}

  multiset(multiset&& other) : base(std::move(other)) {}

  multiset(std::initializer_list<key_type> init) {
    this->get_tree_ptr()->set_is_multi(true);
    *this = init;
  }

  multiset& operator=(std::initializer_list<key_type> ilist) {
    for (auto it = ilist.begin(); it != ilist.end(); ++it) {
      this->insert(*it);
    }
    return *this;
  }

  void merge(base& source) { base::merge(source); }

  void merge(multiset& source) {
    iterator it = source.begin();
    for (size_type i = 0; i < source.size(); i++) {
      base::insert(it.get_key());
      it++;
    }
  }
};
}  // namespace s21

#endif  // S21_CONTAINERS_SRC_S21_MULTISET_H
