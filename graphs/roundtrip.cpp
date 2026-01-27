#include <bits/stdc++.h>
using namespace std;

void dfs(vector<bool> &explored, vector<int> &parents, vector<vector<int>> &g,
         int i, int parent) {
  explored[i] = true;
  for (int conn : g[i]) {
    if (conn != parent) {
      parents[conn] = i;
      if (explored[conn]) {
        // found a cycle
        vector<int> nodes = {conn, i};
        while (nodes.back() != conn) {
          nodes.push_back(parents[nodes.back()]);
        }
        cout << nodes.size() << endl;
        for (int node : nodes) {
          cout << node << " ";
        }
        cout << endl;

        exit(0);
      }
      dfs(explored, parents, g, conn, i);
    }
  }
}

int main() {
  int n, m;
  cin >> n >> m;
  vector<vector<int>> g(n + 1);
  vector<bool> explored(n + 1, false);
  vector<int> parents(n + 1, -1);
  for (int i = 0; i < m; ++i) {
    int a, b;
    cin >> a >> b;
    g[a].push_back(b);
    g[b].push_back(a);
  }
  for (int i = 1; i <= n; ++i) {
    if (!explored[i]) {
      dfs(explored, parents, g, i, -1);
    }
  }

  cout << "IMPOSSIBLE" << endl;
}