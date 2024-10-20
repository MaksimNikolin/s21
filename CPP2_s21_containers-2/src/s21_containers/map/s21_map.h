#ifndef SRC_s21_CONTAINERS_MAP_S21_MAP_H
#define SRC_s21_CONTAINERS_MAP_S21_MAP_H

#include <climits>
#include <initializer_list>
#include <iostream>

#include "../tree/tree.h"
#include "../vector/s21_vector.h"

namespace s21 {

template <typename Key, typename T>
class Map : public Tree<Key, T> {
 public:
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = size_t;
  using TreeNode = typename Tree<Key, T>::TreeNode;

  Map(){};
  explicit Map(std::initializer_list<value_type> const &items);
  explicit Map(const Map &m);
  Map(Map &&m);
  ~Map();

  // Map Element access
  Map<Key, T> &operator=(Map<Key, T> &&m);
  Map<Key, T> &operator=(const Map<Key, T> &m);
  T &At(const Key &key);
  T &operator[](const Key &key);

  struct Iterator {
    friend class Map;
    Iterator(){};
    explicit Iterator(TreeNode &other) : current_node_(&other){};

    Iterator &operator++() {
      if (current_node_ != nullptr &&
          current_node_ != Tree<Key, T>::GetNIL(current_node_)) {
        current_node_ = Tree<Key, T>::Successor(current_node_);
      }
      return *this;
    };

    Iterator &operator--() {
      if (current_node_ == nullptr)
        throw std::out_of_range("This iterator is nullptr");

      if (current_node_ != Tree<Key, T>::GetNIL(current_node_)) {
        current_node_ = Tree<Key, T>::Predecessor(current_node_);
      } else {
        current_node_ = Tree<Key, T>::RightmostChild(current_node_->parent_);
      }
      return *this;
    };

    // post fixing is bad in general but it has it's usages
    Iterator operator++(int) {
      Iterator tempIter = *this;  // we make a copy of the iterator
      ++*this;                    // we increment
      return tempIter;            // we return the copy before increment
    };

    // we need to be able to compare nodes
    bool operator!=(const Iterator &other) const {
      return this->current_node_ != other.current_node_;
    };

    bool operator==(const Iterator &other) const {
      return this->current_node_ == other.current_node_;
    };

    Iterator operator--(int) {
      Iterator tempIter = *this;  // we make a copy of the iterator
      --*this;                    // we increment
      return tempIter;            // we return the copy before increment
    };

    // return the data from the node (dereference operator)
    Map<Key, T>::value_type operator*() const {
      if (current_node_ != nullptr && current_node_->left_ != current_node_ &&
          current_node_ != Tree<Key, T>::GetNIL(current_node_)) {
        return std::pair(current_node_->key_, current_node_->value);
      } else {
        throw std::out_of_range("This iterator is nullptr");
      }
    };
    TreeNode *GetNode() { return current_node_; }

    Key First() {
      if (current_node_ != nullptr &&
          current_node_ != Tree<Key, T>::GetNIL(current_node_)) {
        return current_node_->key_;
      } else {
        throw std::out_of_range("This iterator is nullptr");
      }
    };

    T Second() {
      if (current_node_ != nullptr &&
          current_node_ != Tree<Key, T>::GetNIL(current_node_))
        return current_node_->value;
      else {
        throw std::out_of_range("This iterator is nullptr");
      }
    };

   private:
    TreeNode *current_node_ = nullptr;
  };

  // Map Iterators
  typedef typename Map<Key, T>::Iterator iterator;

  iterator Begin();
  iterator End();

  // Map Modifiers
  std::pair<iterator, bool> Insert(const value_type &value);
  std::pair<iterator, bool> Insert(const Key &key, const T &obj);
  std::pair<iterator, bool> InsertOrAssign(const Key &key, const T &obj);
  void Merge(Map &other);  // splices nodes from another container
  void Erase(Iterator pos);

  template <class... Args>
  s21::Vector<std::pair<typename Map<Key, T>::iterator, bool>> Emplace(
      Args &&...args);

 private:
  Iterator InsertNode(TreeNode *&n, Key k, T v);
  void DeleteTreeNode(iterator pos);
  bool RootAndLeftChild(iterator pos);
  bool RootAndRightChild(iterator pos);
  bool LeafNode(iterator pos);
  bool LeafLeft(iterator pos);
  bool LeafRight(iterator pos);
  bool RightChild(iterator pos);
  bool CompareKey(iterator pos);
  bool LeftChild(iterator pos);
  bool CompareKey_(iterator pos);
};
#include "s21_map.tpp"
}  // namespace s21

#endif  // SRC_s21_CONTAINERS_MAP_S21_MAP_H
