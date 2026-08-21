#include <bits/stdc++.h>
using namespace std;
using ll = long long;

class Segtree {
  vector<vector<ll>> levels;
  size_t n;

public:
  Segtree(vector<ll> &vals) : n(vals.size()) {
    levels.push_back(vals);
    while (levels.back().size() > 1) {
      auto &b = levels.back();
      vector<ll> nextLevel;
      for (size_t i = 0; i < b.size(); i += 2) {
        if (i + 1 < b.size()) {
          nextLevel.push_back(b[i] + b[i + 1]);
        } else {
          nextLevel.push_back(b[i]);
        }
      }
      levels.push_back(nextLevel);
    }
  }

  void update(int idx, ll newVal) {
    ll dif = newVal - levels[0][idx];
    for (size_t level = 0; level < levels.size(); level++, idx /= 2) {
      levels[level][idx] += dif;
    }
  }

  ll sumHelper(int l, int r, size_t level, size_t levelIdx) {
    if (levelIdx >= levels[level].size()) {
      return 0;
    }
    int myL = (1 << level) * levelIdx;
    int myR = min((1 << level) * (levelIdx + 1), n) - 1;
    if (l <= myL && myR <= r) {
      return levels[level][levelIdx];
    } else if (r < myL || myR < l) {
      return 0;
    } else {
      return sumHelper(l, r, level - 1, levelIdx * 2) +
             sumHelper(l, r, level - 1, levelIdx * 2 + 1);
    }
  }
  ll sum(int l, int r) { return sumHelper(l, r, levels.size() - 1, 0); }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  // eulerian tour to flatten, then segtree for
  // point update and range sum queries
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
  auto dfs = [&](auto &&dfs, int i, int parent) -> void {
    int start = tourValues.size();
    positions[i] = start;
    tourValues.push_back(values[i]);
    for (int conn : g[i]) {
      if (conn != parent) {
        dfs(dfs, conn, i);
      }
    }
    int end = tourValues.size() - 1;
    ranges[i] = {start, end};
  };
  dfs(dfs, 0, -1);

  // then use the eulerian tour to make our segtree
  Segtree stree(tourValues);
  // and handle queries
  for (; q > 0; --q) {
    int qType;
    cin >> qType;
    if (qType == 1) {
      int node, x;
      cin >> node >> x;
      stree.update(positions[--node], x);
    } else {
      int node;
      cin >> node;
      auto [start, end] = ranges[--node];
      cout << stree.sum(start, end) << '\n';
    }
  }
}