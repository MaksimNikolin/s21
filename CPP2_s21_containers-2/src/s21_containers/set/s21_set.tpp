template <typename Key, typename T>
Set<Key, T>::Set(const std::initializer_list<value_type> &items) {
  for (auto it = items.begin(); it != items.end(); ++it) {
    Set<Key, T>::InsertNode(this->root_, *it);
  }
}

template <typename Key, typename T>
Set<Key, T>::Set(const Set &other) : Tree<Key, T>() {
  if (other.root_ == nullptr) return;

  this->CreateNIL();
  this->root_ = this->CopyTree(other.root_);
  this->NIL_->parent_ = this->root_;
  this->root_->parent_ = this->NIL_;
  this->size_ = other.size_;
}

template <typename Key, typename T>
Set<Key, T>::Set(Set &&s) {
  this->Swap(s);
}

template <typename Key, typename T>
Set<Key, T>::~Set() {
  this->Clear();
}

template <typename Key, typename T>
Set<Key, T> &Set<Key, T>::operator=(Set &&s) {
  if (this != &s) {
    this->Swap(s);
  }
  return *this;
}

template <typename Key, typename T>
Set<Key, T> &Set<Key, T>::operator=(const Set &other) {
  if (this != &other) {
    this->Clear();
    this->CreateNIL();
    this->root_ = this->CopyTree(other.root_);
    this->NIL_->parent_ = this->root_;
    this->root_->parent_ = this->NIL_;
    this->size_ = other.size_;
  }
  return *this;
}

template <typename Key, typename T>
typename Set<Key, T>::iterator Set<Key, T>::Begin() {
  TreeNode *a = Set<Key, T>::LeftmostChild(this->root_);
  return iterator(*a);
}

template <typename Key, typename T>
typename Set<Key, T>::iterator Set<Key, T>::End() {
  return iterator(*this->NIL_);
}

template <typename Key, typename T>
std::pair<typename Set<Key, T>::iterator, bool> Set<Key, T>::Insert(
    const value_type &value) {
  typename Tree<Key, T>::iterator it = Find(value);
  bool bool_ins = false;
  if (it.GetNode() == nullptr || it.GetNode() == this->NIL_) {
    it = s21::Tree<Key, T>::InsertNode(this->root_, value);
    bool_ins = true;
  }
  return std::make_pair(it, bool_ins);
}

template <typename Key, typename T>
void Set<Key, T>::Merge(Set &other) {
  s21::Vector<typename s21::Tree<Key, T>::iterator> keep_iterator;
  for (auto it = other.Begin(); it != other.End(); ++it) {
    auto ins = Insert(*it);
    if (ins.second) {
      keep_iterator.PushBack(it);
    }
  }
  for (auto it = keep_iterator.Begin(); it != keep_iterator.End(); ++it) {
    other.Erase(*it);
  }
}

template <typename Key, typename T>
typename Tree<Key, T>::iterator Set<Key, T>::Find(const Key &key) {
  return typename Tree<Key, T>::Iterator(
      *s21::Tree<Key, T>::FindNode(this->root_, key));
}

template <typename Key, typename T>
template <class... Args>
s21::Vector<std::pair<typename Tree<Key, T>::iterator, bool>>
Set<Key, T>::Emplace(Args &&...args) {
  s21::Vector<std::pair<typename Tree<Key, T>::iterator, bool>> resultVector;
  s21::Vector<value_type> tempVector{args...};
  if (tempVector.Size() == 0) {
    TreeNode *tmp = new TreeNode();
    std::pair<s21::Tree<int, bool>::Iterator, bool> res = Insert(tmp->key_);
    resultVector.PushBack(res);
    delete tmp;
  } else {
    for (size_t i = 0; i < tempVector.Size(); ++i) {
      std::pair<s21::Tree<int, bool>::Iterator, bool> it =
          Insert(tempVector[i]);
      resultVector.PushBack(it);
    }
  }
  return resultVector;
}