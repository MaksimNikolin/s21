#ifndef SRC_S21_CONTAINERS_SET_S21_SET_H
#define SRC_S21_CONTAINERS_SET_S21_SET_H

#include <initializer_list>
#include <iostream>

#include "../tree/tree.h"
#include "../vector/s21_vector.h"

namespace s21 {
template <typename Key, typename T = bool>
class Set : public Tree<Key, T> {
 public:
  using key_type = Key;
  using size_type = std::size_t;
  using value_type = Key;  //  value type (the value itself is a key)
  using const_iterator = const Key *;
  using TreeNode = typename s21::Tree<Key, T>::TreeNode;

  Set(){};
  explicit Set(const std::initializer_list<value_type> &items);
  explicit Set(const Set &s);
  Set(Set &&s);
  ~Set();

  Set<Key, T> &operator=(
      Set<Key, T> &&s);  // assignment operator overload for moving object
  Set<Key, T> &operator=(
      const Set &s);  // assignment operator overload for coping object

  // Set Iterators
  typedef typename Set<Key, T>::Iterator iterator;
  iterator Begin();
  iterator End();

  // Set Modifiers
  std::pair<iterator, bool> Insert(const value_type &value);
  void Merge(Set &other);  // splices nodes from another container
  template <class... Args>
  s21::Vector<std::pair<typename Tree<Key, T>::iterator, bool>> Emplace(
      Args &&...args);

  // Set Lookup
  typename Tree<Key, T>::iterator Find(const Key &key);
};
#include "s21_set.tpp"
}  // namespace s21

#endif  // SRC_S21_CONTAINERS_SET_S21_SET_H
