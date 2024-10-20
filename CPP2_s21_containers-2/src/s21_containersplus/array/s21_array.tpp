template <typename T, size_t N>
Array<T, N>::Array() {}

template <typename T, size_t N>
Array<T, N>::Array(const Array<T, N> &v) {
  for (size_t i = 0; i != v.Size(); ++i) {
    arr_[i] = v.arr_[i];
  }
}

template <typename T, size_t N>
Array<T, N>::Array(Array<T, N> &&v) {
  std::swap(arr_, v.arr_);
}

template <typename T, size_t N>
Array<T, N>::~Array() {}

template <typename T, size_t N>
Array<T, N>::Array(std::initializer_list<value_type> const &items) {
  if (items.size() > N) {
    throw std::length_error("cannot create std::Array larger than its size()");
  }
  size_t i = 0;
  for (auto it = items.begin(); it != items.end(); ++it) {
    arr_[i] = *it;
    ++i;
  }
};

template <typename T, size_t N>
Array<T, N> &Array<T, N>::operator=(const Array<T, N> &v) {
  if (this == &v) {
  } else {
    for (size_t i = 0; i != v.Size(); ++i) {
      arr_[i] = v.arr_[i];
    }
  }
  return *this;
}

template <typename T, size_t N>
Array<T, N> &Array<T, N>::operator=(Array<T, N> &&v) {
  if (N == v.Size()) std::swap(arr_, v.arr_);
  return *this;
}

template <typename T, size_t N>
bool Array<T, N>::Empty() const {
  return N == 0;
}

template <typename T, size_t N>
size_t Array<T, N>::Size() const {
  return N;
}

template <typename T, size_t N>
typename Array<T, N>::reference Array<T, N>::At(size_type i) {
  if (i > N - 1) {
    throw std::out_of_range("Error. Index is out of range.");
  }
  return arr_[i];
}

template <typename T, size_t N>
typename Array<T, N>::reference Array<T, N>::operator[](size_type position) {
  return arr_[position];
}

template <typename T, size_t N>
typename Array<T, N>::const_reference Array<T, N>::Front() {
  return arr_[0];
}

template <typename T, size_t N>
typename Array<T, N>::const_reference Array<T, N>::Back() {
  return arr_[N - 1];
}

template <typename T, size_t N>
typename Array<T, N>::iterator Array<T, N>::Data() {
  return arr_;
}

template <typename T, size_t N>
typename Array<T, N>::iterator Array<T, N>::Begin() {
  return arr_;
}

template <typename T, size_t N>
typename Array<T, N>::iterator Array<T, N>::End() {
  return arr_ + N;
}

template <typename T, size_t N>
size_t Array<T, N>::MaxSize() {
  return N;
}

template <typename T, size_t N>
void s21::Array<T, N>::Swap(Array<T, N> &other) {
  if (N == other.Size()) {
    for (size_t i = 0; i < N; i++) std::swap(arr_[i], other.arr_[i]);
  }
}

template <typename T, size_t N>
void s21::Array<T, N>::Fill(const_reference value) {
  for (size_t i = 0; i != Size(); ++i) {
    arr_[i] = value;
  }
}
