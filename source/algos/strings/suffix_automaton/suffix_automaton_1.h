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
    bool leaf;
    std::map<char, int> next;
    std::vector<int> linking;
  };

  // runtime = O(n), memory = O(n), where n = |s|.
  SuffixAutomaton1(std::string s)
  {
    n = s.size();
    str = s;
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

  // runtime = O(n), memory = O(n), where n = |str|.
  std::vector<int> getEndPoses(int nodeIdx) const
  {
    std::vector<bool> all(n + 1);
    std::vector<int> ret;
    ret.reserve(n + 1);
    for (auto nextIdx : nodes[nodeIdx].linking) {
      getEndPosesDfs(nextIdx, all);
    }
    if (nodes[nodeIdx].leaf) {
      all[nodes[nodeIdx].len - 1] = true;
    }
    for (size_t i = 0; i < size_t(n + 1); ++i) {
      if (all[i] == true) {
        ret.push_back(i);
      }
    }
    return ret;
  }

  // runtime = O(n), memory = O(n), where n = |str|.
  std::pair<std::string, std::string> getStringInterval(int nodeIdx) const
  {
    if (nodeIdx == 0) {
      return {};
    }
    auto endPoses = getEndPoses(nodeIdx);
    auto high = str.substr(endPoses[0] + 1 - nodes.at(nodeIdx).len, nodes.at(nodeIdx).len);
    size_t lenLow = nodes.at(nodes.at(nodeIdx).link).len + 1;
    auto low = str.substr(endPoses[0] + 1 - lenLow, lenLow);
    return {high, low};
  }

  const std::vector<Node>& getNodes() const { return nodes; }

private:
  int n;
  int last;
  std::string str;
  std::vector<Node> nodes;

  void extend(char c)
  {
    int cur = nodes.size();
    nodes.push_back(Node());
    nodes[cur].len = nodes[last].len + 1;
    nodes[cur].leaf = true;
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
        nodes[clone].leaf = false;
        while (p != -1 && nodes[p].next[c] == q) {
          nodes[p].next[c] = clone;
          p = nodes[p].link;
        }
        nodes[q].link = nodes[cur].link = clone;
      }
    }
    last = cur;
  }

  void getEndPosesDfs(size_t nodeIdx, std::vector<bool>& all) const
  {
    for (auto nextIdx : nodes[nodeIdx].linking) {
      getEndPosesDfs(nextIdx, all);
    }
    if (nodes[nodeIdx].leaf) {
      all[nodes[nodeIdx].len - 1] = true;
    }
  }
};

#endif  // ALGOS_STRINGS_SUFFIX_AUTOMATON_1_INCLUDED
