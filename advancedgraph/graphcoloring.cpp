#include <bits/stdc++.h>
using namespace std;

int main() {
  // we know greedy coloring is not always optimal
  // but we also know there always exists an order
  // such that greedy coloring yields the optimal value
  // so brute force = try running greedy graph coloring
  // on all n! orderings
  // I'd like to just be able to say that maybe we can choose
  // an ordering similar to elevator rides where we know
  // some node must be last
  // but a node being last isn't all that we need; we need
  // actually all of the nodes
  // or at least like the colors of the nodes that I have edges to
  // ===========
  // another alternative is to just, if we're coloring with k colors,
  // choose a color 1-k for a node
  // this is k**n
  // ===========
  // suppose I know how to optimally color some set of nodes
  // can I expand this?
  // maybe we can do like dividing it into independent sets
  // we can calculate whether a set is possible as an independent set
  // and then combine those sets minimally with brute force enumeration
  // 2**16 * 16 * 16 + 3**16
  int n, m;
  cin >> n >> m;
  vector<vector<int>> g(n);
  for (int i = 0; i < m; ++i) {
    int a, b;
    cin >> a >> b;
    g[--a].push_back(--b);
    g[b].push_back(a);
  }
  const int LIMIT = 1 << n;
  vector<bool> isIndependent(LIMIT);
  for (int subset = 0; subset < LIMIT; ++subset) {
    bool independent = true;
    for (int node = 0; node < n; ++node) {
      if (subset & (1 << node)) {
        for (int conn : g[node]) {
          independent = independent && !(subset & (1 << conn));
        }
      }
    }
    isIndependent[subset] = independent;
  }
  // then just combine those
  vector<int> minColorsFor(LIMIT, n + 1);
  vector<int> parents(LIMIT, -1);
  for (int subset = 0; subset < LIMIT; ++subset) {
    if (isIndependent[subset]) {
      minColorsFor[subset] = 1;
      continue;
    }
    for (int combineA = subset - 1; combineA > 0;
         combineA = (combineA - 1) & subset) {
      int combineB = subset ^ combineA;
      int nextColors = minColorsFor[combineA] + minColorsFor[combineB];
      if (nextColors < minColorsFor[subset]) {
        parents[subset] = combineA;
        minColorsFor[subset] = nextColors;
      }
    }
  }
  // retrace
  vector<int> colors(n);
  int color = 0;
  auto rec = [&](auto &rec, int subset) -> void {
    if (isIndependent[subset]) {
      for (int node = 0; node < n; ++node) {
        if (subset & (1 << node)) {
          colors[node] = color;
        }
      }
      color++;
      return;
    }
    // color subparts
    int p1 = parents[subset];
    rec(rec, p1);
    rec(rec, subset ^ p1);
  };
  rec(rec, LIMIT - 1);
  cout << minColorsFor[LIMIT - 1] << endl;
  for (int color : colors) {
    cout << color + 1 << ' ';
  }
  cout << endl;
}
