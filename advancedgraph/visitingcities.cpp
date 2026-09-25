#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  int n, m;
  cin >> n >> m;
  vector<vector<pair<int, ll>>> g(n);
  for (int i = 0; i < m; ++i) {
    int a, b, c;
    cin >> a >> b >> c;
    g[--a].push_back({--b, c});
  }
  // since all weights are nonnegative, just use dijkstra's and keep track of
  // parents then we can topsort the parents
  vector<vector<int>> parents(n);
  const ll M = 1'000'000'000'000'000LL;
  vector<ll> minDists(n, M);
  priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<>> minPq;
  minDists[0] = 0;
  minPq.push({0, 0});
  while (!minPq.empty()) {
    auto [cost, node] = minPq.top();
    minPq.pop();
    if (cost > minDists[node]) {
      // this is a stale version
      continue;
    }
    // this is a current cost
    for (auto [conn, connCost] : g[node]) {
      ll nextCost = cost + connCost;
      if (nextCost < minDists[conn]) {
        minDists[conn] = nextCost;
        parents[conn] = {node};
        minPq.push({nextCost, conn});
      } else if (nextCost == minDists[conn]) {
        parents[conn].push_back(node);
      }
    }
  }
  // now that we have that, filter down to just our graph
  // we can do that by bfs'ing on the parents
  // starting at n-1
  vector<bool> explored(n);
  queue<int> q;
  q.push(n - 1);
  explored[n - 1] = true;
  vector<int> outDegree(n);
  while (!q.empty()) {
    int node = q.front();
    q.pop();
    for (int parent : parents[node]) {
      outDegree[parent]++;
      if (!explored[parent]) {
        q.push(parent);
        explored[parent] = true;
      }
    }
  }
  // now do the topsort
  assert(outDegree[n - 1] == 0);
  set<int> reachable;
  set<int> criticalCities;
  reachable.insert(n - 1);
  q.push(n - 1);
  while (!q.empty()) {
    int node = q.front();
    q.pop();
    if (reachable.size() == 1) {
      criticalCities.insert(node);
    }
    reachable.erase(node);
    for (int parent : parents[node]) {
      reachable.insert(parent);
      if (--outDegree[parent] == 0) {
        q.push(parent);
      }
    }
  }
  cout << criticalCities.size() << endl;
  for (int node : criticalCities) {
    cout << node + 1 << ' ';
  }
  cout << endl;
}