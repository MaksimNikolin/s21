#ifndef SRC_S21_CONTAINERS_QUEUE_S21_QUEUE_HPP
#define SRC_S21_CONTAINERS_QUEUE_S21_QUEUE_HPP

#include "../list/s21_list.hpp"

namespace s21 {

template <typename T, typename Container = s21::list<T>>
class queue {
 public:
  // Member type
  using value_type = typename Container::value_type;
  using reference = typename Container::reference;
  using const_reference = typename Container::const_reference;
  using size_type = typename Container::size_type;

 protected:
  Container cont;

 public:
  // Member functions
  queue() : cont() {}
  ~queue() {}
  queue(std::initializer_list<value_type> const &items) : cont(items) {}
  queue(const queue &s) : cont(s.cont) {}
  queue(queue &&s) : cont(std::move(s.cont)) {}
  queue &operator=(queue &&s) {
    this->cont = std::move(s.cont);
    return *this;
  }

  // Element access
  const_reference front() { return cont.front(); }
  const_reference back() { return cont.back(); }

  // Capacity
  bool empty() { return cont.empty(); }
  size_type size() { return cont.size(); }

  // Modifiers
  void push(const_reference value) { this->cont.push_back(value); }
  void pop() { this->cont.pop_front(); }
  void swap(queue &other) { this->cont.swap(other.cont); }
};
}  // namespace s21

#endif  // SRC_S21_CONTAINERS_QUEUE_S21_QUEUE_HPP