#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll C = 1'000'000'007;

int main() {
  int n, m;
  cin >> n >> m;
  vector<vector<int>> adj(n);
  for (int i = 0; i < m; ++i) {
    int a, b;
    cin >> a >> b;
    adj[--a].push_back(--b);
  }
  int limit = 1 << n;
  // ways[mask*n + lastCity] = # of ways to cover that mask w/ lastCity
  // as the ending
  vector<ll> ways(limit * n);
  ways[1 * n + 0] = 1;
  for (int mask = 0; mask < limit; ++mask) {
    // n shouldn't be something we consider since we have to end there
    if (mask >> (n - 1)) {
      continue;
    }
    for (int lastCity = 0; lastCity < n - 1; ++lastCity) {
      if (mask & (1 << lastCity)) {
        // is actually something that could be the last city
        for (int to : adj[lastCity]) {
          if (!(mask & (1 << to))) {
            // it's a new city
            ways[(mask | (1 << to)) * n + to] += ways[mask * n + lastCity];
            ways[(mask | (1 << to)) * n + to] %= C;
          }
        }
      }
    }
  }
  cout << ways[(limit - 1) * n + (n - 1)] << endl;
}