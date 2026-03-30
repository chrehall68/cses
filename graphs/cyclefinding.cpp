#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main() {
  int n, m;
  cin >> n >> m;
  // directed graph; we'll just bellman ford
  vector<vector<pair<int, ll>>> adjList(n);
  for (int i = 0; i < m; ++i) {
    ll a, b, cost;
    cin >> a >> b >> cost;
    a--;
    b--;
    adjList[a].push_back({b, cost});
  }
  // then just run it on each component
  vector<ll> dists(n, 0);
  vector<int> pi(n);
  bool didChange = true;
  int iter = 0;
  while (iter < n && didChange) {
    didChange = false;
    for (int i = 0; i < n; ++i) {
      for (auto [to, cost] : adjList[i]) {
        if (dists[i] + cost < dists[to]) {
          dists[to] = dists[i] + cost;
          pi[to] = i;
          didChange = true;
        }
      }
    }
    iter++;
  }
  if (iter == n && didChange) {
    for (int i = 0; i < n; ++i) {
      for (auto [to, cost] : adjList[i]) {
        if (dists[i] + cost < dists[to]) {
          // found a node in or downstream of the cycle
          vector<int> exploring;
          vector<bool> seen(n, false);
          seen[to] = true;
          exploring.push_back(to);
          int cur = i;
          while (!seen[cur]) {
            exploring.push_back(cur);
            seen[cur] = true;
            cur = pi[cur];
          }
          // then take just the cycle
          vector<int> cycle;
          cycle.push_back(cur);
          while (exploring.back() != cur) {
            cycle.push_back(exploring.back());
            exploring.pop_back();
          }
          cycle.push_back(cur);
          cout << "YES" << endl;
          for (int node : cycle) {
            cout << node + 1 << ' ';
          }
          cout << endl;
          return 0;
        }
      }
    }
  }
  cout << "NO" << endl;
}