#include <bits/stdc++.h>
using namespace std;
int main() {
  int n;
  cin >> n;
  vector<vector<int>> adj(n);
  for (int i = 1; i < n; ++i) {
    int a, b;
    cin >> a >> b;
    adj[--a].push_back(--b);
    adj[b].push_back(a);
  }
  int best = 0;
  auto dfs = [&](auto &&d, int i, int par) -> int {
    // returns height
    int ma2 = 0;
    int ma = 0;
    for (int conn : adj[i]) {
      if (conn != par) {
        int h = d(d, conn, i);
        if (h > ma) {
          ma2 = ma;
          ma = h;
        } else if (h > ma2) {
          ma2 = h;
        }
      }
    }
    best = max(best, 1 + ma2 + ma);

    return 1 + ma;
  };
  dfs(dfs, 0, -1);
  cout << best - 1 << endl;
}