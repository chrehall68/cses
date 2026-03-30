#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ll n, m;
  cin >> n >> m;
  vector<vector<ll>> adjList(n);
  for (ll i = 0; i < m; ++i) {
    ll a, b;
    cin >> a >> b;
    adjList[--a].push_back(--b);
  }
  // then just dfs to find a cycle
  // or if that fails, impossible
  vector<bool> explored(n, false), exploring(n, false);
  vector<ll> pi(n);
  function<bool(ll)> dfs = [&](ll i) {
    if (exploring[i]) {
      // found a cycle
      ll cur = pi[i];
      vector<ll> cycle = {i};
      while (cur != i) {
        cycle.push_back(cur);
        cur = pi[cur];
      }
      cycle.push_back(i);
      reverse(cycle.begin(), cycle.end());
      cout << cycle.size() << endl;
      for (ll node : cycle) {
        cout << node + 1 << ' ';
      }
      cout << endl;

      return true;
    }
    exploring[i] = true;
    bool ret = false;
    for (ll conn : adjList[i]) {
      if (!explored[conn]) {
        pi[conn] = i;
        ret = ret || dfs(conn);
      }
    }
    exploring[i] = false;
    explored[i] = true;
    return ret;
  };
  for (ll i = 0; i < n; ++i) {
    if (!explored[i]) {
      if (dfs(i)) {
        return 0;
      }
    }
  }
  cout << "IMPOSSIBLE" << endl;
}