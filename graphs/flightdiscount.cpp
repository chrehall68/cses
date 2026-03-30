#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main() {

  int n, m;
  cin >> n >> m;
  vector<vector<pair<int, ll>>> adjList(n);
  vector<vector<pair<int, ll>>> incomingAdjList(n);
  for (int i = 0; i < m; ++i) {
    ll a, b, cost;
    cin >> a >> b >> cost;
    a--;
    b--;
    adjList[a].push_back({b, cost});
    incomingAdjList[b].push_back({a, cost});
  }
  // one dijkstra's to figure out cost to get to destination city
  const ll IMPOSSIBLE = 1e15;
  vector<ll> toDest(n, IMPOSSIBLE);
  toDest[n - 1] = 0;
  priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<>> pq;
  pq.push({0, n - 1});
  while (!pq.empty()) {
    auto [cost, top] = pq.top();
    pq.pop();
    if (cost == toDest[top]) {
      // explore this
      for (auto [from, extra] : incomingAdjList[top]) {
        if (cost + extra < toDest[from]) {
          toDest[from] = cost + extra;
          pq.push({cost + extra, from});
        }
      }
    }
  }
  // then do similar thing for first one
  vector<ll> fromSource(n, IMPOSSIBLE);
  fromSource[0] = 0;
  pq.push({0, 0});
  ll best = IMPOSSIBLE;
  while (!pq.empty()) {
    auto [cost, top] = pq.top();
    pq.pop();
    if (cost == fromSource[top]) {
      // explore this
      for (auto [to, extra] : adjList[top]) {
        if (cost + extra < fromSource[to]) {
          fromSource[to] = cost + extra;
          pq.push({cost + extra, to});
          // and consider using this as the one that gets cut in half
          best = min(best, cost + extra / 2 + toDest[to]);
        }
      }
    }
  }
  cout << best << endl;
}