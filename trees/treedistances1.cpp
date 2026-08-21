#include <bits/stdc++.h>
using namespace std;

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
  // dfs to compute subtree heights
  // maxSubtreeHeights = {max, secondMax}
  vector<pair<int, int>> maxSubtreeHeights(n);
  auto dfs = [&](auto &dfs, int i, int parent) -> void {
    int m1 = -1, m2 = -1;
    for (int conn : g[i]) {
      if (conn != parent) {
        dfs(dfs, conn, i);
        if (maxSubtreeHeights[conn].first > m1) {
          m2 = m1;
          m1 = maxSubtreeHeights[conn].first;
        } else if (maxSubtreeHeights[conn].first > m2) {
          m2 = maxSubtreeHeights[conn].first;
        }
      }
    }
    maxSubtreeHeights[i] = {m1 + 1, m2 + 1};
  };
  dfs(dfs, 0, -1);
  // then dfs again to fill in the answer
  vector<int> result(n);
  auto dfs2 = [&](auto &dfs2, int i, int parent, int parentDist) -> void {
    result[i] = max(parentDist, maxSubtreeHeights[i].first);
    // then fill in children
    for (int conn : g[i]) {
      if (conn != parent) {
        int nextParentDist = parentDist;
        if (maxSubtreeHeights[conn].first + 1 != maxSubtreeHeights[i].first) {
          nextParentDist = max(nextParentDist, maxSubtreeHeights[i].first);
        } else {
          nextParentDist = max(nextParentDist, maxSubtreeHeights[i].second);
        }
        dfs2(dfs2, conn, i, nextParentDist + 1);
      }
    }
  };
  dfs2(dfs2, 0, -1, 0);
  for (int res : result) {
    cout << res << ' ';
  }
  cout << endl;
}