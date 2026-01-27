#include <bits/stdc++.h>
#include <limits>
#include <queue>
#include <vector>
using namespace std;
using ll = long long;

int main() {
  int n, m;
  cin >> n >> m;
  vector<vector<pair<int, ll>>> g(n + 1);
  for (int i = 0; i < m; ++i) {
    int a, b, c;
    cin >> a >> b >> c;
    g[a].push_back({b, c});
  }
  // now just dijkstra's from 1
  vector<ll> minCosts(n + 1, numeric_limits<ll>::max());
  minCosts[1] = 0;
  priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<>> pq;
  pq.push({0, 1}); // cost, node
  while (!pq.empty()) {
    auto [cost, node] = pq.top();
    pq.pop();
    if (cost <= minCosts[node]) {
      // explore neighbors
      for (auto [conn, extra] : g[node]) {
        if (extra + cost < minCosts[conn]) {
          minCosts[conn] = extra + cost;
          pq.push({extra + cost, conn});
        }
      }
    }
  }
  for (int i = 1; i <= n; ++i) {
    cout << minCosts[i] << " ";
  }
  cout << endl;
}