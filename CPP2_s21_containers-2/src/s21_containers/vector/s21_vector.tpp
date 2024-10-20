
template <typename T>
s21::Vector<T>::Vector() {
  capacity_ = 4;
  size_ = 0U;
  arr_ = new T[4]();
}

template <typename T>
s21::Vector<T>::Vector(const Vector<T> &v)
    : size_(v.size_), capacity_(v.capacity_) {
  arr_ = new T[v.capacity_];
  for (size_t i = 0; i != v.Size(); ++i) {
    arr_[i] = v.arr_[i];
  }
}

template <typename T>
s21::Vector<T>::Vector(Vector<T> &&v) : size_(v.size_), capacity_(v.capacity_) {
  std::swap(arr_, v.arr_);
  v.arr_ = NULL;
  v.size_ = 0;
  v.capacity_ = 0;
}

template <typename T>
s21::Vector<T>::~Vector() {
  if (arr_ != NULL) {
    delete[] arr_;
  }
}

template <typename T>
s21::Vector<T>::Vector(size_type n) {
  if (n > MaxSize()) {
    throw std::length_error("cannot create std::vector larger than max_size()");
  }
  size_ = n;
  capacity_ = n;
  arr_ = new T[n];
}

template <typename T>
s21::Vector<T>::Vector(std::initializer_list<value_type> const &items)
    : size_(0), capacity_(0) {
  if (items.size() > MaxSize()) {
    throw std::length_error("cannot create std::vector larger than max_size()");
  }
  capacity_ = items.size();
  arr_ = new value_type[capacity_]();
  int i = 0;
  for (auto it = items.begin(); it != items.end(); ++it) {
    arr_[i] = *it;
    ++i;
  }
  size_ = items.size();
};

template <typename T>
s21::Vector<T> &s21::Vector<T>::operator=(Vector &&s) {
  if (this == &s) {
  } else {
    std::swap(arr_, s.arr_);
    size_ = s.size_;
    capacity_ = s.capacity_;
  }
  return *this;
}

template <typename T>
s21::Vector<T> &s21::Vector<T>::operator=(const Vector &s) {
  if (this == &s) {
  } else {
    delete[] arr_;
    arr_ = new T[s.capacity_];
    for (size_t i = 0; i != s.Size(); ++i) {
      arr_[i] = s.arr_[i];
    }
    size_ = s.size_;
    capacity_ = s.capacity_;
  }
  return *this;
}

template <typename T>
bool s21::Vector<T>::Empty() const {
  return size_ == 0U;
}

template <typename T>
size_t s21::Vector<T>::Size() const {
  return size_;
}

template <typename T>
size_t s21::Vector<T>::Capacity() const {
  return capacity_;
}

template <typename T>
void s21::Vector<T>::AddMemory() {
  if (size_ == capacity_) {
    if (size_ + 1 > MaxSize()) {
      throw std::length_error(
          "cannot create std::vector larger than max_size()");
    }
    if (capacity_ == 0) {
      capacity_ = 4;
      arr_ = new T[capacity_]();
    } else if (capacity_ * 2 > MaxSize()) {
      capacity_ += 1;
    } else {
      capacity_ *= 2;
    }
    T *tmp = arr_;
    arr_ = new T[capacity_]();
    for (size_t i = 0; i < size_; ++i) arr_[i] = tmp[i];
    delete[] tmp;
  }
}

template <typename T>
void s21::Vector<T>::PushBack(const T &value) {
  AddMemory();
  arr_[size_++] = value;
}

template <typename T>
void s21::Vector<T>::PopBack() {
  if (arr_ && size_ >= 1) {
    --size_;
  }
}

template <typename T>
typename s21::Vector<T>::reference s21::Vector<T>::At(size_type i) {
  if (i > size_ - 1 || size_ == 0) {
    throw std::out_of_range("Error. Index is out of range.");
  }
  return arr_[i];
}

template <typename T>
typename s21::Vector<T>::reference s21::Vector<T>::operator[](
    size_type position) {
  return arr_[position];
}

template <typename T>
typename s21::Vector<T>::const_reference s21::Vector<T>::Front() {
  return arr_[0];
}

template <typename T>
typename s21::Vector<T>::const_reference s21::Vector<T>::Back() {
  return arr_[size_ - 1];
}

template <typename T>
typename s21::Vector<T>::iterator s21::Vector<T>::Data() {
  return arr_;
}

template <typename T>
typename s21::Vector<T>::iterator s21::Vector<T>::Begin() {
  return arr_;
}

template <typename T>
typename s21::Vector<T>::iterator s21::Vector<T>::End() {
  return arr_ + size_;
}

template <typename T>
size_t s21::Vector<T>::MaxSize() {
  return (LLONG_MAX) / (sizeof(value_type));
}

template <typename T>
void s21::Vector<T>::Reserve(size_type neo_size) {
  if (neo_size > MaxSize()) {
    throw std::out_of_range("Error. New size is out of range.");
  }
  if (neo_size > Capacity()) {
    capacity_ = neo_size;
    ReallocVector();
  }
}

template <typename T>
void s21::Vector<T>::Clear() {
  size_ = 0;
}

template <typename T>
void s21::Vector<T>::ShrinkToFit() {
  capacity_ = size_;
  ReallocVector();
}

template <typename T>
void s21::Vector<T>::Swap(Vector<T> &other) {
  std::swap(capacity_, other.capacity_);
  std::swap(size_, other.size_);
  std::swap(arr_, other.arr_);
}

template <typename T>
void s21::Vector<T>::ReallocVector() {
  if (capacity_ == 0) {
    delete[] arr_;
    arr_ = NULL;
    size_ = 0;
  } else {
    iterator newArray = new value_type[size_]();
    for (size_t i = 0; i < size_; ++i) {
      newArray[i] = arr_[i];
    }
    std::swap(arr_, newArray);
    delete[] newArray;
  }
}

template <typename T>
void s21::Vector<T>::Erase(iterator it) {
  if (arr_) {
    std::move(it + 1, arr_ + size_, it);
    --size_;
  }
}

template <typename T>
typename s21::Vector<T>::iterator s21::Vector<T>::Insert(
    iterator it, const_reference value) {
  if ((size_ + 1) > MaxSize()) {
    std::out_of_range("Error. Pos is out of range.");
  }
  size_t pos = it - arr_;
  if (size_ == 0) {
    PushBack(value);
  } else {
    if (size_ == capacity_) {
      AddMemory();
    }

    for (size_t i = Size(), j = Size() - 1; i != 0; i--, j--) {
      arr_[i] = arr_[j];
      if (i == pos) {
        arr_[i] = value;
        ++j;
      }
    }
    ++size_;
    it = arr_ + pos;
    arr_[pos] = value;
  }

  return it;
}

template <class T>
template <class... Args>
void s21::Vector<T>::EmplaceBack(Args &&...args) {
  s21::Vector<value_type> tempVector{args...};
  if (tempVector.Size() == 0) {
    T data = {};
    PushBack(data);
  } else {
    for (size_t i = 0; i < tempVector.Size(); ++i) {
      PushBack(tempVector[i]);
    }
  }
}

template <class T>
template <class... Args>
typename s21::Vector<T>::iterator s21::Vector<T>::Emplace(iterator pos,
                                                          Args &&...args) {
  s21::Vector<value_type> tempVector{args...};
  if (tempVector.Size() == 0) {
    T tmp = {};
    pos = Insert(pos, tmp);
  } else {
    for (size_t i = 0; i < tempVector.Size(); ++i) {
      pos = Insert(pos, tempVector[i]);
    }
  }
  return pos;
}
