#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
  int n, m;
  cin >> n >> m;
  // so if there's a positive weight cycle, then it's -1
  // basically, bellman ford on the inverted edge weights
  vector<vector<pair<int, ll>>> adjList(n);
  const ll UNREACHABLE = -1e15;
  vector<ll> dists(n, UNREACHABLE);
  for (int i = 0; i < m; ++i) {
    ll a, b, cost;
    cin >> a >> b >> cost;
    // 0-index them
    a--;
    b--;
    adjList[a].push_back({b, cost});
  }
  dists[0] = 0;
  // now just bellman ford, but use max instead of min
  bool didChange = true;
  int iter = 0;
  while (iter < n && didChange) {
    didChange = false;
    // relax edges in arbitrary order
    for (int a = 0; a < adjList.size(); ++a) {
      if (dists[a] != UNREACHABLE) {
        for (auto [b, cost] : adjList[a]) {
          // relax this edge
          didChange |= dists[a] + cost > dists[b];
          dists[b] = max(dists[b], dists[a] + cost);
        }
      }
    }
    iter++;
  }
  if (iter == n && didChange) {
    // then have a cycle and need to propagate the cycle
    queue<int> toExplore;
    vector<bool> explored(n, false);
    // do one more round to see who's in the cycle
    for (int a = 0; a < adjList.size(); ++a) {
      if (dists[a] != UNREACHABLE) {
        for (auto [b, cost] : adjList[a]) {
          if (dists[a] + cost > dists[b] && !explored[a]) {
            toExplore.push(a);
            explored[a] = true;
          }
        }
      }
    }
    // then propagate
    while (!toExplore.empty()) {
      int front = toExplore.front();
      dists[front] = -1;
      toExplore.pop();
      for (auto [b, _] : adjList[front]) {
        if (!explored[b]) {
          explored[b] = true;
          toExplore.push(b);
        }
      }
    }
  }
  // now just output
  cout << dists[n - 1] << endl;
}