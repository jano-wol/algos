#ifndef ALGOS_DATA_STRUCTURES_MO_OBJECT_SUM_INCLUDED
#define ALGOS_DATA_STRUCTURES_MO_OBJECT_SUM_INCLUDED

#include <iostream>
#include <optional>
#include <vector>

#include "i_mo_object.h"

class MoObjectSum : public IMoObject
{
public:
  MoObjectSum(std::vector<int> base_) : sum(0), base(std::move(base_)) {}

  void add(size_t idx) override { sum += base[idx]; };
  void remove(size_t idx) override { sum -= base[idx]; };
  int solve() const override { return sum; };

private:
  int sum;
  std::vector<int> base;
};

#endif  // ALGOS_DATA_STRUCTURES_MO_OBJECT_SUM_INCLUDED
