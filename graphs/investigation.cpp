#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll C = 1'000'000'007;

int main() {
  int n, m;
  cin >> n >> m;
  vector<vector<pair<ll, ll>>> adjList(n);
  for (int i = 0; i < m; ++i) {
    ll a, b, c;
    cin >> a >> b >> c;
    adjList[--a].push_back({--b, c});
  }
  // dijkstra's
  // info[i] = {minPrice, # ways, min length, max length}
  vector<tuple<ll, ll, ll, ll>> info(n, {1e18, -1, -1, -1});
  priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<>> pq;
  info[0] = {0, 1, 0, 0};
  pq.push({0, 0});
  while (!pq.empty()) {
    auto [cost, node] = pq.top();
    pq.pop();
    if (cost > get<0>(info[node])) {
      continue;
    }
    auto [minPrice, ways, minLength, maxLength] = info[node];
    assert(minPrice == cost);
    for (auto [conn, price] : adjList[node]) {
      if (minPrice + price < get<0>(info[conn])) {
        // new min price
        info[conn] = {minPrice + price, ways, minLength + 1, maxLength + 1};
        pq.push({minPrice + price, conn});
      } else if (minPrice + price == get<0>(info[conn])) {
        // more ways
        get<1>(info[conn]) += ways;
        get<1>(info[conn]) %= C;
        // and potentially new lengths
        get<2>(info[conn]) = min(get<2>(info[conn]), minLength + 1);
        get<3>(info[conn]) = max(get<3>(info[conn]), maxLength + 1);
      }
    }
  }

  auto [minPrice, ways, minLength, maxLength] = info[n - 1];
  cout << minPrice << ' ' << ways << ' ' << minLength << ' ' << maxLength
       << endl;
}