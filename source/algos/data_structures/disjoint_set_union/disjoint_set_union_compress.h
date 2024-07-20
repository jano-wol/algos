#ifndef ALGOS_DATA_STRUCTURES_DISJOINT_SET_UNION_COMPRESS_INCLUDED
#define ALGOS_DATA_STRUCTURES_DISJOINT_SET_UNION_COMPRESS_INCLUDED

#include <iostream>
#include <vector>

class DisjointSetUnionCompress
{
public:
  // runtime = O(n), memory = O(n).
  DisjointSetUnionCompress(size_t n_) : n(n_)
  {
    parent.resize(n);
    for (size_t i = 0; i < n; ++i) {
      parent[i] = i;
    }
  }

  // runtime = amortized O(log(n)), memory = O(1).
  size_t findSet(size_t v)
  {
    if (v >= n) {
      throw std::out_of_range("v is out of bound");
    }
    if (v == parent[v]) {
      return v;
    }
    return parent[v] = findSet(parent[v]);
  }

  // runtime = O(1), memory = O(1).
  void connect(size_t a, size_t b)
  {
    if ((a >= n) || (b >= n)) {
      throw std::out_of_range("out of bound");
    }
    parent[a] = b;
  }

  size_t getN() const { return n; }

private:
  std::vector<size_t> parent;
  size_t n;
};

#endif  // ALGOS_DATA_STRUCTURES_DISJOINT_SET_UNION_COMPRESS_INCLUDED
