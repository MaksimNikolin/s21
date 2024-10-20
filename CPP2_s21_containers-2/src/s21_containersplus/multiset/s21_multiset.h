#ifndef SRC_S21_CONTAINERS_MULTISET_S21_MULTISET_H
#define SRC_S21_CONTAINERS_MULTISET_S21_MULTISET_H

#include <initializer_list>
#include <iostream>

#include "../../s21_containers/tree/tree.h"
#include "../../s21_containers/vector/s21_vector.h"

namespace s21 {
template <typename Key, typename T = size_t>
class Multiset : public Tree<Key, T> {
 public:
  using key_type = Key;
  using mapped_type = T;
  using size_type = std::size_t;
  using value_type = Key;  //  value type (the value itself is a key)
  using referens =
      value_type &;  // defines the type of the reference to an element
  using const_reference =
      const value_type &;  // defines the type of the constant reference
  using TreeNode = typename s21::Tree<Key, T>::TreeNode;

  Multiset(){};
  explicit Multiset(const std::initializer_list<value_type> &items);
  explicit Multiset(const Multiset &s);
  Multiset(Multiset &&s);
  ~Multiset() { this->Clear(); };

  Multiset<Key, T> &operator=(
      Multiset<Key, T> &&s);  // assignment operator overload for moving object
  Multiset<Key, T> &operator=(
      const Multiset &s);  // assignment operator overload for coping object

  struct Iterator {
    friend class Multiset;
    Iterator(){};
    explicit Iterator(TreeNode &other) : current_node_(&other){};

    size_t temp = 0;
    typename Multiset<Key, T>::iterator &operator++() {
      if (this->current_node_ != nullptr &&
          this->current_node_ != Tree<Key, T>::GetNIL(this->current_node_)) {
        if (temp < this->current_node_->value) {
          ++temp;
        } else {
          this->current_node_ = Tree<Key, T>::Successor(this->current_node_);
          temp = 0;
        }
      }
      return *this;
    };

    typename Multiset<Key, T>::iterator &operator--() {
      if (this->current_node_ == nullptr)
        throw std::out_of_range("This iterator is nullptr");

      if (this->current_node_ != Tree<Key, T>::GetNIL(this->current_node_)) {
        if (temp > 0) {
          --temp;
        } else {
          this->current_node_ = Tree<Key, T>::Predecessor(this->current_node_);
          temp = this->current_node_->value;
        }
      } else {
        this->current_node_ =
            Tree<Key, T>::RightmostChild(this->current_node_->parent_);
        temp = this->current_node_->value;
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
    typename Multiset<Key, T>::value_type operator*() const {
      if (current_node_ != nullptr && current_node_->left_ != current_node_ &&
          current_node_ != Tree<Key, T>::GetNIL(current_node_)) {
        return current_node_->key_;
      } else {
        throw std::out_of_range("This iterator is nullptr");
      }
    };
    typename Multiset<Key, T>::TreeNode *GetNode() { return current_node_; }

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
    typename Multiset<Key, T>::TreeNode *current_node_ = nullptr;
  };

  // Multiset Iterators
  typedef typename Multiset<Key, T>::Iterator iterator;
  iterator Begin();
  iterator End();

  typename Multiset<Key, T>::iterator Insert(const value_type &value);
  typename Multiset<Key, T>::iterator InsertNode_(TreeNode *&n, Key k);
  void Erase(iterator pos);
  void Merge(Multiset &other);

  template <class... Args>
  s21::Vector<typename Multiset<Key, T>::iterator> Emplace(Args &&...args);

  // Multiset Lookup
  typename Multiset<Key, T>::iterator Find(const Key &key);
  size_t Count(const Key &key);
  std::pair<iterator, iterator> EqualRange(const Key &key);
  typename Multiset<Key, T>::iterator LowerBound(const Key &key);
  typename Multiset<Key, T>::iterator UpperBound(const Key &key);

 private:
  void DeleteTreeNode(iterator pos);
  bool RootAndLeftChild(iterator pos);
  bool RootAndRightChild(iterator pos);
  bool LeafNode(iterator pos);
  bool LeafLeft(iterator pos);
  bool LeafRight(iterator pos);
  bool RightChild(iterator pos);
  bool CompareKeyRight(iterator pos);
  bool LeftChild(iterator pos);
  bool CompareKeyLeft(iterator pos);
};
#include "s21_multiset.tpp"
}  // namespace s21

#endif  // SRC_S21_CONTAINERS_MULTISET_S21_MULTISET_H
