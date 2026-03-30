#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  int n, m, q;
  cin >> n >> m >> q;
  // then we find shortest paths
  // technically we could floyd warshall in v^3
  // but we can also dijkstra's in n*(n+m)lgn
  // but that's worse when m = n**2
  // so floyd warshall is better
  vector<vector<ll>> dp(n, vector<ll>(n, 1e14));
  for (int i = 0; i < n; ++i) {
    dp[i][i] = 0;
  }
  for (int i = 0; i < m; ++i) {
    ll a, b, cost;
    cin >> a >> b >> cost;
    a--;
    b--;
    dp[a][b] = min(dp[a][b], cost);
    dp[b][a] = min(dp[b][a], cost);
  }
  // then just dp based on k
  for (int k = 0; k < n; ++k) {
    // either pass through k or don't pass through k
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j]);
      }
    }
  }
  // now answer queries
  for (int i = 0; i < q; ++i) {
    int a, b;
    cin >> a >> b;
    ll amt = dp[a - 1][b - 1];
    if (amt >= 1e14) {
      cout << -1 << endl;
    } else {
      cout << amt << endl;
    }
  }
}