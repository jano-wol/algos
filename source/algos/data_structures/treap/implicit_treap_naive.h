#ifndef ALGOS_DATA_STRUCTURES_IMPLICIT_TREAP_NAIVE_INCLUDED
#define ALGOS_DATA_STRUCTURES_IMPLICIT_TREAP_NAIVE_INCLUDED

#include <algorithm>
#include <vector>

template <typename T>
class ImplicitTreapNaive
{
public:
  ImplicitTreapNaive() {}

  ImplicitTreapNaive(size_t n) : data(n) {}

  ImplicitTreapNaive(std::vector<T> v) : data(std::move(v)) {}

  size_t size() { return data.size(); }

  void push_back(T val) { data.push_back(val); }

  void insert(size_t pos, T val)
  {
    if (pos >= size()) {
      throw std::out_of_range("insert pos is out of range");
    }
    data.insert(data.begin() + pos, val);
  }

  void erase(size_t pos)
  {
    if (pos >= size()) {
      throw std::out_of_range("erase pos is out of range");
    }
    data.erase(data.begin() + pos);
  }

  T& operator[](size_t pos)
  {
    if (pos >= size()) {
      throw std::out_of_range("operator[] pos is out of range");
    }
    return data[pos];
  }

private:
  std::vector<T> data;
};

#endif  // ALGOS_DATA_STRUCTURES_IMPLICIT_TREAP_INCLUDED
