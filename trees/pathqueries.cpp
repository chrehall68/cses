
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

class Segtree {
  size_t n;
  vector<ll> initialVals;
  vector<vector<ll>> levels; // stores increments

public:
  Segtree(vector<ll> &vals) : n(vals.size()), initialVals(vals) {
    levels.push_back(vector<ll>(n, 0));
    while (levels.back().size() > 1) {
      levels.push_back(vector<ll>((levels.back().size() + 1) / 2, 0));
    }
  }

  void updateHelper(int l, int r, ll inc, size_t level, size_t levelIdx) {
    if (levelIdx >= levels[level].size()) {
      return;
    }
    int myL = (1 << level) * levelIdx;
    int myR = min((1 << level) * (levelIdx + 1), n) - 1;
    if (l <= myL && myR <= r) {
      levels[level][levelIdx] += inc;
    } else if (r < myL || myR < l) {
      return;
    } else {
      updateHelper(l, r, inc, level - 1, levelIdx * 2);
      updateHelper(l, r, inc, level - 1, levelIdx * 2 + 1);
    }
  }
  void update(int l, int r, ll inc) {
    updateHelper(l, r, inc, levels.size() - 1, 0);
  }

  ll valOf(int idx) {
    ll inc = initialVals[idx];
    for (size_t level = 0; level < levels.size(); ++level, idx /= 2) {
      inc += levels[level][idx];
    }
    return inc;
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  // this problem simply requires reframing "the sum of values on the path from
  // the root to node s" as "the sum of all values from the root to s", plus any
  // changes that happened in the parents (where we can get alerted of those
  // changes by incrementing parent's subtree) thus, we need eulerian tour to
  // flatten, then segtree for point query and range increment
  int n, q;
  cin >> n >> q;
  vector<vector<int>> g(n);
  vector<ll> values(n);
  for (ll &val : values) {
    cin >> val;
  }
  for (int i = 0; i < n - 1; ++i) {
    int a, b;
    cin >> a >> b;
    g[--a].push_back(--b);
    g[b].push_back(a);
  }
  vector<ll> tourValues;
  vector<int> positions(n);
  vector<pair<int, int>> ranges(n);
  auto dfs = [&](auto &&dfs, int i, int parent, ll parentSum) -> void {
    int start = tourValues.size();
    positions[i] = start;
    parentSum += values[i];
    tourValues.push_back(parentSum);
    for (int conn : g[i]) {
      if (conn != parent) {
        dfs(dfs, conn, i, parentSum);
      }
    }
    int end = tourValues.size() - 1;
    ranges[i] = {start, end};
  };
  dfs(dfs, 0, -1, 0);

  // then use the eulerian tour to make our segtree
  Segtree stree(tourValues);
  // and handle queries
  for (; q > 0; --q) {
    int qType;
    cin >> qType;
    if (qType == 1) {
      int node, newVal;
      cin >> node >> newVal;
      ll inc = newVal - values[--node];
      values[node] = newVal;
      auto [start, end] = ranges[node];
      stree.update(start, end, inc);
    } else {
      int node;
      cin >> node;
      cout << stree.valOf(positions[--node]) << '\n';
    }
  }
}