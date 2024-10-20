template <typename Key, typename T>
Map<Key, T>::Map(std::initializer_list<value_type> const &items) {
  for (auto it = items.begin(); it != items.end(); ++it) {
    InsertNode(this->root_, it->first, it->second);
  }
}

template <typename Key, typename T>
Map<Key, T>::Map(const Map &m) : Tree<Key, T>() {
  if (m.root_ == nullptr) return;
  this->CreateNIL();
  this->root_ = this->CopyTree(m.root_);
  this->NIL_->parent_ = this->root_;
  this->root_->parent_ = this->NIL_;
  this->size_ = m.size_;
}

template <typename Key, typename T>
Map<Key, T>::Map(Map &&m) {
  this->Swap(m);
}

template <typename Key, typename T>
Map<Key, T>::~Map() {
  this->Clear();
}

template <typename Key, typename T>
Map<Key, T> &Map<Key, T>::operator=(Map<Key, T> &&m) {
  if (this != &m) {
    this->Swap(m);
  }
  return *this;
}

template <typename Key, typename T>
Map<Key, T> &Map<Key, T>::operator=(const Map<Key, T> &m) {
  if (this != &m) {
    this->Clear();
    this->root_ = this->CopyTree(m.root_);
    this->size_ = m.size_;
  }
  return *this;
}

template <typename Key, typename T>
T &Map<Key, T>::operator[](const Key &key) {
  typename Map<Key, T>::iterator it =
      typename Map<Key, T>::iterator(*(this->FindNode(this->root_, key)));
  if (it.GetNode() == nullptr || it.GetNode() == this->NIL_) {
    T value = {};
    it = InsertNode(this->root_, key, value);
  }
  return it.GetNode()->value;
}

template <typename Key, typename T>
typename Map<Key, T>::iterator s21::Map<Key, T>::Begin() {
  TreeNode *a = this->LeftmostChild(this->root_);
  return iterator(*a);
}

template <typename Key, typename T>
typename Map<Key, T>::iterator s21::Map<Key, T>::End() {
  return iterator(*this->NIL_);
}

template <typename Key, typename T>
T &Map<Key, T>::At(const Key &k) {
  typename Map<Key, T>::iterator it =
      typename Map<Key, T>::iterator(*(this->FindNode(this->root_, k)));
  if (it.GetNode() == nullptr || it.GetNode() == this->NIL_) {
    throw std::out_of_range("Incorrect input, index is out of range");
  }
  return it.GetNode()->value;
}

template <typename Key, typename T>
std::pair<typename Map<Key, T>::iterator, bool> Map<Key, T>::Insert(
    const value_type &value) {
  return Insert(value.first, value.second);
}

template <typename Key, typename T>
std::pair<typename Map<Key, T>::iterator, bool> Map<Key, T>::Insert(
    const Key &key, const T &obj) {
  typename Map<Key, T>::iterator it =
      typename Map<Key, T>::iterator(*(this->FindNode(this->root_, key)));
  bool bool_ins = false;
  if (it.GetNode() == nullptr || it.GetNode() == this->NIL_) {
    it = InsertNode(this->root_, key, obj);
    bool_ins = true;
  }
  return std::make_pair(it, bool_ins);
}

template <typename Key, typename T>
std::pair<typename Map<Key, T>::iterator, bool> Map<Key, T>::InsertOrAssign(
    const Key &key, const T &obj) {
  typename Map<Key, T>::iterator it =
      typename Map<Key, T>::iterator(*(this->FindNode(this->root_, key)));
  bool bool_ins = false;

  if (it.GetNode() == nullptr || it.GetNode() == this->NIL_) {
    it = InsertNode(this->root_, key, obj);
    bool_ins = true;
  } else {
    // заменяем значение по ключу
    it.GetNode()->value = obj;
  }
  return std::make_pair(it, bool_ins);
}

template <typename Key, typename T>
void Map<Key, T>::Merge(Map &other) {
  s21::Vector<typename s21::Map<Key, T>::iterator> keep_iterator;
  for (auto it = other.Begin(); it != other.End(); ++it) {
    auto ins = Insert((*it).first, (*it).second);
    if (ins.second) {
      keep_iterator.PushBack(it);
    }
  }
  for (auto it = keep_iterator.Begin(); it != keep_iterator.End(); ++it) {
    other.Erase(*it);
  }
}

template <typename Key, typename T>
template <class... Args>
s21::Vector<std::pair<typename Map<Key, T>::iterator, bool>>
Map<Key, T>::Emplace(Args &&...args) {
  s21::Vector<std::pair<typename Map<Key, T>::iterator, bool>> resultVector;
  s21::Vector<std::pair<Key, T>> tempVector{args...};
  if (tempVector.Size() == 0) {
    TreeNode *tmp = new TreeNode();
    std::pair<typename Map<Key, T>::iterator, bool> res =
        Insert(tmp->key_, tmp->value);
    resultVector.PushBack(res);
    delete tmp;
  } else {
    for (size_t i = 0; i < tempVector.Size(); ++i) {
      std::pair<typename Map<Key, T>::iterator, bool> res =
          Insert(tempVector[i]);
      resultVector.PushBack(res);
    }
  }
  return resultVector;
}

