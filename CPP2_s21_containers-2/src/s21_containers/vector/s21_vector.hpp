#ifndef SRC_S21_CONTAINERS_VECTOR_VECTOR_HPP
#define SRC_S21_CONTAINERS_VECTOR_VECTOR_HPP

#include <cmath>
#include <initializer_list>
#include <iostream>
using namespace std;

namespace s21 {

template <class T>
class VectorIterator {
  friend class vector<T>;

  using value_type = T;
  using reference = T &;
  using pointer = T *;

 public:
  VectorIterator() { ptr_ = nullptr; }
  VectorIterator(pointer ptr) { ptr_ = ptr; }

  value_type &operator*() const { return (*ptr_); }
  pointer operator->() { return ptr_; }

  VectorIterator &operator++() {
    ptr_++;
    return *this;
  }
  VectorIterator &operator--() {
    ptr_--;
    return *this;
  }
  VectorIterator operator++(int) {
    VectorIterator tmp = *this;
    ++(*this);
    return tmp;
  }
  VectorIterator operator--(int) {
    VectorIterator tmp = *this;
    --(*this);
    return tmp;
  }
  VectorIterator operator+(const size_t value) {
    VectorIterator tmp(this->ptr_ + value);
    return tmp;
  }
  VectorIterator operator-(const size_t value) {
    VectorIterator tmp(this->ptr_ - value);
    return tmp;
  }
  bool operator==(const VectorIterator &other) { return ptr_ == other.ptr_; }
  bool operator!=(const VectorIterator &other) { return ptr_ != other.ptr_; }

 private:
  pointer ptr_;
};

template <class T>
class vector {
 public:
  // Member types
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using pointer = T *;
  using size_type = std::size_t;
  using iterator = VectorIterator<T>;

  // Member functions
  vector();
  ~vector();
  vector(size_type n);
  vector(std::initializer_list<T> const &items);
  vector(const vector &v);
  vector(vector &&v);
  vector &operator=(vector &&v);

  // Element access
  reference at(size_type pos);                     // access specified element with bounds checking
  reference operator[](size_type pos);             // access specified element
  const_reference front();                         // access the first element
  const_reference back();                          // access the last element
  pointer data();                                  // direct access to contiguous storage

  // Iterators
  iterator begin();                                // returns an iterator to the beginning
  iterator end();                                  // returns an iterator to the end

  // Capacity
  bool empty() const;                              // checks whether the container is empty
  size_type size() const;                          // returns the number of elements
  size_type max_size() const;                      // returns max possible number of elements
  void reserve(size_type new_cap);                 // reserves storage
  size_type capacity() const;                      // returns count of elements in allocated storage
  void shrink_to_fit();                            // reduces memory usage by freeing unused memory

  // Modifiers
  void clear();                                          // clears the contents
  iterator insert(iterator pos, const_reference value);  // inserts elements
  void erase(iterator pos);                              // erases elements
  void push_back(const_reference value);                 // adds an element to the end
  void pop_back();                                       // removes the last element
  void swap(vector &other);                              // swaps the contents

 protected:
 private:
  size_type size_;
  size_type capacity_;
  value_type *container_;

  // Additional functions
  void bring_to_zero();
  void add_memory(size_type size, bool flag);
  size_type add_memory_size(size_type size, bool flag);
  void copy_vector(const vector &v);
  void remove();
};
}  // namespace s21

#endif  // SRC_S21_CONTAINERS_VECTOR_VECTOR_HPP
