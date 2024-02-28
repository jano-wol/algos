#ifndef ALGOS_DATA_STRUCTURES_MO_OBJECT_SUM_INCLUDED
#define ALGOS_DATA_STRUCTURES_MO_OBJECT_SUM_INCLUDED

#include <iostream>
#include <optional>
#include <vector>

#include "i_mo_object.h"

template <typename T, typename R>
class MoObjectSum : public IMoObject<R>
{
public:
  MoObjectSum(std::vector<T> base_) : sum(0), base(std::move(base_)) {}

  void add(size_t idx) override { sum += base[idx]; };
  void remove(size_t idx) override { sum -= base[idx]; };
  R solve() const override { return sum; };

private:
  R sum;
  std::vector<T> base;
};

#endif  // ALGOS_DATA_STRUCTURES_MO_OBJECT_SUM_INCLUDED
