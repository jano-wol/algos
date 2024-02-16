#ifndef ALGOS_STRINGS_SUFFIX_AUTOMATON_2_INCLUDED
#define ALGOS_STRINGS_SUFFIX_AUTOMATON_2_INCLUDED

#include <map>
#include <string>
#include <vector>

class SuffixAutomaton2
{
public:
  struct Node
  {
    int len = 0;
    std::map<char, Node*> next;
    Node* link = 0;
    std::vector<Node*> linking;
    bool leaf = false;
  };

  // runtime = O(n), memory = O(n), where n = |s|.
  SuffixAutomaton2(std::string s)
  {
    n = s.size();

    nodes.reserve(2 * n + 1);
    nodes.push_back(Node());

    Node* last = &nodes.back();
    last->len = 0, last->link = 0;

    for (int ind = 0; ind < n; ind++) {
      char c = s[ind];

      nodes.push_back(Node());
      Node *prev = last->link, *cur = &nodes.back();
      cur->len = ind + 1;
      last->next[c] = cur;

      while (prev != 0) {
        if (prev->next.count(c))
          break;
        prev->next[c] = cur;
        prev = prev->link;
      }

      if (prev == 0)
        cur->link = &nodes[0];
      else {
        Node* next = prev->next[c];

        if (next->len == prev->len + 1)
          cur->link = prev->next[c];
        else {
          nodes.push_back(Node());
          Node* added = &nodes.back();

          added->len = prev->len + 1;
          added->next = next->next;
          added->link = next->link;

          cur->link = added;
          next->link = added;

          while (prev != 0 && prev->next[c] == next) {
            prev->next[c] = added;
            prev = prev->link;
          }
        }
      }

      last = cur;
      last->leaf = true;
    }

    // And now initialize the tree nodes
    for (int i = nodes.size() - 1; i > 0; i--) {
      Node *cur = &nodes[i], *prev = cur->link;
      prev->linking.push_back(cur);
    }
  }

  const std::vector<Node>& getNodes() const { return nodes; }

private:
  int n;
  std::vector<Node> nodes;
};

#endif  // ALGOS_STRINGS_SUFFIX_AUTOMATON_2_INCLUDED
