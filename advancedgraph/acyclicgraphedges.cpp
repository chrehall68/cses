#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);
  int n, m;
  cin >> n >> m;
  // uEdges[from][to] = cnt
  vector<map<int, int>> uEdges(n);
  for (int i = 0; i < m; ++i) {
    int a, b;
    cin >> a >> b;
    uEdges[--a][--b]++;
    uEdges[b][a]++;
  }
  vector<vector<int>> directEdges(n);
  vector<bool> explored(n), exploring(n);
  int total = 0;
  auto dfs = [&](auto &dfs, int i) {
    exploring[i] = true;
    while (!uEdges[i].empty()) {
      auto first = uEdges[i].begin();
      uEdges[i].erase(first);
      auto [conn, cnt] = *first;
      assert(!explored[conn]);
      total += cnt;
      for (int iter = 0; iter < cnt; ++iter) {
        if (exploring[conn]) {
          // the edge must come from conn to i
          directEdges[conn].push_back(i);
        } else {
          // the edge should come from i to conn
          directEdges[i].push_back(conn);
        }
      }
      uEdges[conn].erase(i);
    }

    exploring[i] = false;
    explored[i] = true;
  };
  for (int i = 0; i < n; ++i) {
    if (!explored[i]) {
      dfs(dfs, i);
    }
  }
  assert(total == m);
  // output
  for (int i = 0; i < n; ++i) {
    for (int conn : directEdges[i]) {
      cout << i + 1 << ' ' << conn + 1 << endl;
    }
  }
}