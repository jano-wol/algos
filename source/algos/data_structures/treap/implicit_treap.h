#ifndef ALGOS_DATA_STRUCTURES_IMPLICIT_TREAP_INCLUDED
#define ALGOS_DATA_STRUCTURES_IMPLICIT_TREAP_INCLUDED

#include <algorithm>
#include <random>
#include <vector>

namespace algos::implicit_treap_utils
{
std::mt19937 randomGenerator;
int getRandom() { return randomGenerator(); }

template <typename T>
struct Node
{
  T value;
  Node* p;
  int prior;
  size_t count;
  Node* l;
  Node* r;

  Node() : value(), p(nullptr), prior(getRandom()), count(1), l(nullptr), r(nullptr) {}
  Node(T value_) : value(std::move(value_)), p(nullptr), prior(getRandom()), count(1), l(nullptr), r(nullptr) {}
  Node(T value_, Node* p_) : value(std::move(value_)), p(p_), prior(getRandom()), count(1), l(nullptr), r(nullptr) {}
  Node(T value_, Node* p_, int prior_)
      : value(std::move(value_)), p(p_), prior(prior_), count(1), l(nullptr), r(nullptr)
  {}
  Node(T value_, Node* p_, int prior_, size_t count_)
      : value(std::move(value_)), p(p_), prior(prior_), count(count_), l(nullptr), r(nullptr)
  {}
};

template <typename T>
size_t count(Node<T>* it)
{
  return it ? it->count : 0;
}

template <typename T>
void updateCount(Node<T>* it)
{
  if (it) {
    it->count = count(it->l) + count(it->r) + 1;
  }
}

template <typename T>
void merge(Node<T>*& t, Node<T>* l, Node<T>* r)
{
  if (!l || !r) {
    t = l ? l : r;
  } else if (l->prior > r->prior) {
    merge(l->r, l->r, r);
    t = l;
    l->r->p = l;
  } else {
    merge(r->l, l, r->l);
    t = r;
    r->l->p = r;
  }
  updateCount(t);
}

template <typename T>
void split(Node<T>* t, Node<T>*& l, Node<T>*& r, size_t key, size_t add = 0)
{
  if (!t) {
    return void(l = r = 0);
  }
  size_t currKey = add + count(t->l);
  if (key <= currKey) {
    split(t->l, l, t->l, key, add);
    r = t;
    if (r->l) {
      r->l->p = r;
    }
  } else {
    split(t->r, t->r, r, key, add + 1 + count(t->l));
    l = t;
    if (l->r) {
      l->r->p = l;
    }
  }
  updateCount(t);
}

template <typename T>
void del(Node<T>* t)
{
  if (!t) {
    return;
  }
  del(t->l);
  del(t->r);
  delete t;
}

template <typename T>
void eraseImpl(Node<T>*& t, size_t key, size_t add = 0)
{
  size_t currKey = add + count(t->l);
  if (currKey == key) {
    Node<T>* th = t;
    Node<T>* thp = t->p;
    merge(t, t->l, t->r);
    if (t) {
      t->p = thp;
    }
    delete th;
  } else {
    if (key <= currKey) {
      eraseImpl(t->l, key, add);
    } else {
      eraseImpl(t->r, key, add + 1 + count(t->l));
    }
    updateCount(t);
  }
}

template <typename T>
void insertImpl(Node<T>*& t, size_t pos, T val, Node<T>* endNode)
{
  algos::implicit_treap_utils::Node<T>* t1;
  algos::implicit_treap_utils::Node<T>* t2;
  algos::implicit_treap_utils::split(t, t1, t2, pos);
  algos::implicit_treap_utils::Node<T>* n = new algos::implicit_treap_utils::Node<T>(val, endNode);
  algos::implicit_treap_utils::merge(t1, t1, n);
  algos::implicit_treap_utils::merge(t, t1, t2);
}

template <typename T>
void buildImpl(Node<T>*& tNew, Node<T>* tOld, Node<T>* p)
{
  if (!tOld) {
    tNew = nullptr;
    return;
  }
  tNew = new algos::implicit_treap_utils::Node<T>(tOld->value, p, tOld->prior, tOld->count);
  buildImpl(tNew->l, tOld->l, tNew);
  buildImpl(tNew->r, tOld->r, tNew);
}

template <typename T>
T& getImpl(Node<T>* t, size_t key, size_t add = 0)
{
  size_t currKey = add + count(t->l);
  if (currKey == key) {
    return t->value;
  } else {
    if (key <= currKey) {
      return getImpl(t->l, key, add);
    } else {
      return getImpl(t->r, key, add + 1 + count(t->l));
    }
  }
}
}  // namespace algos::implicit_treap_utils

template <typename T>
class ImplicitTreap
{
public:
  // runtime = O(1), memory = O(1).
  ImplicitTreap() : nodePtr(nullptr) {}

  // expected runtime = O(n * log(n)), worst runtime O(n * n), memory = O(n).
  ImplicitTreap(size_t n) : nodePtr(nullptr)
  {
    for (size_t i = 0; i < n; ++i) {
      push_back(T{});
    }
  }

