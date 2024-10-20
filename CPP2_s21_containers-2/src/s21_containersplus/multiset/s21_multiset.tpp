template <typename Key, typename T>
inline s21::Multiset<Key, T>::Multiset(
    const std::initializer_list<value_type> &items) {
  for (auto it = items.begin(); it != items.end(); ++it) {
    Insert(*it);
  }
}

template <typename Key, typename T>
Multiset<Key, T>::Multiset(const Multiset &other) : Tree<Key, T>() {
  if (other.root_ == nullptr) return;

  this->CreateNIL();
  this->root_ = Tree<Key, T>::CopyTree(other.root_);
  this->NIL_->parent_ = this->root_;
  this->root_->parent_ = this->NIL_;
  this->size_ = other.size_;
}

template <typename Key, typename T>
Multiset<Key, T>::Multiset(Multiset &&s) {
  this->Swap(s);
}

template <typename Key, typename T>
Multiset<Key, T> &Multiset<Key, T>::operator=(Multiset &&s) {
  if (this != &s) {
    this->Swap(s);
  }
  return *this;
}

template <typename Key, typename T>
Multiset<Key, T> &Multiset<Key, T>::operator=(const Multiset &s) {
  if (this != &s) {
    this->Clear();
    this->CreateNIL();
    this->root_ = Tree<Key, T>::CopyTree(s.root_);
    this->NIL_->parent_ = this->root_;
    if (this->root_) this->root_->parent_ = this->NIL_;
    this->size_ = s.size_;
  }
  return *this;
}

template <typename Key, typename T>
typename Multiset<Key, T>::iterator Multiset<Key, T>::InsertNode_(TreeNode *&n,
                                                                  Key k) {
  if (n == nullptr || n == this->NIL_) {
    n = new TreeNode(k);
    if (this->size_ == 0) {
      this->CreateNIL();
      n->parent_ = this->NIL_;
      this->NIL_->parent_ = n;
    }
    n->left_ = this->NIL_;
    n->right_ = this->NIL_;
    n->value = 0;
    ++this->size_;
  } else if (k < n->key_) {
    InsertNode_(n->left_, k);
    n->left_->parent_ = n;
  } else if (k > n->key_) {
    InsertNode_(n->right_, k);
    n->right_->parent_ = n;
  }
  return iterator(*this->FindNode(n, k));
}

template <typename Key, typename T>
typename Multiset<Key, T>::iterator s21::Multiset<Key, T>::Begin() {
  TreeNode *a = Multiset<Key, T>::LeftmostChild(this->root_);
  return iterator(*a);
}

template <typename Key, typename T>
typename Multiset<Key, T>::iterator s21::Multiset<Key, T>::End() {
  return iterator(*this->NIL_);
}

template <typename Key, typename T>
typename Multiset<Key, T>::iterator Multiset<Key, T>::Insert(
    const value_type &key) {
  iterator it = Find(key);
  if (it.GetNode() != nullptr && it.GetNode() != this->NIL_) {
    it.GetNode()->value += 1;
    ++this->size_;
  } else {
    it = InsertNode_(this->root_, key);
  }

  return it;
}

template <typename Key, typename T>
void Multiset<Key, T>::Merge(Multiset &other) {
  for (auto it = other.Begin(); it != other.End(); ++it) {
    Insert(it.First());
  }
  other.Clear();
}

template <typename Key, typename T>
typename Multiset<Key, T>::iterator Multiset<Key, T>::Find(const Key &key) {
  return typename Multiset<Key, T>::Iterator(
      *s21::Tree<Key, T>::FindNode(this->root_, key));
}

template <typename Key, typename T>
typename Multiset<Key, T>::iterator Multiset<Key, T>::LowerBound(const Key &k) {
  return Find(k);
}

template <typename Key, typename T>
typename Multiset<Key, T>::iterator Multiset<Key, T>::UpperBound(const Key &k) {
  return Iterator(
      *Tree<Key, T>::Successor(Tree<Key, T>::FindNode(this->root_, k)));
}

template <typename Key, typename T>
size_t Multiset<Key, T>::Count(const Key &k) {
  size_t n = 0;
  Iterator it = Find(k);
  if (it.GetNode() != nullptr && it.GetNode() != this->NIL_) {
    n = it.GetNode()->value + 1;
  }
  return n;
}

template <typename Key, typename T>
std::pair<typename s21::Multiset<Key, T>::iterator,
          typename s21::Multiset<Key, T>::iterator>
Multiset<Key, T>::EqualRange(const Key &key) {
  iterator it = LowerBound(key);
  iterator it_end = UpperBound(key);
  return std::make_pair(it, it_end);
}

