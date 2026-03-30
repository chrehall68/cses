#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  ll n, m, k;
  cin >> n >> m >> k;
  // {to, cost}
  vector<vector<pair<ll, ll>>> adjList(n);
  for (ll i = 0; i < m; ++i) {
    ll a, b, c;
    cin >> a >> b >> c;
    adjList[--a].push_back({--b, c});
  }
  vector<int> times(n, 0);
  vector<ll> d;
  // min heap
  priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<>> pq;
  pq.push({0, 0});
  while (times[n - 1] < k) {
    auto [cost, node] = pq.top();
    pq.pop();
    if (times[node] >= k) {
      continue;
    }
    // use this node
    times[node]++;
    if (node == n - 1) {
      d.push_back(cost);
    }
    for (auto [conn, c] : adjList[node]) {
      if (times[conn] < k) {
        pq.push({c + cost, conn});
      }
    }
  }
  for (auto c : d) {
    cout << c << ' ';
  }
  cout << endl;
}