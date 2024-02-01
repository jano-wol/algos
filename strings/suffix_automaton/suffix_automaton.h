#ifndef ALGOS_STRINGS_SUFFIX_AUTOMATON_INCLUDED
#define ALGOS_STRINGS_SUFFIX_AUTOMATON_INCLUDED

#include <map>
#include <string>

namespace SuffixAutomaton
{
struct State
{
  int len;
  int link;
  std::map<char, int> next;
};

const int MAXLEN = 100005;
State st[MAXLEN * 2];
int sz;
int last;

void init()
{
  st[0].len = 0;
  st[0].link = -1;
  sz++;
  last = 0;
}

void extend(char c)
{
  int cur = sz++;
  st[cur].len = st[last].len + 1;
  int p = last;
  while (p != -1 && !st[p].next.count(c)) {
    st[p].next[c] = cur;
    p = st[p].link;
  }
  if (p == -1) {
    st[cur].link = 0;
  } else {
    int q = st[p].next[c];
    if (st[p].len + 1 == st[q].len) {
      st[cur].link = q;
    } else {
      int clone = sz++;
      st[clone].len = st[p].len + 1;
      st[clone].next = st[q].next;
      st[clone].link = st[q].link;
      while (p != -1 && st[p].next[c] == q) {
        st[p].next[c] = clone;
        p = st[p].link;
      }
      st[q].link = st[cur].link = clone;
    }
  }
  last = cur;
}
};  // namespace SuffixAutomaton

#endif  // ALGOS_STRINGS_SUFFIX_AUTOMATON_INCLUDED