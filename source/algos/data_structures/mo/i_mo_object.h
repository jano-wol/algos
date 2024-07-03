#ifndef ALGOS_DATA_STRUCTURES_I_MO_OBJECT_INCLUDED
#define ALGOS_DATA_STRUCTURES_I_MO_OBJECT_INCLUDED

#include <iostream>
#include <optional>
#include <vector>

template <typename R>
class IMoObject
{
public:
  virtual ~IMoObject() = default;
  virtual void add(size_t idx) = 0;
  virtual void remove(size_t idx) = 0;
  virtual R solve() const = 0;
  virtual size_t getN() const = 0;
};

#endif  // ALGOS_DATA_STRUCTURES_I_MO_OBJECT_INCLUDED
