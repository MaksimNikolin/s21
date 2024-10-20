#ifndef SRC_S21_CONTAINERS_TREE_TREE_H_
#define SRC_S21_CONTAINERS_TREE_TREE_H_

#include <climits>
#include <iostream>
namespace s21 {

template <typename Key, typename T>
class Tree {
 public:
  using value_type = Key;
  using reference = Key &;
  using size_type = std::size_t;
  using mapped_type = T;

  bool Empty();
  size_type Size() const;
  size_type MaxSize() const;
  void Clear();
  bool Contains(const Key &k);
  void Erase(typename Tree<Key, T>::Iterator pos);
  void Swap(Tree &other);
  static typename Tree<Key, T>::TreeNode *Successor(
      typename Tree<Key, T>::TreeNode *node);
  static typename Tree<Key, T>::TreeNode *Predecessor(
      typename Tree<Key, T>::TreeNode *node);
  void Clear(typename Tree<Key, T>::TreeNode *&n);
  static typename Tree<Key, T>::TreeNode *LeftmostChild(
      typename Tree<Key, T>::TreeNode *n);
  static typename Tree<Key, T>::TreeNode *RightmostChild(
      typename Tree<Key, T>::TreeNode *n);
  static typename Tree<Key, T>::TreeNode *GetNIL(
      const typename Tree<Key, T>::TreeNode *n);

 protected:
  Tree();
  Tree(const Tree &node);
  Tree(Tree &&other);
  Tree<Key, T> &operator=(const Tree &s);
  Tree<Key, T> &operator=(Tree &&s);
  ~Tree();

  struct TreeNode {
    TreeNode *parent_ = nullptr;
    TreeNode *left_ = nullptr;
    TreeNode *right_ = nullptr;
    Key key_ = {};
    T value = {};
    TreeNode(){};
    explicit TreeNode(Key k) : key_(k), value(){};
    explicit TreeNode(Key k, T v) : key_(k), value(v){};
  };

  struct Iterator {
    friend class Tree;
    Iterator(){};
    explicit Iterator(TreeNode &other) : current_node_(&other){};

    Iterator &operator++() {
      if (current_node_ != nullptr && current_node_ != GetNIL(current_node_)) {
        current_node_ = Successor(current_node_);
      }
      return *this;
    };

