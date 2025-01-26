#ifndef ALGOS_DATA_STRUCTURES_LINK_CUT_TREE_INCLUDED
#define ALGOS_DATA_STRUCTURES_LINK_CUT_TREE_INCLUDED

#include <algorithm>
#include <vector>

class LinkCutTree
{
public:
  // runtime = O(n), memory = O(n).
  LinkCutTree(int n) : node(n) {}

  // runtime = O(log n), memory = O(1).
  void link(int u, int v)
  {
    makeRoot(&node[u]);
    node[u].pp = &node[v];
  }

  // runtime = O(log n), memory = O(1).
  void cut(int u, int v)
  {
    Node *x = &node[u], *top = &node[v];
    makeRoot(top);
    x->splay();
    if (x->pp)
      x->pp = 0;
    else {
      x->c[0] = top->p = 0;
      x->fix();
    }
  }

  // runtime = O(log n), memory = O(1).
  bool connected(int u, int v)
  {
    Node* nu = access(&node[u])->first();
    return nu == access(&node[v])->first();
  }

private:
  struct Node
  {
    Node *p = 0, *pp = 0, *c[2];
    bool flip = 0;
    Node()
    {
      c[0] = c[1] = 0;
      fix();
    }
    void fix()
    {
      if (c[0])
        c[0]->p = this;
      if (c[1])
        c[1]->p = this;
    }
    void pushFlip()
    {
      if (!flip)
        return;
      flip = 0;
      std::swap(c[0], c[1]);
      if (c[0])
        c[0]->flip ^= 1;
      if (c[1])
        c[1]->flip ^= 1;
    }
    int up() { return p ? p->c[1] == this : -1; }
    void rot(int i, int b)
    {
      int h = i ^ b;
      Node *x = c[i], *y = b == 2 ? x : x->c[h], *z = b ? y : x;
      if ((y->p = p))
        p->c[up()] = y;
      c[i] = z->c[i ^ 1];
      if (b < 2) {
        x->c[h] = y->c[h ^ 1];
        y->c[h ^ 1] = x;
      }
      z->c[i ^ 1] = this;
      fix();
      x->fix();
      y->fix();
      if (p)
        p->fix();
      std::swap(pp, y->pp);
    }
    void splay()
    {
      for (pushFlip(); p;) {
        if (p->p)
          p->p->pushFlip();
        p->pushFlip();
        pushFlip();
        int c1 = up(), c2 = p->up();
        if (c2 == -1)
          p->rot(c1, 2);
        else
          p->p->rot(c2, c1 != c2);
      }
    }
    Node* first()
    {
      pushFlip();
      return c[0] ? c[0]->first() : (splay(), this);
    }
  };

  void makeRoot(Node* u)
  {
    access(u);
    u->splay();
    if (u->c[0]) {
      u->c[0]->p = 0;
      u->c[0]->flip ^= 1;
      u->c[0]->pp = u;
      u->c[0] = 0;
      u->fix();
    }
  }
  Node* access(Node* u)
  {
    u->splay();
    while (Node* pp = u->pp) {
      pp->splay();
      u->pp = 0;
      if (pp->c[1]) {
        pp->c[1]->p = 0;
        pp->c[1]->pp = pp;
      }
      pp->c[1] = u;
      pp->fix();
      u = pp;
    }
    return u;
  }

  std::vector<Node> node;
};

#endif  // ALGOS_DATA_STRUCTURES_LINK_CUT_TREE_INCLUDED
