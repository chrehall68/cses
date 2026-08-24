#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  int n;
  cin >> n;
  vector<vector<int>> g(n);
  for (int i = 0; i < n - 1; ++i) {
    int a, b;
    cin >> a >> b;
    g[--a].push_back(--b);
    g[b].push_back(a);
  }
  // initial dfs to compute sizes
  vector<int> sizes(n);
  auto dfs = [&](auto &dfs, int i, int parent) -> int {
    sizes[i] = 1;
    for (int conn : g[i]) {
      if (conn != parent) {
        sizes[i] += dfs(dfs, conn, i);
      }
    }
    return sizes[i];
  };
  dfs(dfs, 0, -1);
  // now just reroot
  int answer = -1;
  auto dfs2 = [&](auto &dfs2, int i, int parent, int parentSize) -> void {
    // check whether this node works
    bool allGood = parentSize <= n / 2;
    for (int conn : g[i]) {
      if (conn != parent) {
        allGood = allGood && sizes[conn] <= n / 2;
      }
    }
    if (allGood) {
      answer = i;
    } else {
      // check connections
      for (int conn : g[i]) {
        if (conn != parent) {
          dfs2(dfs2, conn, i, n - sizes[conn]);
        }
      }
    }
  };
  dfs2(dfs2, 0, -1, 0);
  assert(answer != -1);

  cout << (answer + 1) << endl;
}