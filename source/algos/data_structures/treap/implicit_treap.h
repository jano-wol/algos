#ifndef ALGOS_DATA_STRUCTURES_IMPLICIT_TREAP_INCLUDED
#define ALGOS_DATA_STRUCTURES_IMPLICIT_TREAP_INCLUDED

#include <algorithm>
#include <fstream>
#include <random>
#include <vector>

bool janoGlob = false;

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

  using PMap = std::map<Node*, std::pair<Node*, Node*>>;

  void getMap(PMap& map)
  {
    map.insert({this, {l, r}});
    if (l) {
      l->getMap(map);
    }
    if (r) {
      r->getMap(map);
    }
  }

  void printMap(std::string s)
  {
    std::string path = "/home/jw/Repositories/algos/" + s;
    std::ofstream f(path);
    if (!f) {
      std::cout << "para";
    }
    PMap m;
    getMap(m);
    f << "basePtr=" << this << "\n";
    for (auto [x, y] : m) {
      auto [v, w] = y;
      f << x << " " << v << " " << w << " p=" << x->p << "\n";
    }
  }
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
  auto t_s = t;
  std::cout << "merge_start t=" << t << " l=" << l << " r=" << r << "\n";
  if (!l || !r) {
    t = l ? l : r;
    std::cout << "merge0 t_s=" << t_s << " l=" << l << " r=" << r << " t_e=" << t << "\n";
  } else if (l->prior > r->prior) {
    merge(l->r, l->r, r);
    t = l;
    l->r->p = l;
    // std::cout << l << " " << l->r << "!\n";
    std::cout << "merge1 t_s=" << t_s << " l=" << l << " r=" << r << " t_e=" << t << "\n";
  } else {
    merge(r->l, l, r->l);
    t = r;
    r->l->p = r;
    //    std::cout << r << " " << r->l << "!\n";
    std::cout << "merge2 t_s=" << t_s << " l=" << l << " r=" << r << " t_e=" << t << "\n";
  }
  updateCount(t);
}

template <typename T>
void split(Node<T>* t, Node<T>*& l, Node<T>*& r, size_t key, size_t add = 0)
{
  std::cout << "split t=" << t << " l=" << l << " r=" << r << "\n";
  if (!t) {
    return void(l = r = 0);
  }
  size_t currKey = add + count(t->l);
  if (key <= currKey) {
    split(t->l, l, t->l, key, add);
    r = t;
    if (r->l)
      r->l->p = r;
  } else {
    split(t->r, t->r, r, key, add + 1 + count(t->l));
    l = t;
    if (l->r)
      l->r->p = l;
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
void testParentsImpl(algos::implicit_treap_utils::Node<T>* curr, algos::implicit_treap_utils::Node<T>* parent)
{
  if (!curr) {
    return;
  }
  if (curr->p != parent) {
    std::cout << "halal\n";
  }
  testParentsImpl(curr->l, curr);
  testParentsImpl(curr->r, curr);
}

template <typename T>
void insertImpl(Node<T>*& t, T val, size_t pos, Node<T>* endNode)
{
  if (janoGlob) {
    if (t)
      t->printMap("before");
    std::cout << "zzzzzzzzzzzzzzzzzzzzzzzzzzzz\n";
  }
  algos::implicit_treap_utils::Node<T>* t1;
  algos::implicit_treap_utils::Node<T>* t2;
  algos::implicit_treap_utils::split(t, t1, t2, pos);
  algos::implicit_treap_utils::Node<T>* n = new algos::implicit_treap_utils::Node<T>(val, endNode);
  algos::implicit_treap_utils::merge(t1, t1, n);
  testParentsImpl(t1, t1->p);
  std::cout << "merge1 done\n";
  algos::implicit_treap_utils::merge(t, t1, t2);
  if (janoGlob)
    t->printMap("after");
  testParentsImpl(t, t->p);
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
    if (val == -1) {
      std::cout << "zzzzzzzzzz\n";
    }
    insertImpl(nodePtr, val, size(), &endNode);
    testParents();
  }

  // expected runtime = O(log(n)), worst runtime O(n), memory = O(1).
  void insert(T val, size_t pos)
  {
    if (jano) {
      janoGlob = jano;
    }
    if (pos >= size()) {
      throw std::overflow_error("insert pos is out of bound");
    }
    insertImpl(nodePtr, val, pos, &endNode);
    testParents();
  }

  // expected runtime = O(log(n)), worst runtime O(n), memory = O(1).
  void erase(size_t pos)
  {
    if (pos >= size()) {
      throw std::overflow_error("erase pos is out of bound");
    }
    algos::implicit_treap_utils::eraseImpl(nodePtr, pos);
  }

  // expected runtime = O(log(n)), worst runtime O(n), memory = O(1).
  T& operator[](size_t pos) const
  {
    if (pos >= size()) {
      throw std::overflow_error("operator[] pos is out of bound");
    }
    return algos::implicit_treap_utils::getImpl(nodePtr, pos);
  }

  struct Iterator
  {
    using iterator_category = std::forward_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = algos::implicit_treap_utils::Node<T>;
    using pointer = value_type*;
    using reference = value_type&;

    Iterator(pointer ptr) : mPtr(ptr) {}

    reference operator*() const { return *mPtr; }
    pointer operator->() { return mPtr; }
    Iterator& operator++()
    {
      if (mPtr->r != nullptr) {
        mPtr = mPtr->r;
        while (mPtr->l != nullptr) {
          mPtr = mPtr->l;
        }
      } else {
        auto y = mPtr->p;
        while (mPtr == y->r) {
          mPtr = y;
          y = y->p;
        }
        if (mPtr->r != y)
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
  Iterator end() { return Iterator(&endNode); }

  // private:
  algos::implicit_treap_utils::Node<T>* nodePtr;
  algos::implicit_treap_utils::Node<T> endNode;
  bool jano = false;

  void fixParentsImpl(algos::implicit_treap_utils::Node<T>* curr, algos::implicit_treap_utils::Node<T>* parent)
  {
    curr->p = parent;
    if (curr->l) {
      fixParentsImpl(curr->l, curr);
    }
    if (curr->r) {
      fixParentsImpl(curr->r, curr);
    }
  }

  void testParents() { testParentsImpl(nodePtr, &endNode); }

  void fixParents() { fixParentsImpl(nodePtr, &endNode); }
};

#endif  // ALGOS_DATA_STRUCTURES_IMPLICIT_TREAP_INCLUDED
