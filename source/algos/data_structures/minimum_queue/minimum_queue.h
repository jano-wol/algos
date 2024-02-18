#ifndef ALGOS_DATA_STRUCTURES_MINIMUM_QUEUE_INCLUDED
#define ALGOS_DATA_STRUCTURES_MINIMUM_QUEUE_INCLUDED

#include "./../minimum_stack/minimum_stack.h"

template <typename T>
class MinimumQueue
{
public:
  void push(T v) { back.push(v); };

  void pop()
  {
    if (empty()) {
      throw std::overflow_error("queue is empty");
    }
    if (!front.empty()) {
      front.pop();
    } else {
      while (!back.empty()) {
        T val = back.top();
        front.push(val);
      }
      front.pop();
    }
  };

  T getMinimum() const
  {
    if (empty()) {
      throw std::overflow_error("queue is empty");
    }
    if (back.empty()) {
      return front.getMinimum();
    }
    if (front.empty()) {
      return back.getMinimum();
    }
    return std::min(front.getMinimum(), back.getMinimum());
  };

  T front()
  {
    if (empty()) {
      throw std::overflow_error("queue is empty");
    }
    if (!front.empty()) {
      front.top();
    } else {
      while (!back.empty()) {
        T val = back.top();
        front.push(val);
      }
      front.top();
    }
  };

  bool empty() const { return (front.empty() && back.empty()); };
  size_t size() const { return front.size() + back.size(); };

private:
  MinimumStack front;
  MinimumStack back;
};

#endif  // ALGOS_DATA_STRUCTURES_MINIMUM_QUEUE_INCLUDED