    Iterator &operator--() {
      if (current_node_ == nullptr)
        throw std::out_of_range("This iterator is nullptr");

      if (current_node_ != GetNIL(current_node_)) {
        current_node_ = Predecessor(current_node_);
      } else {
        current_node_ = RightmostChild(current_node_->parent_);
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
    Key operator*() const {
      if (current_node_ != nullptr && current_node_->left_ != current_node_) {
        return current_node_->key_;
      } else {
        throw std::out_of_range("This iterator is nullptr");
      }
    };
    const TreeNode *GetNode() const { return current_node_; }

   private:
    TreeNode *current_node_ = nullptr;
  };

  typedef typename Tree<Key, T>::Iterator iterator;
  TreeNode *root_ = nullptr;
  TreeNode *NIL_ = nullptr;
  size_type size_ = 0;

  Iterator InsertNode(TreeNode *&n, Key k);
  TreeNode *FindNode(TreeNode *node, Key k);
  TreeNode *CopyTree(TreeNode *node);

  void CreateNIL();
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
  void DeleteNIL();
};

template <typename Key, typename T>
Tree<Key, T>::Tree() {}

template <typename Key, typename T>
Tree<Key, T>::Tree(const Tree &other) {
  if (other == nullptr) return;

  CreateNIL();
  root_ = CopyTree(other.root_);
  NIL_->parent_ = root_;
  root_->parent_ = NIL_;
  size_ = other.size_;
}

template <typename Key, typename T>
void Tree<Key, T>::CreateNIL() {
  NIL_ = new TreeNode();
  NIL_->parent_ = NIL_;
  NIL_->left_ = NIL_->right_ = NIL_;
}

template <typename Key, typename T>
Tree<Key, T>::Tree(Tree &&other) {
  swap(other);
}

template <typename Key, typename T>
Tree<Key, T> &Tree<Key, T>::operator=(const Tree &s) {
  root_ = this->CopyTree(s);
  size_ = s.size_;
  CreateNIL();
  NIL_->parent_ = root_;
  root_->parent_ = NIL_;
  return *this;
}

template <typename Key, typename T>
Tree<Key, T> &Tree<Key, T>::operator=(Tree &&s) {
  if (this != &s) {
    swap(s);
  }
  return *this;
}

template <typename Key, typename T>
inline Tree<Key, T>::~Tree() {
  Clear();
}

template <typename Key, typename T>
typename Tree<Key, T>::iterator Tree<Key, T>::InsertNode(TreeNode *&n, Key k) {
  if (n == nullptr || n == NIL_) {
    n = new TreeNode(k);
    if (size_ == 0) {
      CreateNIL();
      n->parent_ = NIL_;
      NIL_->parent_ = n;
    }
    n->left_ = NIL_;
    n->right_ = NIL_;
    ++size_;
  } else if (k < n->key_) {
    InsertNode(n->left_, k);
    n->left_->parent_ = n;
  } else if (k > n->key_) {
    InsertNode(n->right_, k);
    n->right_->parent_ = n;
  }
  return Iterator(*FindNode(n, k));
}

template <typename Key, typename T>
typename Tree<Key, T>::TreeNode *Tree<Key, T>::FindNode(TreeNode *node, Key k) {
  if (node == nullptr || node == NIL_ || k == node->key_) return node;
  return FindNode((k < node->key_ ? node->left_ : node->right_), k);
}

template <typename Key, typename T>
typename Tree<Key, T>::TreeNode *Tree<Key, T>::CopyTree(TreeNode *node) {
  if (node == nullptr || node == GetNIL(node)) return nullptr;

  //  TreeNode *newnode = new TreeNode(node->key_);
  TreeNode *newnode = new TreeNode(node->key_, node->value);
  newnode->left_ = newnode->right_ = NIL_;
  newnode->parent_ = NIL_;

  if (node->left_ != GetNIL(node)) {
    newnode->left_ = CopyTree(node->left_);
    newnode->left_->parent_ = newnode;
  }

  if (node->right_ != GetNIL(node)) {
    newnode->right_ = CopyTree(node->right_);
    newnode->right_->parent_ = newnode;
  }

  return newnode;
}

template <typename Key, typename T>
typename Tree<Key, T>::TreeNode *Tree<Key, T>::Successor(TreeNode *node) {
  TreeNode *nil = Tree<Key, T>::GetNIL(node);

  // The successor is the minimum key value
  // of right subtree
  if (node->right_ != nullptr && node->right_ != nil) {
    return LeftmostChild(node->right_);

    // If no any right subtree
  } else {
    TreeNode *tmp_node = node;

    // If currentNode is not root and
    // tmp_node->parent_->key_ < node->key_
    // continue moving up
    while (tmp_node->parent_ != nil) {
      // if (tmp_node->parent_->key_ > node->key_)
      if (tmp_node->parent_->key_ >= node->key_)  // равно для мультисет
        return tmp_node->parent_;

      tmp_node = tmp_node->parent_;
    }

    return nil;
  }
}

template <typename Key, typename T>
typename Tree<Key, T>::TreeNode *Tree<Key, T>::Predecessor(TreeNode *node) {
  TreeNode *nil = Tree<Key, T>::GetNIL(node);

  // The predecessor is the maximum key value
  // of left subtree
  if (node->left_ != nullptr && node->left_ != nil) {
    return RightmostChild(node->left_);

    // If no any left subtree
  } else {
    TreeNode *tmp_node = node;

    // If currentNode is not root and
    // tmp_node->parent_->key_ > node->key_
    // continue moving up
    while (tmp_node->parent_ != nil) {
      // if (tmp_node->parent_->key_ < node->key_)
      if (tmp_node->parent_->key_ <= node->key_)  // равно для мультисет
        return tmp_node->parent_;

      tmp_node = tmp_node->parent_;
    }

    return node;
  }
}

template <typename Key, typename T>
bool Tree<Key, T>::Empty() {
  return size_ == 0;
}

template <typename Key, typename T>
size_t Tree<Key, T>::Size() const {
  return size_;
}

template <typename Key, typename T>
size_t Tree<Key, T>::MaxSize() const {
  return (LLONG_MAX) / (sizeof(TreeNode));
}

template <typename Key, typename T>
void Tree<Key, T>::Clear() {
  Clear(root_);
  if (NIL_) {
    delete NIL_;
    NIL_ = nullptr;
  }
}

template <typename Key, typename T>
void Tree<Key, T>::Clear(TreeNode *&n) {
  if (n && size_ > 0 && n != NIL_) {
    --size_;
    Clear(n->left_);
    Clear(n->right_);
    n->left_ = nullptr;
    n->right_ = nullptr;
    n->parent_ = nullptr;
    delete n;
    n = nullptr;
  }
}

template <typename Key, typename T>
typename Tree<Key, T>::TreeNode *Tree<Key, T>::LeftmostChild(TreeNode *n) {
  if (n == nullptr) return nullptr;

  TreeNode *nil = Tree<Key, T>::GetNIL(n);
  TreeNode *p = n;
  while (p->left_ != nil) {
    p = p->left_;
  }
  return p;
}

template <typename Key, typename T>
typename Tree<Key, T>::TreeNode *Tree<Key, T>::RightmostChild(TreeNode *n) {
  if (n == nullptr) return nullptr;

  TreeNode *nil = Tree<Key, T>::GetNIL(n);
  TreeNode *p = n;
  while (p->right_ != nil) {
    p = p->right_;
  }
  return p;
}

template <typename Key, typename T>
typename Tree<Key, T>::TreeNode *Tree<Key, T>::GetNIL(const TreeNode *n) {
  if (n == nullptr) return nullptr;

  const TreeNode *p = n;
  while (p->left_ != p->right_) {
    p = p->left_;
  }

  return p->left_;
}

template <typename Key, typename T>
void Tree<Key, T>::Erase(typename Tree<Key, T>::Iterator pos) {
  if (pos.current_node_ != nullptr || pos.current_node_ != NIL_) {
    // If the node is a root node with a left child
    if (RootAndLeftChild(pos)) {
      root_ = pos.current_node_->left_;
      root_->parent_ = NIL_;
      pos.current_node_->left_ = NIL_;
      DeleteTreeNode(pos);
      // If the node is a root node with a right child
    } else if (RootAndRightChild(pos)) {
      root_ = pos.current_node_->right_;
      root_->parent_ = NIL_;
      pos.current_node_->right_ = NIL_;
      DeleteTreeNode(pos);
      // If the node is a leaf node
    } else if (LeafNode(pos)) {
      if (LeafLeft(pos)) pos.current_node_->parent_->left_ = NIL_;
      if (LeafRight(pos)) pos.current_node_->parent_->right_ = NIL_;
      DeleteTreeNode(pos);
      // The node have only one child at right
    } else if (RightChild(pos)) {
      pos.current_node_->right_->parent_ = pos.current_node_->parent_;
      if (CompareKeyRight(pos)) {
        pos.current_node_->parent_->left_ = pos.current_node_->right_;
      } else if (pos.current_node_->parent_) {
        pos.current_node_->parent_->right_ = pos.current_node_->right_;
      }
      DeleteTreeNode(pos);
      // The node have only one child at left
    } else if (LeftChild(pos)) {
      pos.current_node_->left_->parent_ = pos.current_node_->parent_;
      if (CompareKeyLeft(pos)) {
        pos.current_node_->parent_->right_ = pos.current_node_->left_;
      } else {
        pos.current_node_->parent_->left_ = pos.current_node_->left_;
      }
      DeleteTreeNode(pos);
      // The node have two children (left and right)
    } else {
      pos.current_node_->key_ = Predecessor(pos.current_node_)->key_;
      Erase(Iterator(*Predecessor(pos.current_node_)));
    }
    if (size_ == 0) DeleteNIL();
  }
}

template <typename Key, typename T>
void Tree<Key, T>::DeleteTreeNode(iterator pos) {
  delete pos.current_node_;
  pos.current_node_ = nullptr;
  --size_;
}

template <typename Key, typename T>
bool Tree<Key, T>::RootAndLeftChild(iterator pos) {
  bool temp = false;
  if (pos.current_node_->parent_ == NIL_ && pos.current_node_->left_ &&
      pos.current_node_->right_ == NIL_)
    temp = true;
  return temp;
}

template <typename Key, typename T>
bool Tree<Key, T>::RootAndRightChild(iterator pos) {
  bool temp = false;
  if (pos.current_node_->parent_ == NIL_ && pos.current_node_->right_ &&
      pos.current_node_->left_ == NIL_)
    temp = true;
  return temp;
}

template <typename Key, typename T>
bool Tree<Key, T>::LeafNode(iterator pos) {
  bool temp = false;
  if (pos.current_node_->left_ == NIL_ && pos.current_node_->right_ == NIL_)
    temp = true;
  return temp;
}

template <typename Key, typename T>
bool Tree<Key, T>::LeafLeft(iterator pos) {
  bool temp = false;
  if (pos.current_node_->parent_ &&
      pos.current_node_ == pos.current_node_->parent_->left_)
    temp = true;
  return temp;
}

template <typename Key, typename T>
bool Tree<Key, T>::LeafRight(iterator pos) {
  bool temp = false;
  if (pos.current_node_->parent_ &&
      pos.current_node_ == pos.current_node_->parent_->right_)
    temp = true;
  return temp;
}

template <typename Key, typename T>
bool Tree<Key, T>::RightChild(iterator pos) {
  bool temp = false;
  if (pos.current_node_->left_ == NIL_ && pos.current_node_->right_ != NIL_)
    temp = true;
  return temp;
}

template <typename Key, typename T>
bool Tree<Key, T>::CompareKeyRight(iterator pos) {
  bool temp = false;
  if (pos.current_node_->parent_ &&
      pos.current_node_->right_->key_ < pos.current_node_->parent_->key_)
    temp = true;
  return temp;
}

template <typename Key, typename T>
bool Tree<Key, T>::LeftChild(iterator pos) {
  bool temp = false;
  if (pos.current_node_->left_ != NIL_ && pos.current_node_->right_ == NIL_)
    temp = true;
  return temp;
}

template <typename Key, typename T>
bool Tree<Key, T>::CompareKeyLeft(iterator pos) {
  bool temp = false;
  if (pos.current_node_->parent_ &&
      pos.current_node_->left_->key_ > pos.current_node_->parent_->key_)
    temp = true;
  return temp;
}

template <typename Key, typename T>
void Tree<Key, T>::DeleteNIL() {
  delete NIL_;
  root_ = nullptr;
  NIL_ = nullptr;
}

template <typename Key, typename T>
void Tree<Key, T>::Swap(Tree &other) {
  std::swap(root_, other.root_);
  std::swap(size_, other.size_);
  std::swap(NIL_, other.NIL_);
}

template <typename Key, typename T>
bool Tree<Key, T>::Contains(const Key &k) {
  TreeNode *temp = FindNode(root_, k);
  if (temp != nullptr && temp != NIL_) {
    return temp->key_ == k;
  } else {
    return false;
  }
}

}  // namespace s21

#endif  // SRC_S21_CONTAINERS_TREE_TREE_H_
