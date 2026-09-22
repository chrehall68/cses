#include <bits/stdc++.h>
using namespace std;

int main() {
  // length of shortest cycle?
  // unweighted edges
  // n is small
  // maybe just compute a table of distances
  // oh but that doesn't enforce that it's actually a true cycle
  // is this doable in a dfs?
  // we should at least be able to detect cycles in a dfs
  // so maybe just keep track of things' locations in the dfs
  // actually maybe that doesn't work
  // but maybe we can do something like, for each edge e that we add,
  // it joins a,b
  // then find the shortest path from a -> b (without using e)
  // and then take the min of that over adding all edges
  int n, m;
  cin >> n >> m;
  vector<vector<int>> edges(n);
  const int M = 1'000'000;
  vector<bool> visited(n);
  vector<int> dists(n);
  int minCycle = M;
  for (int i = 0; i < m; ++i) {
    int a, b;
    cin >> a >> b;
    --a;
    --b;

    // see if there's already a path
    fill(visited.begin(), visited.end(), false);
    fill(dists.begin(), dists.end(), M);
    dists[a] = 0;
    queue<int> toProcess;
    toProcess.push(a);
    while (dists[b] == M && !toProcess.empty()) {
      int top = toProcess.front();
      toProcess.pop();
      for (int conn : edges[top]) {
        if (dists[conn] > dists[top] + 1) {
          assert(dists[conn] == M);
          dists[conn] = dists[top] + 1;
          toProcess.push(conn);
        }
      }
    }
    // then if there is, this will have completed a cycle
    minCycle = min(minCycle, dists[b] + 1);
    // and put for later
    edges[a].push_back(b);
    edges[b].push_back(a);
  }
  if (minCycle >= M) {
    cout << -1 << endl;
  } else {
    cout << minCycle << endl;
  }
}