template <typename Key, typename T>
typename Map<Key, T>::iterator Map<Key, T>::InsertNode(TreeNode *&n, Key k,
                                                       T v) {
  if (n == nullptr || n == this->NIL_) {
    n = new TreeNode(k, v);
    if (this->size_ == 0) {
      this->CreateNIL();
      n->parent_ = this->NIL_;
      this->NIL_->parent_ = n;
    }
    n->left_ = this->NIL_;
    n->right_ = this->NIL_;
    ++this->size_;
  } else if (k < n->key_) {
    InsertNode(n->left_, k, v);
    n->left_->parent_ = n;
  } else if (k > n->key_) {
    InsertNode(n->right_, k, v);
    n->right_->parent_ = n;
  }
  return Iterator(*this->FindNode(n, k));
}

template <typename Key, typename T>
void Map<Key, T>::Erase(typename Map<Key, T>::Iterator pos) {
  if (pos.current_node_ != nullptr || pos.current_node_ != this->NIL_) {
    // If the node is a root node
    if (RootAndLeftChild(pos)) {
      this->root_ = pos.current_node_->left_;
      this->root_->parent_ = this->NIL_;
      pos.current_node_->left_ = this->NIL_;
      DeleteTreeNode(pos);
    } else if (RootAndRightChild(pos)) {
      this->root_ = pos.current_node_->right_;
      this->root_->parent_ = this->NIL_;
      pos.current_node_->right_ = this->NIL_;
      DeleteTreeNode(pos);

      // If the node is a leaf node
    } else if (LeafNode(pos)) {
      if (LeafLeft(pos)) pos.current_node_->parent_->left_ = this->NIL_;
      if (LeafRight(pos)) pos.current_node_->parent_->right_ = this->NIL_;
      DeleteTreeNode(pos);

      // The node have only child at right
    } else if (RightChild(pos)) {
      pos.current_node_->right_->parent_ = pos.current_node_->parent_;
      if (CompareKey(pos)) {
        pos.current_node_->parent_->left_ = pos.current_node_->right_;
      } else if (pos.current_node_->parent_) {
        pos.current_node_->parent_->right_ = pos.current_node_->right_;
      }
      DeleteTreeNode(pos);

      // The node have only child at left
    } else if (LeftChild(pos)) {
      pos.current_node_->left_->parent_ = pos.current_node_->parent_;
      if (CompareKey_(pos)) {
        pos.current_node_->parent_->right_ = pos.current_node_->left_;
      } else {
        pos.current_node_->parent_->left_ = pos.current_node_->left_;
      }
      DeleteTreeNode(pos);

      // The node have two children (left and right)
    } else {
      pos.current_node_->key_ = this->Predecessor(pos.current_node_)->key_;
      pos.current_node_->value = this->Predecessor(pos.current_node_)->value;
      Erase(Iterator(*this->Predecessor(pos.current_node_)));
    }
    if (this->size_ == 0) this->DeleteNIL();
  }
}

template <typename Key, typename T>
void Map<Key, T>::DeleteTreeNode(iterator pos) {
  delete pos.current_node_;
  pos.current_node_ = nullptr;
  --this->size_;
}

template <typename Key, typename T>
bool Map<Key, T>::RootAndLeftChild(iterator pos) {
  bool temp = false;
  if (pos.current_node_->parent_ == this->NIL_ && pos.current_node_->left_ &&
      pos.current_node_->right_ == this->NIL_)
    temp = true;
  return temp;
}

template <typename Key, typename T>
bool Map<Key, T>::RootAndRightChild(iterator pos) {
  bool temp = false;
  if (pos.current_node_->parent_ == this->NIL_ && pos.current_node_->right_ &&
      pos.current_node_->left_ == this->NIL_)
    temp = true;
  return temp;
}

template <typename Key, typename T>
bool Map<Key, T>::LeafNode(iterator pos) {
  bool temp = false;
  if (pos.current_node_->left_ == this->NIL_ &&
      pos.current_node_->right_ == this->NIL_)
    temp = true;
  return temp;
}

template <typename Key, typename T>
bool Map<Key, T>::LeafLeft(iterator pos) {
  bool temp = false;
  if (pos.current_node_->parent_ &&
      pos.current_node_ == pos.current_node_->parent_->left_)
    temp = true;
  return temp;
}

template <typename Key, typename T>
bool Map<Key, T>::LeafRight(iterator pos) {
  bool temp = false;
  if (pos.current_node_->parent_ &&
      pos.current_node_ == pos.current_node_->parent_->right_)
    temp = true;
  return temp;
}

template <typename Key, typename T>
bool Map<Key, T>::RightChild(iterator pos) {
  bool temp = false;
  if (pos.current_node_->left_ == this->NIL_ &&
      pos.current_node_->right_ != this->NIL_)
    temp = true;
  return temp;
}

template <typename Key, typename T>
bool Map<Key, T>::LeftChild(iterator pos) {
  bool temp = false;
  if (pos.current_node_->left_ != this->NIL_ &&
      pos.current_node_->right_ == this->NIL_)
    temp = true;
  return temp;
}
template <typename Key, typename T>
bool Map<Key, T>::CompareKey(iterator pos) {
  bool temp = false;
  if (pos.current_node_->parent_ &&
      pos.current_node_->right_->key_ < pos.current_node_->parent_->key_)
    temp = true;
  return temp;
}

template <typename Key, typename T>
bool Map<Key, T>::CompareKey_(iterator pos) {
  bool temp = false;
  if (pos.current_node_->parent_ &&
      pos.current_node_->left_->key_ > pos.current_node_->parent_->key_)
    temp = true;
  return temp;
}
