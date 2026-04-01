#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ll n, m;
  cin >> n >> m;
  vector<ll> coins(n);
  for (ll i = 0; i < n; ++i) {
    cin >> coins[i];
  }
  vector<vector<ll>> adj(n), adjR(n);
  for (ll i = 0; i < m; ++i) {
    ll a, b;
    cin >> a >> b;
    adj[--a].push_back(--b);
    adjR[b].push_back(a);
  }
  // convert into scc, then dp up
  vector<ll> order;
  vector<bool> explored(n, false);
  function<void(ll)> dfs = [&](ll i) {
    explored[i] = true;
    for (ll conn : adj[i]) {
      if (!explored[conn]) {
        dfs(conn);
      }
    }
    order.push_back(i);
  };
  for (ll i = 0; i < n; ++i) {
    if (!explored[i]) {
      dfs(i);
    }
  }
  reverse(order.begin(), order.end());
  vector<ll> compScore, component(n);
  vector<vector<ll>> components;
  fill(explored.begin(), explored.end(), false);
  function<void(ll, ll)> dfs2 = [&](ll i, ll comp) {
    explored[i] = true;
    component[i] = comp;
    compScore[comp] += coins[i];
    components[comp].push_back(i);
    for (ll conn : adjR[i]) {
      if (!explored[conn]) {
        dfs2(conn, comp);
      }
    }
  };
  ll comp = 0;
  for (ll node : order) {
    if (!explored[node]) {
      compScore.push_back(0);
      components.push_back({});
      dfs2(node, comp++);
    }
  }
  // then dp up
  for (ll i = components.size() - 1; i >= 0; --i) {
    ll maxBelow = 0;
    for (ll node : components[i]) {
      for (ll conn : adj[node]) {
        ll comp = component[conn];
        if (comp != i) {
          maxBelow = max(maxBelow, compScore[comp]);
        }
      }
    }
    compScore[i] += maxBelow;
  }
  cout << *max_element(compScore.begin(), compScore.end()) << endl;
}