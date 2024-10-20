template <class T, class Container>
Stack<T, Container>::Stack() {}

template <class T, class Container>
Stack<T, Container>::Stack(std::initializer_list<T> const &items) {
  for (const auto &it : items) Push(it);
}

template <class T, class Container>
Stack<T, Container>::Stack(const Container &v) {
  container_(v);
}

template <class T, class Container>
Stack<T, Container>::Stack(const Stack &v) {
  this->container_ = v.container_;
}

template <class T, class Container>
Stack<T, Container>::Stack(Stack &&v) {
  Swap(v);
}

template <class T, class Container>
Stack<T, Container>::~Stack() {}

template <class T, class Container>
Stack<T, Container> &Stack<T, Container>::operator=(Stack &&s) {
  Swap(s);
  s.MakeEmptyStack();
  return *this;
}

template <class T, class Container>
Stack<T, Container> &Stack<T, Container>::operator=(const Stack &v) {
  if (this != &v) {
    MakeEmptyStack();
    this->container_ = v.container_;
  }
  return *this;
}

template <class T, class Container>
const T &Stack<T, Container>::Top() {
  if (Empty()) {
    throw std::out_of_range("Stack is empty.");
  }
  return container_.Back();
}

template <class T, class Container>
bool Stack<T, Container>::Empty() const {
  return container_.Empty();
}

template <class T, class Container>
size_t Stack<T, Container>::Size() {
  return container_.Size();
}

template <class T, class Container>
void Stack<T, Container>::Push(Stack<T, Container>::const_reference value) {
  container_.PushBack(value);
}

template <class T, class Container>
void Stack<T, Container>::Pop() {
  if (!Empty()) {
    container_.PopBack();
  }
}

template <class T, class Container>
void Stack<T, Container>::MakeEmptyStack() {
  while (!Empty()) {
    Pop();
  }
}

template <class T, class Container>
void Stack<T, Container>::Swap(Stack &s) {
  Stack temp;
  temp.container_ = s.container_;
  s.container_ = this->container_;
  this->container_ = temp.container_;
}

template <class T, class Container>
template <class... Args>
void Stack<T, Container>::EmplaceFront(Args &&...args) {
  container_.EmplaceBack(args...);
}
