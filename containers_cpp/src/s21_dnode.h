#ifndef S21_CONTAINERS_SRC_S21_DNODE_H_
#define S21_CONTAINERS_SRC_S21_DNODE_H_

namespace s21 {

template <typename T>
struct dnode {
  dnode<T>* prev;
  T data;
  dnode<T>* next;

  dnode() noexcept : prev(nullptr), data(T()), next(nullptr) {}

  explicit dnode(const T& value) noexcept
      : prev(nullptr), data(value), next(nullptr) {}

  explicit dnode(T&& value) noexcept
      : prev(nullptr), data(std::move(value)), next(nullptr) {}

  void attach_prev(dnode<T>* other) noexcept {
    other->next = this;
    prev = other;
  }

  void attach_next(dnode<T>* other) noexcept {
    other->prev = this;
    next = other;
  }

  dnode<T>* detach_prev() noexcept {
    dnode<T>* prev_ = prev;
    if (prev_) {
      prev_->next = nullptr;
      prev = nullptr;
    }
    return prev_;
  }

  dnode<T>* detach_next() noexcept {
    dnode<T>* next_ = next;
    if (next_) {
      next_->prev = nullptr;
      next = nullptr;
    }
    return next_;
  }

  void swap(dnode& other) {
    std::swap(prev, other.prev);
    std::swap(data, other.data);
    std::swap(next, other.next);
  }

  void reverse() noexcept {
    auto tmp = prev;
    prev = next;
    next = tmp;
  }

  bool operator==(const dnode<T>& rhs) const noexcept {
    return ((prev == rhs.prev) && (data == rhs.data) && (next == rhs.next));
  }

  bool operator!=(const dnode<T>& rhs) const noexcept {
    return !(*this == rhs);
  }
};

}  // namespace s21

#endif  // S21_CONTAINERS_SRC_S21_DNODE_H_
