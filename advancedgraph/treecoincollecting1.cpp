#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  // to make it to a coin, we have to go off the path
  // if the coin is k nodes off the path, we end up stepping 2k extra steps
  // so just need to store, for every node, what is its min distance
  // to a coin
  // and then take the minimum of that along the path from a to b, which
  // we can do with lca / binary lifts
  int n, q;
  cin >> n >> q;
  vector<bool> hasCoin(n + 1);
  queue<int> distQueue; // for bfs to figure out min dist to coin
  vector<int> minDistToCoin(n + 1, n + 1);
  for (int i = 1; i <= n; ++i) {
    int c;
    cin >> c;
    hasCoin[i] = c == 1;
    if (hasCoin[i]) {
      distQueue.push(i);
      minDistToCoin[i] = 0;
    }
  }
  vector<vector<int>> g(n + 1);
  for (int i = 0; i < n - 1; ++i) {
    int a, b;
    cin >> a >> b;
    g[a].push_back(b);
    g[b].push_back(a);
  }
  // bfs to compute min dist to coin
  while (!distQueue.empty()) {
    int node = distQueue.front();
    distQueue.pop();
    int nextDist = minDistToCoin[node] + 1;
    for (int conn : g[node]) {
      if (nextDist < minDistToCoin[conn]) {
        minDistToCoin[conn] = nextDist;
        distQueue.push(conn);
      }
    }
  }
  // now calculate lifts
  // lifts[node][i] = {2**i'th parent, min dist to coin along path}
  vector<vector<pair<int, int>>> lifts(n + 1);
  vector<int> depths(n + 1);
  auto dfs = [&](auto &dfs, int i, int parent) -> void {
    // compute my lifts
    for (int l = 0; l < lifts[i].size() && l < lifts[lifts[i][l].first].size();
         ++l) {
      auto [myParent, myMinDist] = lifts[i][l];
      auto [nextParent, theirMinDist] = lifts[myParent][l];
      lifts[i].push_back({nextParent, min(myMinDist, theirMinDist)});
    }
    // then dfs
    for (int conn : g[i]) {
      if (conn != parent) {
        depths[conn] = depths[i] + 1;
        lifts[conn].push_back({i, minDistToCoin[conn]});
        dfs(dfs, conn, i);
      }
    }
  };
  depths[1] = 0;
  dfs(dfs, 1, 0);
  // now process queries
  const int MAX_LCA = 21;
  for (int i = 0; i < q; ++i) {
    int a, b;
    cin >> a >> b;
    int lower = a, higher = b;
    if (depths[lower] < depths[higher]) {
      swap(lower, higher);
    }
    // move lower up
    int minOnPath = n;
    int dist = 0;
    for (int i = MAX_LCA; i >= 0; --i) {
      if (depths[lower] - (1 << i) >= depths[higher]) {
        auto [nextLower, segmentMin] = lifts[lower][i];
        minOnPath = min(minOnPath, segmentMin);
        lower = nextLower;
        dist += 1 << i;
      }
    }
    // then move both up
    int lca = lower;
    if (lower != higher) {
      for (int i = MAX_LCA; i >= 0; --i) {
        if (i < lifts[lower].size() &&
            lifts[lower][i].first != lifts[higher][i].first) {
          auto [nextLower, segmentMinL] = lifts[lower][i];
          minOnPath = min(minOnPath, segmentMinL);
          lower = nextLower;

          auto [nextHigher, segmentMinH] = lifts[higher][i];
          minOnPath = min(minOnPath, segmentMinH);
          higher = nextHigher;

          dist += 2 << i;
        }
      }
      assert(lower != higher);
      assert(lifts[lower][0].first == lifts[higher][0].first);
      minOnPath = min(minOnPath, lifts[lower][0].second);
      minOnPath = min(minOnPath, lifts[higher][0].second);
      dist += 2;
      lca = lifts[lower][0].first;
    }
    minOnPath = min(minOnPath, minDistToCoin[lca]);

    cout << 2 * minOnPath + dist << '\n';
  }
}