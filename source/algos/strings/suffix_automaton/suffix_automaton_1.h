#ifndef ALGOS_STRINGS_SUFFIX_AUTOMATON_1_INCLUDED
#define ALGOS_STRINGS_SUFFIX_AUTOMATON_1_INCLUDED

#include <map>
#include <string>

class SuffixAutomaton1
{
public:
  struct Node
  {
    int len;
    int link;
    std::map<char, int> next;
  };

  std::vector<Node> data;

  SuffixAutomaton1(std::string s)
  {
    n = s.size();
    data.reserve(2 * n + 1);
    data.push_back(Node());
    data[0].len = 0;
    data[0].link = -1;
    last = 0;
    for (char c : s) {
      extend(c);
    }
  }

private:
  int n;
  int last;

  void extend(char c)
  {
    int cur = data.size();
    data.push_back(Node());
    data[cur].len = data[last].len + 1;
    int p = last;
    while (p != -1 && !data[p].next.count(c)) {
      data[p].next[c] = cur;
      p = data[p].link;
    }
    if (p == -1) {
      data[cur].link = 0;
    } else {
      int q = data[p].next[c];
      if (data[p].len + 1 == data[q].len) {
        data[cur].link = q;
      } else {
        int clone = data.size();
        data.push_back(Node());
        data[clone].len = data[p].len + 1;
        data[clone].next = data[q].next;
        data[clone].link = data[q].link;
        while (p != -1 && data[p].next[c] == q) {
          data[p].next[c] = clone;
          p = data[p].link;
        }
        data[q].link = data[cur].link = clone;
      }
    }
    last = cur;
  }
};

#endif  // ALGOS_STRINGS_SUFFIX_AUTOMATON_1_INCLUDED
