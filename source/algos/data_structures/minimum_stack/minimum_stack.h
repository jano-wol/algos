#ifndef ALGOS_DATA_STRUCTURES_MINIMUM_STACK_INCLUDED
#define ALGOS_DATA_STRUCTURES_MINIMUM_STACK_INCLUDED

#include <stack>

template <typename T>
class MinimumStack
{
public:
  // runtime = O(1), memory = O(1).
  T getMinimum() const
  {
    if (empty()) {
      throw std::overflow_error("stack is empty");
    }
    return stack.top().second;
  }

  void push(T v)
  {
    T newMin = empty() ? v : std::min(v, stack.top().second);
    stack.push({v, newMin});
  }

  void pop()
  {
    if (empty()) {
      throw std::overflow_error("stack is empty");
    }
    return stack.pop();
  }

  T top() const
  {
    if (empty()) {
      throw std::overflow_error("stack is empty");
    }
    return stack.top().first;
  }

  bool empty() const { return stack.empty(); }
  size_t size() const { return stack.size(); }

private:
  std::stack<std::pair<T, T>> stack;
};

#endif  // ALGOS_DATA_STRUCTURES_MINIMUM_STACK_INCLUDED
