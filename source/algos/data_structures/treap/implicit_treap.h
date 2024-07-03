#ifndef ALGOS_DATA_STRUCTURES_IMPLICIT_TREAP_INCLUDED
#define ALGOS_DATA_STRUCTURES_IMPLICIT_TREAP_INCLUDED

#include <algorithm>
#include <random>
#include <vector>

namespace
{
template <typename T>
class ImplicitTreap<T>;

template <typename T>
int cnt(ImplicitTreap<T>::Node::Ptr it)
{
  return it ? it->cnt : 0;
}

template <typename T>
void upd_cnt(ImplicitTreap<T>::Node::Ptr it)
{
  if (it)
    it->cnt = cnt(it->l) + cnt(it->r) + 1;
}

template <typename T>
void push(ImplicitTreap<T>::Node::Ptr it)
{
  if (it && it->rev) {
    it->rev = false;
    std::swap(it->l, it->r);
    if (it->l)
      it->l->rev ^= true;
    if (it->r)
      it->r->rev ^= true;
  }
}

template <typename T>
void merge(ImplicitTreap<T>::Node::Ptr& t, ImplicitTreap<T>::Node::Ptr l, ImplicitTreap<T>::Node::Ptr r)
{
  push(l);
  push(r);
  if (!l || !r)
    t = l ? l : r;
  else if (l->prior > r->prior)
    merge(l->r, l->r, r), t = l;
  else
    merge(r->l, l, r->l), t = r;
  upd_cnt(t);
}

template <typename T>
void split(ImplicitTreap<T>::Node::Ptr t, ImplicitTreap<T>::Node::Ptr& l, ImplicitTreap<T>::Node::Ptr& r, int key,
           int add = 0)
{
  if (!t)
    return void(l = r = 0);
  push(t);
  int cur_key = add + cnt(t->l);
  if (key <= cur_key)
    split(t->l, l, t->l, key, add), r = t;
  else
    split(t->r, t->r, r, key, add + 1 + cnt(t->l)), l = t;
  upd_cnt(t);
}

template <typename T>
void reverse(ImplicitTreap<T>::Node::Ptr t, int l, int r)
{
  ImplicitTreap<T>::Node::Ptr t1, t2, t3;
  split(t, t1, t2, l);
  split(t2, t2, t3, r - l + 1);
  t2->rev ^= true;
  merge(t, t1, t2);
  merge(t, t, t3);
}

template <typename T>
void del(ImplicitTreap<T>::Node::Ptr t)
{
  if (!t) {
    return;
  }
  del(t->l);
  del(t->r);
  delete t;
}

template <typename T>
void erase(ImplicitTreap<T>::Node::Ptr& t, int key)
{
  if (t->key == key) {
    ImplicitTreap<T>::Node::Ptr th = t;
    merge(t, t->l, t->r);
    delete th;
  } else
    erase(key < t->key ? t->l : t->r, key);
}

}  // namespace

template <typename T>
class ImplicitTreap
{
public:
  ImplicitTreap() : nodePtr(nullptr) {}
  ~ImplicitTreap() { del(nodePtr); }

  void insert(int pos, T val)
  {
    Node::Ptr t1;
    Node::Ptr t2;
    split(nodePtr, t1, t2, pos);
    auto prior = randomGenerator();
    Node::Ptr n = new Node(prior, 1, val);
    merge(t1, t1, n);
  }

  void erase(int pos) { erase(nodePtr, pos); }

  int size() { return nodePtr ? nodePtr->cnt : 0; }

private:
  struct Node
  {
    using Ptr = Node*;
    int prior;
    int cnt;
    T value;
    bool rev;
    Ptr l;
    Ptr r;
  };

  Node::Ptr nodePtr;
  static std::mt19937 randomGenerator;
};

#endif  // ALGOS_DATA_STRUCTURES_IMPLICIT_TREAP_INCLUDED
