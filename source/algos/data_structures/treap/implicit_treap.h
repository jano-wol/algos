#ifndef ALGOS_DATA_STRUCTURES_IMPLICIT_TREAP_INCLUDED
#define ALGOS_DATA_STRUCTURES_IMPLICIT_TREAP_INCLUDED

#include <algorithm>
#include <random>
#include <vector>

namespace
{
template <typename T>
struct Node
{
  int prior;
  int cnt;
  T value;
  bool rev;
  Node* l;
  Node* r;
};

std::mt19937 randomGenerator;

int getRandom() { return randomGenerator(); }

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
void push(Node<T>* it)
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
void merge(Node<T>*& t, Node<T>* l, Node<T>* r)
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
void split(Node<T>* t, Node<T>*& l, Node<T>*& r, int key, int add = 0)
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
void reverse(Node<T>* t, int l, int r)
{
  Node<T>* t1;
  Node<T>* t2;
  Node<T>* t3;
  split(t, t1, t2, l);
  split(t2, t2, t3, r - l + 1);
  t2->rev ^= true;
  merge(t, t1, t2);
  merge(t, t, t3);
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
}  // namespace

template <typename T>
class ImplicitTreap
{
public:
  ImplicitTreap() : nodePtr(nullptr) {}
  ~ImplicitTreap() { del(nodePtr); }

  void insert(int pos, T val)
  {
    Node<T>* t1;
    Node<T>* t2;
    split(nodePtr, t1, t2, pos);
    auto prior = getRandom();
    Node<T>* n = new Node<T>;
    n->prior = prior;
    n->value = val;
    n->cnt = 1;
    n->l = nullptr;
    n->r = nullptr;
    merge(t1, t1, n);
    merge(nodePtr, t1, t2);
  }

  void erase(int pos) { eraseImpl(nodePtr, pos); }

  int size() { return cnt(nodePtr); }

private:
  Node<T>* nodePtr;
};

#endif  // ALGOS_DATA_STRUCTURES_IMPLICIT_TREAP_INCLUDED
