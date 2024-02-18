#ifndef ALGOS_DATA_STRUCTURES_MINIMUM_STACK_INCLUDED
#define ALGOS_DATA_STRUCTURES_MINIMUM_STACK_INCLUDED

#include <stack>

template <typename T>
class MinimumStack
{
public:
  void push(T v)
  {
    T newMin = stack.empty() ? v : std::min(v, stack.top().second);
    stack.push({v, newMin});
  };

  void pop()
  {
    if (stack.empty()) {
      throw std::overflow_error("stack is empty");
    }
    return stack.pop();
  };

  T getMinimum() const
  {
    if (stack.empty()) {
      throw std::overflow_error("stack is empty");
    }
    return stack.top().second;
  };

  T top() const
  {
    if (stack.empty()) {
      throw std::overflow_error("stack is empty");
    }
    return stack.top().first;
  };

  bool empty() const { return stack.empty(); };
  size_t size() const { return stack.size(); };

private:
  std::stack<std::pair<T, T>> stack;
};

#endif  // ALGOS_DATA_STRUCTURES_MINIMUM_STACK_INCLUDED
