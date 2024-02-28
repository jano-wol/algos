#ifndef ALGOS_DATA_STRUCTURES_I_MO_OBJECT_INCLUDED
#define ALGOS_DATA_STRUCTURES_I_MO_OBJECT_INCLUDED

#include <iostream>
#include <optional>
#include <vector>

class IMoObject
{
public:
  virtual void add(size_t idx) = 0;
  virtual void remove(size_t idx) = 0;
  virtual int solve() const = 0;
};

#endif  // ALGOS_DATA_STRUCTURES_I_MO_OBJECT_INCLUDED
