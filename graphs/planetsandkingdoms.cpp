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
  // just label each component
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
  vector<int> component(n);
  fill(explored.begin(), explored.end(), false);
  function<void(int, int)> dfs2 = [&](int i, int comp) {
    explored[i] = true;
    component[i] = comp;
    for (int conn : adjR[i]) {
      if (!explored[conn]) {
        dfs2(conn, comp);
      }
    }
  };
  int comps = 0;
  for (int node : order) {
    if (!explored[node]) {
      dfs2(node, ++comps);
    }
  }
  cout << comps << endl;
  for (int i = 0; i < n; ++i) {
    cout << component[i] << ' ';
  }
  cout << endl;
}