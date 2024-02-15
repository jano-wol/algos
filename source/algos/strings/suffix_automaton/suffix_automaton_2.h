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

  std::vector<Node> data;

  SuffixAutomaton2(std::string s)
  {
    n = s.size();

    data.reserve(2 * n + 1);
    data.push_back(Node());

    Node* last = &data.back();
    last->len = 0, last->link = 0;

    for (int ind = 0; ind < n; ind++) {
      char c = s[ind];

      data.push_back(Node());
      Node *prev = last->link, *cur = &data.back();
      cur->len = ind + 1;
      last->next[c] = cur;

      while (prev != 0) {
        if (prev->next.count(c))
          break;
        prev->next[c] = cur;
        prev = prev->link;
      }

      if (prev == 0)
        cur->link = &data[0];
      else {
        Node* next = prev->next[c];

        if (next->len == prev->len + 1)
          cur->link = prev->next[c];
        else {
          data.push_back(Node());
          Node* added = &data.back();

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

    // And now initialize the tree data
    for (int i = data.size() - 1; i > 0; i--) {
      Node *cur = &data[i], *prev = cur->link;
      prev->linking.push_back(cur);
    }
  }

private:
  int n;
};

#endif  // ALGOS_STRINGS_SUFFIX_AUTOMATON_2_INCLUDED
