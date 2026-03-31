#include <bits/stdc++.h>
using namespace std;

int main() {
  int n, m;
  cin >> n >> m;
  vector<vector<int>> adj(n), adjR(n);
  for (int i = 0; i < m; ++i) {
    int a, b;
    cin >> a >> b;
    adj[--a].push_back(--b);
    adjR[b].push_back(a);
  }
  // should form exactly 1 scc
  vector<int> order;
  vector<bool> explored(n);
  function<void(int)> dfs = [&](int i) {
    explored[i] = true;
    for (int conn : adj[i]) {
      if (!explored[conn]) {
        dfs(conn);
      }
    }
    order.push_back(i);
  };
  for (int i = 0; i < n; ++i) {
    if (!explored[i]) {
      dfs(i);
    }
  }
  // then reverse (gives us topological order)
  reverse(order.begin(), order.end());
  // then dfs again, collecting into components in topological order
  vector<vector<int>> components;
  fill(explored.begin(), explored.end(), false);
  function<void(int)> dfs2 = [&](int i) {
    explored[i] = true;
    components.back().push_back(i);
    for (int conn : adjR[i]) {
      if (!explored[conn]) {
        dfs2(conn);
      }
    }
  };
  for (int node : order) {
    if (!explored[node]) {
      components.push_back({});
      dfs2(node);
    }
  }
  if (components.size() == 1) {
    cout << "YES" << endl;
  } else {
    cout << "NO" << endl;
    cout << components[1][0] + 1 << ' ' << components[0][0] + 1 << endl;
  }
}