template <typename Key, typename T>
void Multiset<Key, T>::Erase(Iterator pos) {
  if (pos.current_node_ != nullptr || pos.current_node_ != this->NIL_) {
    // If the node is a root node
    if (RootAndLeftChild(pos)) {
      if (pos.current_node_->value > 0) {
        --pos.current_node_->value;
      } else {
        this->root_ = pos.current_node_->left_;
        this->root_->parent_ = this->NIL_;
        pos.current_node_->left_ = this->NIL_;
        DeleteTreeNode(pos);
      }
      --this->size_;
    } else if (RootAndRightChild(pos)) {
      if (pos.current_node_->value > 0) {
        --pos.current_node_->value;
      } else {
        this->root_ = pos.current_node_->right_;
        this->root_->parent_ = this->NIL_;
        pos.current_node_->right_ = this->NIL_;
        DeleteTreeNode(pos);
      }
      --this->size_;

      // If the node is a leaf node
    } else if (LeafNode(pos)) {
      if (pos.current_node_->value > 0) {
        --pos.current_node_->value;
      } else {
        if (LeafLeft(pos)) pos.current_node_->parent_->left_ = this->NIL_;
        if (LeafRight(pos)) pos.current_node_->parent_->right_ = this->NIL_;
        DeleteTreeNode(pos);
      }
      --this->size_;

      // The node have only child at right
    } else if (RightChild(pos)) {
      if (pos.current_node_->value > 0) {
        --pos.current_node_->value;
      } else {
        pos.current_node_->right_->parent_ = pos.current_node_->parent_;
        if (CompareKeyRight(pos)) {
          pos.current_node_->parent_->left_ = pos.current_node_->right_;
        } else {
          if (pos.current_node_->parent_)
            pos.current_node_->parent_->right_ = pos.current_node_->right_;
        }
        DeleteTreeNode(pos);
      }
      --this->size_;

      // The node have only child at left
    } else if (LeftChild(pos)) {
      if (pos.current_node_->value > 0) {
        --pos.current_node_->value;
      } else {
        pos.current_node_->left_->parent_ = pos.current_node_->parent_;
        if (CompareKeyLeft(pos)) {
          pos.current_node_->parent_->right_ = pos.current_node_->left_;
        } else {
          pos.current_node_->parent_->left_ = pos.current_node_->left_;
        }
        DeleteTreeNode(pos);
      }
      --this->size_;

      // The node have two children (left and right)
    } else {
      if (Tree<Key, T>::Predecessor(pos.current_node_) &&
          pos.current_node_->value > 0) {
        --pos.current_node_->value;
        --this->size_;
      } else {
        pos.current_node_->key_ =
            Tree<Key, T>::Predecessor(pos.current_node_)->key_;
        pos.current_node_->value =
            Tree<Key, T>::Predecessor(pos.current_node_)->value;
        Erase(Iterator(*Tree<Key, T>::Predecessor(pos.current_node_)));
      }
    }
    if (this->size_ == 0) Tree<Key, T>::DeleteNIL();
  }
}

template <typename Key, typename T>
template <class... Args>
s21::Vector<typename Multiset<Key, T>::iterator> Multiset<Key, T>::Emplace(
    Args &&...args) {
  s21::Vector<typename Multiset<Key, T>::iterator> resultVector;
  s21::Vector<value_type> tempVector{args...};
  if (tempVector.Size() == 0) {
    TreeNode *tmp = new TreeNode();
    typename Multiset<Key, T>::iterator it = Insert(tmp->key_);
    resultVector.PushBack(it);
    delete tmp;
  } else {
    for (size_t i = 0; i < tempVector.Size(); ++i) {
      typename Multiset<Key, T>::iterator it = Insert(tempVector[i]);
      resultVector.PushBack(it);
    }
  }
  return resultVector;
}

template <typename Key, typename T>
void Multiset<Key, T>::DeleteTreeNode(iterator pos) {
  delete pos.current_node_;
  pos.current_node_ = nullptr;
}

template <typename Key, typename T>
bool Multiset<Key, T>::RootAndLeftChild(iterator pos) {
  bool temp = false;
  if (pos.current_node_->parent_ == this->NIL_ && pos.current_node_->left_ &&
      pos.current_node_->right_ == this->NIL_)
    temp = true;
  return temp;
}

template <typename Key, typename T>
bool Multiset<Key, T>::RootAndRightChild(iterator pos) {
  bool temp = false;
  if (pos.current_node_->parent_ == this->NIL_ && pos.current_node_->right_ &&
      pos.current_node_->left_ == this->NIL_)
    temp = true;
  return temp;
}

template <typename Key, typename T>
bool Multiset<Key, T>::LeafNode(iterator pos) {
  bool temp = false;
  if (pos.current_node_->left_ == this->NIL_ &&
      pos.current_node_->right_ == this->NIL_)
    temp = true;
  return temp;
}

template <typename Key, typename T>
bool Multiset<Key, T>::LeafLeft(iterator pos) {
  bool temp = false;
  if (pos.current_node_->parent_ &&
      pos.current_node_ == pos.current_node_->parent_->left_)
    temp = true;
  return temp;
}

template <typename Key, typename T>
bool Multiset<Key, T>::LeafRight(iterator pos) {
  bool temp = false;
  if (pos.current_node_->parent_ &&
      pos.current_node_ == pos.current_node_->parent_->right_)
    temp = true;
  return temp;
}

template <typename Key, typename T>
bool Multiset<Key, T>::RightChild(iterator pos) {
  bool temp = false;
  if (pos.current_node_->left_ == this->NIL_ &&
      pos.current_node_->right_ != this->NIL_)
    temp = true;
  return temp;
}

template <typename Key, typename T>
bool Multiset<Key, T>::LeftChild(iterator pos) {
  bool temp = false;
  if (pos.current_node_->left_ != this->NIL_ &&
      pos.current_node_->right_ == this->NIL_)
    temp = true;
  return temp;
}
template <typename Key, typename T>
bool Multiset<Key, T>::CompareKeyRight(iterator pos) {
  bool temp = false;
  if (pos.current_node_->parent_ &&
      pos.current_node_->right_->key_ < pos.current_node_->parent_->key_)
    temp = true;
  return temp;
}

template <typename Key, typename T>
bool Multiset<Key, T>::CompareKeyLeft(iterator pos) {
  bool temp = false;
  if (pos.current_node_->parent_ &&
      pos.current_node_->left_->key_ > pos.current_node_->parent_->key_)
    temp = true;
  return temp;
}
