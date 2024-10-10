#ifndef SRC_S21_CONTAINERS_LIST_LIST_HPP
#define SRC_S21_CONTAINERS_LIST_LIST_HPP

#include <initializer_list>
#include <iostream>
#include <limits>

namespace s21 {

template <typename T>
class list {
 public:
  // Member type
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = std::size_t;

 private:
  struct Node {
    value_type value_;
    Node* prev_;
    Node* next_;

    Node(const value_type& value)
        : value_(value), prev_(nullptr), next_(nullptr) {}
  };

  Node* head_;
  Node* tail_;
  Node* end_;
  size_type size_;

 public:
  // Member Functions
  list();
  ~list();
  list(size_type n);  //
  list(std::initializer_list<value_type> const& items);
  list(const list& l);
  list(list&& l);
  list& operator=(list&& l);

  // Element access
  const_reference front();                               // access the first element
  const_reference back();                                // access the last element

  // Capacity
  bool empty();
  size_type size();
  size_type max_size();

  template <typename value_type>
  class ListIterator {
   public:
    ListIterator() { ptr_ = nullptr; }
    ListIterator(Node* ptr) : ptr_(ptr){};

    reference operator*() { return this->ptr_->value_; }

    ListIterator operator++(int) {
      ptr_ = ptr_->next_;
      return *this;
    }

    ListIterator operator--(int) {
      ptr_ = ptr_->prev_;
      return *this;
    }

    ListIterator& operator++() {
      ptr_ = ptr_->next_;
      return *this;
    }

    ListIterator& operator--() {
      ptr_ = ptr_->prev_;
      return *this;
    }

    ListIterator operator+(const size_type value) {
      Node* tmp = ptr_;
      for (size_type i = 0; i < value; i++) {
        tmp = tmp->next_;
      }

      ListIterator res(tmp);
      return res;
    }

    ListIterator operator-(const size_type value) {
      Node* tmp = ptr_;
      for (size_type i = 0; i < value; i++) {
        tmp = tmp->prev_;
      }
      ListIterator res(tmp);
      return res;
    }

    bool operator==(ListIterator other) { return this->ptr_ == other.ptr_; }
    bool operator!=(ListIterator other) { return this->ptr_ != other.ptr_; }

   private:
    Node* ptr_ = nullptr;
    friend class list<T>;
  };

  template <typename value_type>
  class ListConstIterator : public ListIterator<T> {
   public:
    ListConstIterator(ListIterator<T> other) : ListIterator<T>(other) {}
    const T& operator*() { return ListIterator<T>::operator*(); }
  };

  // Member type
  using iterator = ListIterator<T>;
  using const_iterator = ListConstIterator<T>;

  // Iterators
  iterator begin();                                      // returns an iterator to the beginning
  const_iterator begin() const;
  iterator end();                                        // returns an iterator to the end
  const_iterator end() const;

  // Operations
  void merge(list& other);                               // merges two sorted lists
  void splice(const_iterator pos, list& other);          // moves elements from another list
  void reverse();                                        // reverses the order of the elements
  void unique();                                         // removes consecutive duplicate elements
  void sort();                                           // sorts the elements

  // Modifiers
  void clear();                                          // clears the contents
  iterator insert(iterator pos, const_reference value);  // inserts elements
  void erase(iterator pos);                              // erases elements
  void push_back(const_reference value);                 // adds an element to the end
  void pop_back();                                       // removes the last element
  void push_front(const_reference value);                // inserts an element to the beginning
  void pop_front();                                      // removes the first element
  void swap(list& other);                                // swaps the contents

 private:
  // Additional functions
  void change_end();
  void quick_sort(iterator left, iterator right);
  iterator partition(iterator first, iterator last);
  void copy(const list& l);
  void print_list();
};
}  // namespace s21

#endif  // SRC_S21_CONTAINERS_LIST_LIST_HPP
