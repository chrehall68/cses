#include <bits/stdc++.h>
using namespace std;
using ll = long long;
struct PersistentSegtree {
  struct Node;
  vector<Node *> nodes;
  struct Node {
    ll sum, mi, ma;
    int myL, myR;
    Node *l, *r;
    PersistentSegtree *p;

    Node(ll s, ll v, int idx, PersistentSegtree *p)
        : sum(s), mi(v), ma(v), myL(idx), myR(idx), l(nullptr), r(nullptr),
          p(p) {
      p->nodes.push_back(this);
    }
    Node(Node *l, Node *r)
        : sum(l->sum), mi(l->mi), ma(l->ma), myL(l->myL), myR(l->myR), l(l),
          r(r), p(l->p) {
      if (r != nullptr) {
        sum += r->sum;
        ma = max(ma, r->ma);
        mi = min(mi, r->mi);
        myR = r->myR;
      }
      p->nodes.push_back(this);
    }
    ~Node() {
      p = nullptr;
      l = nullptr;
      r = nullptr;
    }

    Node *inc(int idx, ll v) {
      if (myL == myR && myL == idx) {
        return new Node(sum + v, v, idx, p);
      } else {
        if (l->myR < idx) {
          return new Node(l, r->inc(idx, v));
        } else {
          return new Node(l->inc(idx, v), r);
        }
      }
    }
  };

  PersistentSegtree() = default;
  ~PersistentSegtree() {
    for (size_t i = 0; i < nodes.size(); ++i) {
      delete nodes[i];
      nodes[i] = nullptr;
    }
  }

  Node *build(vector<ll> init) {
    vector<Node *> prev;
    for (size_t i = 0; i < init.size(); ++i) {
      prev.push_back(new Node(0, init[i], i, this));
    }
    while (prev.size() > 1) {
      vector<Node *> cur;
      for (size_t i = 0; i < prev.size(); i += 2) {
        if (i + 1 < prev.size()) {
          cur.push_back(new Node(prev[i], prev[i + 1]));
        } else {
          cur.push_back(prev[i]);
        }
      }
      prev = cur;
    }
    return prev[0];
  }
};
int main() {
  // so maybe we could store the mex?
  // well once we can make all numbers up to x-1, then
  // we can use number x to increase the mex by x
  // prev mex = 0, cur num = 1 -> new mex = 1
  // prev mex = 1, cur num = 2 -> new mex = 3
  // prev mex = 3, cur num = 2 -> new mex = 5
  // so the mex would just be the sum of the numbers
  // but we have to be able to add the numbers
  // if the numbers were in sorted order, then we would know for sure that
  // if we can't add number a, we can't add any other numbers
  // but the problem with sorted order is how would we enable/disable things
  // so maybe we do need to have them in the original order
  // but then we want to be able to get the numbers in order
  // so maybe we have merge tree
  // and then just handle it increasing (it can only increase lg(MEX) times)
  // since each time we need to check if it increases, the cur mex
  // either stays the same (it's finished), or it at least doubles
  // and each time we just need to calculate the sum of everything <= MEX
  // the problem is, that gives us O(NlgN + Q (lg**2(N)) lg MEX)
  // which is O(NlgN + Q lg**3 (N))
  // that will TLE, though since Q lg**3 (N) is a lot
  // to improve that, instead of handling online and then bsearching over
  // lgN intervals lgMEX times, maybe we can handle the queries offline
  // we can add things in sorted order
  // and then do their queries when the next element that we would've
  // enabled is greater than next mex
  // since then we need to do O(lgMEX) segtree queries for each query
  // and we need to keep the queries in order
  // and our segtree just needs the sums now, making queries faster
  // so we get O(NlgN + Q lgQ lgMEX + Q lgMEX lgN)
  // if we instead used a persistent segtree
  // we could still have that time complexity by having the persistent
  // segtree be on the sorted numbers, and the roots be the root
  // after inserting the first i numbers
  // because then the amount of numbers <= X is just sum(...upper bound of X)
  // and we can get that sum in lgN time, and get the upper bound of X in lgN
  // time and we would increase our mex lgMEX times
  // maybe if we had a persistent array on the sum
  // and the min in the intervals intervals [1], [2,3], [4,5,6,7], [8..15], ...
  // then we would just need to go through each of those intervals and total
  // up their sum so long as their minimum element <= curSum + 1
  // but that means we need the minimum element, which isn't easily reversible
  // maybe we do use the segtree built on the sorted things
  // goal = do that same logic, but on the persistent segtree
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int n, q;
  cin >> n >> q;
  // don't store multiple nodes for duplicates of the number
  vector<ll> orig(n), sortedDistinct;
  vector<int> toSortedIdx(n), indices(n);
  iota(indices.begin(), indices.end(), 0);
  for (int i = 0; i < n; ++i) {
    ll num;
    cin >> num;
    orig[i] = num;
  }
  sort(indices.begin(), indices.end(),
       [&](int a, int b) { return orig[a] < orig[b]; });
  for (int l = 0, sIdx = 0; l < n; sIdx++) {
    int r = l + 1;
    while (r < n && orig[indices[l]] == orig[indices[r]]) {
      r++;
    }
    sortedDistinct.push_back(orig[indices[l]]);
    while (l < r) {
      toSortedIdx[indices[l++]] = sIdx;
    }
  }
  // roots[i] = root after adding first i elements
  PersistentSegtree s;
  vector<PersistentSegtree::Node *> roots(n + 1);
  roots[0] = s.build(sortedDistinct);
  for (int i = 0; i < n; ++i) {
    roots[i + 1] = roots[i]->inc(toSortedIdx[i], orig[i]);
  }
  // then now process queries
  auto dfs = [](auto &&self, PersistentSegtree::Node *lNode,
                PersistentSegtree::Node *rNode, ll curMex) {
    assert(lNode->mi == rNode->mi && lNode->ma == rNode->ma);
    if (lNode->mi > curMex + 1) {
      return curMex;
    } else if (lNode->ma <= curMex + 1) {
      // then the sums of the interval are encoded as difference in sums between
      // rNode and lNode
      return curMex + rNode->sum - lNode->sum;
    } else {
      // split to children
      ll nextMex = self(self, lNode->l, rNode->l, curMex);
      if (lNode->r != nullptr) {
        nextMex = self(self, lNode->r, rNode->r, nextMex);
      }
      return nextMex;
    }
  };
  for (int i = 0; i < q; ++i) {
    int l, r;
    cin >> l >> r;
    PersistentSegtree::Node *lNode = roots[--l], *rNode = roots[r];
    ll mex = dfs(dfs, lNode, rNode, 0);
    cout << mex + 1 << '\n';
  }
}