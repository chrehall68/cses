#include <bits/stdc++.h>
using namespace std;

int main() {
  // so we know that these vertices must lie on a shortest
  // path from 1 to n
  // because we can think of like
  // 1 - a - b - c - d - n
  // |       |
  //  detour
  // so let's construct a shortest path
  // then, we know that any time we have skip connections (some longer
  // path that goes from index i to index j, j >= i+2)
  // then that disqualifies all nodes in the middle
  // so we can do a bfs to see what nodes on the shortest path get disqualified
  int n, m;
  cin >> n >> m;
  vector<vector<int>> g(n + 1);
  vector<pair<int, int>> edges(m);
  for (int i = 0; i < m; ++i) {
    int a, b;
    cin >> a >> b;
    g[a].push_back(b);
    edges[i] = {a, b};
  }

  // bfs to construct shortest paths / parents
  const int NONEXISTENT = -1;
  vector<size_t> distanceTo1(n + 1, n + 1);
  vector<int> parents(n + 1, NONEXISTENT);
  queue<int> q;
  distanceTo1[1] = 0;
  q.push(1);
  while (!q.empty()) {
    int node = q.front();
    q.pop();
    size_t nextDist = distanceTo1[node] + 1;
    for (int conn : g[node]) {
      if (nextDist < distanceTo1[conn]) {
        q.push(conn);
        distanceTo1[conn] = nextDist;
        parents[conn] = node;
      }
    }
  }
  // now that we have that, filter down to just our graph
  // we can do that by bfs'ing on the parents
  // starting at n-1
  vector<bool> onShortest(n + 1);
  vector<int> shortestPath;
  for (int curNode = n; curNode != 1; curNode = parents[curNode]) {
    assert(parents[curNode] != NONEXISTENT);
    onShortest[curNode] = true;
    shortestPath.push_back(curNode);
  }
  onShortest[1] = true;
  shortestPath.push_back(1);
  reverse(shortestPath.begin(), shortestPath.end());
  // now remove those edges
  vector<vector<int>> filtered(n + 1);
  for (int i = 1; i <= n; ++i) {
    for (int conn : g[i]) {
      if (!(onShortest[i] && onShortest[conn])) {
        // this is not one of the edges on the shortest path that we chose
        // so we can add it to our filtered graph
        filtered[i].push_back(conn);
      }
    }
  }
  // now do another bfs on filtered
  // keeping track of the maximum idx on the shortest path that we can reach
  size_t maxDistOnShortest = 0;
  vector<bool> explored(n + 1);
  set<int> criticalCities;
  for (size_t shortestPathIdx = 0; shortestPathIdx < shortestPath.size();
       ++shortestPathIdx) {
    int node = shortestPath[shortestPathIdx];
    if (maxDistOnShortest <= shortestPathIdx) {
      // this is a good one
      criticalCities.insert(node);
    }
    // now use this
    assert(!explored[node]);
    q.push(node);
    while (!q.empty()) {
      int top = q.front();
      q.pop();
      for (int conn : filtered[top]) {
        if (!explored[conn]) {
          if (onShortest[conn]) {
            maxDistOnShortest = max(maxDistOnShortest, distanceTo1[conn]);
          } else {
            // not on the shortest, so continue our bfs
            explored[conn] = true;
            q.push(conn);
          }
        }
      }
    }
  }
  // output
  cout << criticalCities.size() << endl;
  for (int node : criticalCities) {
    cout << node << ' ';
  }
  cout << endl;
}
