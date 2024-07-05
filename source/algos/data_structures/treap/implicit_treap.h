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
  int prior;
  size_t count;
  T value;
  Node* l;
  Node* r;

  Node(int prior_, T value_) : prior(prior_), count(1), value(std::move(value_)), l(nullptr), r(nullptr) {}
  Node(T value_) : prior(getRandom()), count(1), value(std::move(value_)), l(nullptr), r(nullptr) {}
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
    merge(l->r, l->r, r), t = l;
  } else {
    merge(r->l, l, r->l), t = r;
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
  } else {
    split(t->r, t->r, r, key, add + 1 + count(t->l));
    l = t;
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
    merge(t, t->l, t->r);
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
void insertImpl(Node<T>*& t, T val, size_t pos)
{
  algos::implicit_treap_utils::Node<T>* t1;
  algos::implicit_treap_utils::Node<T>* t2;
  algos::implicit_treap_utils::split(t, t1, t2, pos);
  algos::implicit_treap_utils::Node<T>* n = new algos::implicit_treap_utils::Node<T>(val);
  algos::implicit_treap_utils::merge(t1, t1, n);
  algos::implicit_treap_utils::merge(t, t1, t2);
}

template <typename T>
T& getImpl(Node<T>*& t, size_t key, size_t add = 0)
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

  // Expected runtime = O(n * log(n)), worst runtime O(n * n), memory = O(n).
  ImplicitTreap(size_t n) : nodePtr(nullptr)
  {
    for (size_t i = 0; i < n; ++i) {
      push_back(T{});
    }
  }

  // Expected runtime = O(n * log(n)), worst runtime O(n * n), memory = O(n).
  ImplicitTreap(std::vector<T> v) : nodePtr(nullptr)
  {
    for (const auto& t : v) {
      push_back(t);
    }
  }

  // runtime = O(n), memory = O(1).
  ~ImplicitTreap() { del(nodePtr); }

  // runtime = O(1), memory = O(1).
  size_t size() { return algos::implicit_treap_utils::count(nodePtr); }

  // Expected runtime = O(log(n)), worst runtime O(n), memory = O(1).
  void push_back(T val) { insertImpl(nodePtr, val, size()); }

  // Expected runtime = O(log(n)), worst runtime O(n), memory = O(1).
  void insert(T val, size_t pos)
  {
    if (pos >= size()) {
      throw std::overflow_error("insert pos is out of bound");
    }
    insertImpl(nodePtr, val, pos);
  }

  // Expected runtime = O(log(n)), worst runtime O(n), memory = O(1).
  void erase(size_t pos)
  {
    if (pos >= size()) {
      throw std::overflow_error("erase pos is out of bound");
    }
    algos::implicit_treap_utils::eraseImpl(nodePtr, pos);
  }

  // Expected runtime = O(log(n)), worst runtime O(n), memory = O(1).
  T& operator[](size_t pos)
  {
    if (pos >= size()) {
      throw std::overflow_error("operator[] pos is out of bound");
    }
    return algos::implicit_treap_utils::getImpl(nodePtr, pos);
  }

private:
  algos::implicit_treap_utils::Node<T>* nodePtr;
};

#endif  // ALGOS_DATA_STRUCTURES_IMPLICIT_TREAP_INCLUDED
