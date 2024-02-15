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
    std::vector<int> linking;
  };

  SuffixAutomaton1(std::string s)
  {
    n = s.size();
    nodes.reserve(2 * n + 1);
    nodes.push_back(Node());
    nodes[0].len = 0;
    nodes[0].link = -1;
    last = 0;
    for (char c : s) {
      extend(c);
    }
    for (int i = nodes.size() - 1; i > 0; i--) {
      const Node& cur = nodes[i];
      Node& prev = nodes[cur.link];
      prev.linking.push_back(i);
    }
  }

  const std::vector<Node>& getNodes() const { return nodes; }

private:
  int n;
  int last;
  std::vector<Node> nodes;

  void extend(char c)
  {
    int cur = nodes.size();
    nodes.push_back(Node());
    nodes[cur].len = nodes[last].len + 1;
    int p = last;
    while (p != -1 && !nodes[p].next.count(c)) {
      nodes[p].next[c] = cur;
      p = nodes[p].link;
    }
    if (p == -1) {
      nodes[cur].link = 0;
    } else {
      int q = nodes[p].next[c];
      if (nodes[p].len + 1 == nodes[q].len) {
        nodes[cur].link = q;
      } else {
        int clone = nodes.size();
        nodes.push_back(Node());
        nodes[clone].len = nodes[p].len + 1;
        nodes[clone].next = nodes[q].next;
        nodes[clone].link = nodes[q].link;
        while (p != -1 && nodes[p].next[c] == q) {
          nodes[p].next[c] = clone;
          p = nodes[p].link;
        }
        nodes[q].link = nodes[cur].link = clone;
      }
    }
    last = cur;
  }
};

#endif  // ALGOS_STRINGS_SUFFIX_AUTOMATON_1_INCLUDED
