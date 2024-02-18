#ifndef ALGOS_DATA_STRUCTURES_MINIMUM_QUEUE_INCLUDED
#define ALGOS_DATA_STRUCTURES_MINIMUM_QUEUE_INCLUDED

#include "./../minimum_stack/minimum_stack.h"

template <typename T>
class MinimumQueue
{
public:
  // runtime = O(1), memory = O(1).
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

  void push(T v) { back.push(v); }

  // runtime average during storage lifetime = O(1), memory = O(1).
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
        back.pop();
      }
      front.pop();
    }
  }

  // runtime average during storage lifetime = O(1), memory = O(1).
  T top()
  {
    if (empty()) {
      throw std::overflow_error("queue is empty");
    }
    if (!front.empty()) {
      return front.top();
    } else {
      while (!back.empty()) {
        T val = back.top();
        front.push(val);
        back.pop();
      }
    }
    return front.top();
  }

  bool empty() const { return (front.empty() && back.empty()); }
  size_t size() const { return front.size() + back.size(); }

private:
  MinimumStack<T> front;
  MinimumStack<T> back;
};

#endif  // ALGOS_DATA_STRUCTURES_MINIMUM_QUEUE_INCLUDED
