#ifndef ALGOS_DATA_STRUCTURES_DISJOINT_SET_UNION_EXTRA_INCLUDED
#define ALGOS_DATA_STRUCTURES_DISJOINT_SET_UNION_EXTRA_INCLUDED

#include <functional>
#include <iostream>
#include <vector>

template <typename T>
class DisjointSetUnionExtra
{
public:
  // runtime = O(n), memory = O(n).
  DisjointSetUnionExtra(size_t n_, std::vector<T> extra_, std::function<void(size_t, size_t, std::vector<T>&)> extraOp_)
      : n(n_), extra(std::move(extra_)), extraOp(std::move(extraOp_))
  {
    numberOfComponents = n;
    parent.resize(n);
    size.resize(n, 1);
    for (size_t i = 0; i < n; ++i) {
      parent[i] = i;
    }
  }

  // runtime = amortized O(alpha(n)), memory = O(1), where alpha(n) is the inverse Ackermann function.
  size_t findSet(size_t v)
  {
    if (v >= n) {
      throw std::overflow_error("v is out of bound");
    }
    if (v == parent[v]) {
      return v;
    }
    return parent[v] = findSet(parent[v]);
  }

  // runtime = amortized O(alpha(n) * extraOp(n)), memory = O(1), where alpha(n) is the inverse Ackermann function.
  void unionSets(size_t a, size_t b)
  {
    a = findSet(a);
    b = findSet(b);
    if (a != b) {
      if (size[a] < size[b])
        std::swap(a, b);
      parent[b] = a;
      size[a] += size[b];
      extraOp(a, b, extra);
      --numberOfComponents;
    }
  }

  size_t getN() const { return n; }
  size_t getNumberOfComponents() const { return numberOfComponents; }
  const std::vector<size_t>& getParent() const { return parent; }
  std::vector<size_t>& getParentMutable() { return parent; }
  const std::vector<size_t>& getSize() const { return size; }
  const std::vector<T>& getExtra() const { return extra; }
  std::vector<T>& getExtraMutable() { return extra; }

private:
  size_t n;
  size_t numberOfComponents;
  std::vector<size_t> parent;
  std::vector<size_t> size;
  std::vector<T> extra;
  std::function<void(size_t, size_t, std::vector<T>&)> extraOp;
};

#endif  // ALGOS_DATA_STRUCTURES_DISJOINT_SET_UNION_INCLUDED
