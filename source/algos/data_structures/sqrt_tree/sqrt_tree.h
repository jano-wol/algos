#ifndef ALGOS_DATA_STRUCTURE_SQRT_TREE_INCLUDED
#define ALGOS_DATA_STRUCTURE_SQRT_TREE_INCLUDED

#include <functional>
#include <optional>
#include <vector>

namespace algos::sqrt_tree_utils
{
int log2Up(int n)
{
  int res = 0;
  while ((1 << res) < n) {
    res++;
  }
  return res;
}
}  // namespace algos::sqrt_tree_utils

template <typename T>
class SqrtTree
{
public:
  // runtime = O(n * log(log(n)) * beta), memory = O(n * gamma), where op calls are in O(beta), and the size of T is in
  // O(gamma). Typically beta=1, gamma=1.
  SqrtTree(std::vector<T> v_, std::function<T(const T&, const T&)> op_)
      : v(std::move(v_)),
        op(std::move(op_)),
        n(v.size()),
        logVal(algos::sqrt_tree_utils::log2Up(n)),
        clz(1 << logVal),
        onLayer(logVal + 1)
  {
    clz[0] = 0;
    for (size_t i = 1; i < clz.size(); i++) {
      clz[i] = clz[i >> 1] + 1;
    }
    int tlg = logVal;
    while (tlg > 1) {
      onLayer[tlg] = (int)layers.size();
      layers.push_back(tlg);
      tlg = (tlg + 1) >> 1;
    }
    for (int i = logVal - 1; i >= 0; i--) {
      onLayer[i] = std::max(onLayer[i], onLayer[i + 1]);
    }
    int betweenLayers = std::max(0, (int)layers.size() - 1);
    int bSzLog = (logVal + 1) >> 1;
    int bSz = 1 << bSzLog;
    indexSz = (n + bSz - 1) >> bSzLog;
    v.resize(n + indexSz);
    pref.assign(layers.size(), std::vector<T>(n + indexSz));
    suf.assign(layers.size(), std::vector<T>(n + indexSz));
    between.assign(betweenLayers, std::vector<T>((1 << logVal) + bSz));
    build(0, 0, n, 0);
  }

  // runtime = O(beta), memory = O(1), where op calls are in O(beta). Typically beta=1.
  T query(size_t l, size_t r)
  {
    rangeCheck(l, r);
    return query(l, r, 0, 0);
  }

  // runtime = O(sqrt(n) * beta), memory = O(1), where op calls are in O(beta). Typically beta=1.
  void update(size_t idx, const T& item)
  {
    v[idx] = item;
    update(0, 0, n, 0, idx);
  }

private:
  std::vector<T> v;
  std::function<T(const T&, const T&)> op;
  int n;
  int indexSz;
  int logVal;
  std::vector<int> clz;
  std::vector<int> layers;
  std::vector<int> onLayer;
  std::vector<std::vector<T>> pref;
  std::vector<std::vector<T>> suf;
  std::vector<std::vector<T>> between;

  void rangeCheck(size_t l, size_t r) const
  {
    if (r < l) {
      throw std::out_of_range("incorrect query");
    }
    if (n <= int(r)) {
      throw std::out_of_range("incorrect query");
    }
  }

  void buildBlock(int layer, int l, int r)
  {
    pref[layer][l] = v[l];
    for (int i = l + 1; i < r; i++) {
      pref[layer][i] = op(pref[layer][i - 1], v[i]);
    }
    suf[layer][r - 1] = v[r - 1];
    for (int i = r - 2; i >= l; i--) {
      suf[layer][i] = op(v[i], suf[layer][i + 1]);
    }
  }

  void buildBetween(int layer, int lBound, int rBound, int betweenOffs)
  {
    int bSzLog = (layers[layer] + 1) >> 1;
    int bCntLog = layers[layer] >> 1;
    int bSz = 1 << bSzLog;
    int bCnt = (rBound - lBound + bSz - 1) >> bSzLog;
    for (int i = 0; i < bCnt; i++) {
      T ans;
      for (int j = i; j < bCnt; j++) {
        T add = suf[layer][lBound + (j << bSzLog)];
        ans = (i == j) ? add : op(ans, add);
        between[layer - 1][betweenOffs + lBound + (i << bCntLog) + j] = ans;
      }
    }
  }

  void buildBetweenZero()
  {
    int bSzLog = (logVal + 1) >> 1;
    for (int i = 0; i < indexSz; i++) {
      v[n + i] = suf[0][i << bSzLog];
    }
    build(1, n, n + indexSz, (1 << logVal) - n);
  }

  inline void updateBetweenZero(int bid)
  {
    int bSzLog = (logVal + 1) >> 1;
    v[n + bid] = suf[0][bid << bSzLog];
    update(1, n, n + indexSz, (1 << logVal) - n, n + bid);
  }

  void build(int layer, int lBound, int rBound, int betweenOffs)
  {
    if (layer >= (int)layers.size()) {
      return;
    }
    int bSz = 1 << ((layers[layer] + 1) >> 1);
    for (int l = lBound; l < rBound; l += bSz) {
      int r = std::min(l + bSz, rBound);
      buildBlock(layer, l, r);
      build(layer + 1, l, r, betweenOffs);
    }
    if (layer == 0) {
      buildBetweenZero();
    } else {
      buildBetween(layer, lBound, rBound, betweenOffs);
    }
  }

  void update(int layer, int lBound, int rBound, int betweenOffs, int x)
  {
    if (layer >= (int)layers.size()) {
      return;
    }
    int bSzLog = (layers[layer] + 1) >> 1;
    int bSz = 1 << bSzLog;
    int blockIdx = ((int)x - lBound) >> bSzLog;
    int l = lBound + (blockIdx << bSzLog);
    int r = std::min(l + bSz, rBound);
    buildBlock(layer, l, r);
    if (layer == 0) {
      updateBetweenZero(blockIdx);
    } else {
      buildBetween(layer, lBound, rBound, betweenOffs);
    }
    update(layer + 1, l, r, betweenOffs, x);
  }

  T query(int l, int r, int betweenOffs, int base)
  {
    if (l == r) {
      return v[l];
    }
    if (l + 1 == r) {
      return op(v[l], v[r]);
    }
    int layer = onLayer[clz[(l - base) ^ (r - base)]];
    int bSzLog = (layers[layer] + 1) >> 1;
    int bCntLog = layers[layer] >> 1;
    int lBound = (((l - base) >> layers[layer]) << layers[layer]) + base;
    int lBlock = ((l - lBound) >> bSzLog) + 1;
    int rBlock = ((r - lBound) >> bSzLog) - 1;
    T ans = suf[layer][l];
    if (lBlock <= rBlock) {
      T add = (layer == 0) ? (query(n + lBlock, n + rBlock, (1 << logVal) - n, n))
                           : (between[layer - 1][betweenOffs + lBound + (lBlock << bCntLog) + rBlock]);
      ans = op(ans, add);
    }
    ans = op(ans, pref[layer][r]);
    return ans;
  }
};

#endif  // ALGOS_DATA_STRUCTURE_SQRT_TREE_INCLUDED
