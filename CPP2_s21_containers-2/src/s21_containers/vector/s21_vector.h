#ifndef _SRC_SRC_S21_CONTAINERS_VECTOR_S21_VECTOR_H_
#define _SRC_SRC_S21_CONTAINERS_VECTOR_S21_VECTOR_H_
#include <climits>
#include <cmath>
#include <initializer_list>
#include <iostream>

namespace s21 {
template <typename T>
class Vector {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

  Vector();
  explicit Vector(size_type n);
  Vector(const Vector<T> &v);
  Vector(Vector<T> &&v);
  explicit Vector(std::initializer_list<value_type> const &items);
  ~Vector();
  Vector<T> &operator=(const Vector &s);
  Vector<T> &operator=(Vector &&s);

  reference At(size_type position);
  reference operator[](size_type position);
  const_reference Front();
  const_reference Back();
  iterator Data();

  iterator Begin();
  iterator End();

  bool Empty() const;
  size_t Size() const;
  size_t Capacity() const;
  void Reserve(size_type size);
  void ShrinkToFit();
  size_type MaxSize();

  void Clear();
  iterator Insert(iterator pos, const_reference value);
  void Erase(iterator index);
  void PushBack(const T &value);
  void PopBack();
  void Swap(Vector<T> &other);

  template <class... Args>
  void EmplaceBack(Args &&...args);

  template <class... Args>
  iterator Emplace(iterator it, Args &&...args);

 private:
  T *arr_ = nullptr;
  size_t size_ = 0;
  size_t capacity_ = 0;

  void ReallocVector();
  void AddMemory();
};
}  // namespace s21

#include "s21_vector.tpp"
#endif  // _SRC_SRC_S21_CONTAINERS_VECTOR_S21_VECTOR_H_
