#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct PersistentSegtree {
  struct Node;
  vector<Node *> nodes;

  struct Node {
    ll sum;
    int myL, myR;
    Node *l, *r;
    PersistentSegtree *p;

    Node(ll v, int l, int r, PersistentSegtree *p)
        : sum(v), myL(l), myR(r), l(nullptr), r(nullptr), p(p) {
      p->nodes.push_back(this);
    }
    Node(Node *l, Node *r, PersistentSegtree *p)
        : sum(l->sum), myL(l->myL), myR(l->myR), l(l), r(r), p(p) {
      if (r != nullptr) {
        sum += r->sum;
        myR = r->myR;
      }
      p->nodes.push_back(this);
    }

    // l and r will be freed by the PSegtree
    ~Node() {
      p = nullptr;
      l = nullptr;
      r = nullptr;
    }
    ll query(int l, int r) {
      if (l <= myL && myR <= r) {
        return sum;
      } else if (myR < l || r < myL) {
        return 0;
      } else {
        ll res = this->l->query(l, r);
        if (this->r != nullptr) {
          res += this->r->query(l, r);
        }
        return res;
      }
    }
    Node *update(int idx, ll val) {
      if (myL == idx && myR == idx) {
        return new Node(val, myL, myR, p);
      } else {
        assert(myL <= idx && idx <= myR);
        if (l->myR < idx) {
          // go right
          return new Node(l, r->update(idx, val), p);
        } else {
          // go left
          return new Node(l->update(idx, val), r, p);
        }
      }
    }
  };

  ~PersistentSegtree() {
    for (size_t i = 0; i < nodes.size(); ++i) {
      delete nodes[i];
      nodes[i] = nullptr;
    }
  }
  PersistentSegtree() = default;
  Node *build(vector<ll> init) {
    vector<Node *> prev;
    for (size_t i = 0; i < init.size(); ++i) {
      prev.push_back(new Node(init[i], i, i, this));
    }
    while (prev.size() > 1) {
      vector<Node *> cur;
      for (size_t i = 0; i < prev.size(); i += 2) {
        if (i + 1 < prev.size()) {
          cur.push_back(new Node(prev[i], prev[i + 1], this));
        } else {
          cur.push_back(new Node(prev[i], nullptr, this));
        }
      }
      prev = cur;
    }
    return prev[0];
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int n, q;
  cin >> n >> q;
  vector<ll> nums(n);
  for (int i = 0; i < n; ++i) {
    cin >> nums[i];
  }
  PersistentSegtree p;
  vector<PersistentSegtree::Node *> roots;
  roots.push_back(p.build(nums));
  for (int i = 0; i < q; ++i) {
    int op;
    cin >> op;
    if (op == 1) {
      int k, a, x;
      cin >> k >> a >> x;
      k--;
      roots[k] = roots[k]->update(--a, x);
    } else if (op == 2) {
      int k, a, b;
      cin >> k >> a >> b;
      cout << roots[--k]->query(--a, --b) << '\n';
    } else {
      int k;
      cin >> k;
      roots.push_back(roots[--k]);
    }
  }
  // so that we won't have dangling pointers
  roots.clear();
}