  // expected runtime = O(n * log(n)), worst runtime O(n * n), memory = O(n).
  ImplicitTreap(std::vector<T> v) : nodePtr(nullptr)
  {
    for (const auto& t : v) {
      push_back(t);
    }
  }

  // runtime = O(n), memory = O(n).
  ImplicitTreap(const ImplicitTreap& other) { buildImpl(nodePtr, other.nodePtr, &endNode); }

  // runtime = O(n), memory = O(n).
  ImplicitTreap& operator=(const ImplicitTreap& other)
  {
    if (this != &other) {
      del(nodePtr);
      buildImpl(nodePtr, other.nodePtr, &endNode);
    }
    return *this;
  }

  // runtime = O(1), memory = O(1).
  ImplicitTreap(ImplicitTreap&& other) : nodePtr(other.nodePtr) { other.nodePtr = nullptr; }

  ImplicitTreap& operator=(ImplicitTreap&& other) noexcept
  {
    if (this != &other) {
      del(nodePtr);
      nodePtr = other.nodePtr;
      other.nodePtr = nullptr;
    }
    return *this;
  }

  // runtime = O(n), memory = O(1).
  ~ImplicitTreap() { del(nodePtr); }

  // runtime = O(1), memory = O(1).
  size_t size() const { return algos::implicit_treap_utils::count(nodePtr); }

  // expected runtime = O(log(n)), worst runtime O(n), memory = O(1).
  void push_back(T val)
  {
    insertImpl(nodePtr, size(), val, &endNode);
    endNode.r = nodePtr;
  }

  // expected runtime = O(log(n)), worst runtime O(n), memory = O(1).
  void insert(size_t pos, T val)
  {
    if (pos >= size() + 1) {
      throw std::out_of_range("insert pos is out of range");
    }
    insertImpl(nodePtr, pos, val, &endNode);
    endNode.r = nodePtr;
  }

  // expected runtime = O(log(n)), worst runtime O(n), memory = O(1).
  void erase(size_t pos)
  {
    if (pos >= size()) {
      throw std::out_of_range("erase pos is out of range");
    }
    algos::implicit_treap_utils::eraseImpl(nodePtr, pos);
    endNode.r = nodePtr;
  }

  // expected runtime = O(log(n)), worst runtime O(n), memory = O(1).
  T& operator[](size_t pos) const
  {
    if (pos >= size()) {
      throw std::out_of_range("operator[] pos is out of range");
    }
    return algos::implicit_treap_utils::getImpl(nodePtr, pos);
  }

  struct Iterator
  {
    using iterator_category = std::bidirectional_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = algos::implicit_treap_utils::Node<T>;
    using pointer = value_type*;
    using reference = T&;

    Iterator(pointer ptr) : mPtr(ptr) {}

    reference operator*()
    {
      if (!mPtr->p) {
        throw std::out_of_range("endNode dereference");
      }
      return mPtr->value;
    }
    pointer operator->() { return mPtr; }
    Iterator& operator++()
    {
      if ((mPtr->r != nullptr)) {
        mPtr = mPtr->r;
        while (mPtr->l != nullptr) {
          mPtr = mPtr->l;
        }
      } else {
        auto y = mPtr->p;
        while ((y) && (mPtr == y->r)) {
          mPtr = y;
          y = y->p;
        }
        if ((y) && (mPtr->r != y))
          mPtr = y;
      }
      return *this;
    }
    Iterator& operator--()
    {
      if (mPtr->p == nullptr) {
        if (!(mPtr->r)) {
          return *this;
        }
        auto y = mPtr->r;
        while (y->r != nullptr) {
          y = y->r;
        }
        mPtr = y;
        return *this;
      }
      if (mPtr->l != nullptr) {
        mPtr = mPtr->l;
        while (mPtr->r != nullptr) {
          mPtr = mPtr->r;
        }
      } else {
        auto y = mPtr->p;
        while (mPtr == y->l) {
          mPtr = y;
          y = y->p;
        }
        if (mPtr->l != y)
          mPtr = y;
      }
      return *this;
    }
    Iterator operator++(int)
    {
      Iterator tmp = *this;
      ++(*this);
      return tmp;
    }
    Iterator operator--(int)
    {
      Iterator tmp = *this;
      --(*this);
      return tmp;
    }
    friend bool operator==(const Iterator& a, const Iterator& b) { return a.mPtr == b.mPtr; };
    friend bool operator!=(const Iterator& a, const Iterator& b) { return a.mPtr != b.mPtr; };

  private:
    pointer mPtr;
  };

  Iterator begin()
  {
    if (size() == 0) {
      return Iterator(&endNode);
    }
    auto y = nodePtr;
    while (y->l != nullptr) {
      y = y->l;
    }
    return Iterator(y);
  }
  std::reverse_iterator<Iterator> rbegin() { return std::reverse_iterator<Iterator>(end()); }
  Iterator end() { return Iterator(&endNode); }
  std::reverse_iterator<Iterator> rend() { return std::reverse_iterator<Iterator>(begin()); }

private:
  algos::implicit_treap_utils::Node<T>* nodePtr;
  algos::implicit_treap_utils::Node<T> endNode;
};

#endif  // ALGOS_DATA_STRUCTURES_IMPLICIT_TREAP_INCLUDED
