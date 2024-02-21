#ifndef ALGOS_DATA_STRUCTURES_DISJOINT_SET_UNION_INCLUDED
#define ALGOS_DATA_STRUCTURES_DISJOINT_SET_UNION_INCLUDED

#include <iostream>
#include <vector>

class DisjointSetUnion
{
public:
  // runtime = O(n), memory = O(n).
  DisjointSetUnion(size_t n_) : n(n_)
  {
    numberOfComponents = n;
    parent.resize(n);
    size.resize(n, 1);
    for (size_t i = 0; i < n; ++i) {
      parent[i] = i;
    }
  }

  // runtime = amortized O(alpha(n)), memory = O(1), where alpha(n) is the inverse Ackermann function
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

  // runtime = amortized O(alpha(n)), memory = O(1), where alpha(n) is the inverse Ackermann function
  void unionSets(size_t a, size_t b)
  {
    a = findSet(a);
    b = findSet(b);
    if (a != b) {
      if (size[a] < size[b])
        std::swap(a, b);
      parent[b] = a;
      size[a] += size[b];
      --numberOfComponents;
    }
  }

  size_t getN() const { return n; }
  size_t getNumberOfComponents() const { return numberOfComponents; }
  const std::vector<size_t>& getParent() const { return parent; }
  const std::vector<size_t>& getSize() const { return size; }

private:
  size_t n;
  size_t numberOfComponents;
  std::vector<size_t> parent;
  std::vector<size_t> size;
};

#endif  // ALGOS_DATA_STRUCTURES_DISJOINT_SET_UNION_INCLUDED
