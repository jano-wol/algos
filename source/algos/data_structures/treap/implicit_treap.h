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
  int cnt;
  T value;
  Node* l;
  Node* r;

  Node(int prior_, T value_) : prior(prior_), cnt(1), value(std::move(value_)), l(nullptr), r(nullptr) {}
  Node(T value_) : prior(getRandom()), cnt(1), value(std::move(value_)), l(nullptr), r(nullptr) {}
};

template <typename T>
int cnt(Node<T>* it)
{
  return it ? it->cnt : 0;
}

template <typename T>
void upd_cnt(Node<T>* it)
{
  if (it)
    it->cnt = cnt(it->l) + cnt(it->r) + 1;
}

template <typename T>
void merge(Node<T>*& t, Node<T>* l, Node<T>* r)
{
  if (!l || !r)
    t = l ? l : r;
  else if (l->prior > r->prior)
    merge(l->r, l->r, r), t = l;
  else
    merge(r->l, l, r->l), t = r;
  upd_cnt(t);
}

template <typename T>
void split(Node<T>* t, Node<T>*& l, Node<T>*& r, int key, int add = 0)
{
  if (!t)
    return void(l = r = 0);
  int cur_key = add + cnt(t->l);
  if (key <= cur_key)
    split(t->l, l, t->l, key, add), r = t;
  else
    split(t->r, t->r, r, key, add + 1 + cnt(t->l)), l = t;
  upd_cnt(t);
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
void eraseImpl(Node<T>*& t, int key, int add = 0)
{
  int cur_key = add + cnt(t->l);
  if (cur_key == key) {
    Node<T>* th = t;
    merge(t, t->l, t->r);
    delete th;
  } else {
    if (key <= cur_key) {
      eraseImpl(t->l, key, add);
    } else {
      eraseImpl(t->r, key, add + 1 + cnt(t->l));
    }
    upd_cnt(t);
  }
}

template <typename T>
T& getImpl(Node<T>*& t, int key, int add = 0)
{
  int cur_key = add + cnt(t->l);
  if (cur_key == key) {
    return t->value;
  } else {
    if (key <= cur_key) {
      return getImpl(t->l, key, add);
    } else {
      return getImpl(t->r, key, add + 1 + cnt(t->l));
    }
  }
}

}  // namespace algos::implicit_treap_utils

template <typename T>
class ImplicitTreap
{
public:
  ImplicitTreap() : nodePtr(nullptr) {}
  ~ImplicitTreap() { del(nodePtr); }

  void insert(int pos, T val)
  {
    algos::implicit_treap_utils::Node<T>* t1;
    algos::implicit_treap_utils::Node<T>* t2;
    algos::implicit_treap_utils::split(nodePtr, t1, t2, pos);
    algos::implicit_treap_utils::Node<T>* n = new algos::implicit_treap_utils::Node<T>(val);
    algos::implicit_treap_utils::merge(t1, t1, n);
    algos::implicit_treap_utils::merge(nodePtr, t1, t2);
  }

  void erase(int pos) { algos::implicit_treap_utils::eraseImpl(nodePtr, pos); }

  int size() { return algos::implicit_treap_utils::cnt(nodePtr); }

  T& operator[](int pos) { return algos::implicit_treap_utils::getImpl(nodePtr, pos); }

private:
  algos::implicit_treap_utils::Node<T>* nodePtr;
};

#endif  // ALGOS_DATA_STRUCTURES_IMPLICIT_TREAP_INCLUDED
