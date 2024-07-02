#ifndef ALGOS_DATA_STRUCTURES_IMPLICIT_TREAP_INCLUDED
#define ALGOS_DATA_STRUCTURES_IMPLICIT_TREAP_INCLUDED

#include <algorithm>
#include <vector>

namespace
{
template <typename T>
class ImplicitTreap<T>;

template <typename T>
int cnt(ImplicitTreap<T>::Ptr it)
{
  return it ? it->cnt : 0;
}

template <typename T>
void upd_cnt(ImplicitTreap<T>::Ptr it)
{
  if (it)
    it->cnt = cnt(it->l) + cnt(it->r) + 1;
}

template <typename T>
void push(ImplicitTreap<T>::Ptr it)
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
void merge(ImplicitTreap<T>::Ptr& t, ImplicitTreap<T>::Ptr l, ImplicitTreap<T>::Ptr r)
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
void split(ImplicitTreap<T>::Ptr t, ImplicitTreap<T>::Ptr& l, ImplicitTreap<T>::Ptr& r, int key, int add = 0)
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
void reverse(ImplicitTreap<T>::Ptr t, int l, int r)
{
  ImplicitTreap<T>::Ptr t1, t2, t3;
  split(t, t1, t2, l);
  split(t2, t2, t3, r - l + 1);
  t2->rev ^= true;
  merge(t, t1, t2);
  merge(t, t, t3);
}
}  // namespace

template <typename T>
class ImplicitTreap
{
public:
  using Ptr = ImplicitTreap*;
  
  int prior;
  int cnt;
  T value;
  bool rev;
  Ptr l;
  Ptr r;
};

#endif  // ALGOS_DATA_STRUCTURES_IMPLICIT_TREAP_INCLUDED
