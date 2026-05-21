#include <bits/stdc++.h>
using namespace std;
int main() {
  int n;
  cin >> n;
  vector<vector<int>> adj(n);
  for (int i = 0; i < n - 1; ++i) {
    int a, b;
    cin >> a >> b;
    adj[--a].push_back(--b);
    adj[b].push_back(a);
  }
  vector<bool> used(n);
  int total = 0;
  auto dfs = [&](auto &&d, int cur, int par) -> void {
    for (int conn : adj[cur]) {
      if (conn != par) {
        d(d, conn, cur);
        if (!used[conn] && !used[cur]) {
          used[conn] = used[cur] = true;
          total++;
        }
      }
    }
  };
  dfs(dfs, 0, -1);

  cout << total << endl;
}