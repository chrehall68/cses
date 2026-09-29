#include <bits/stdc++.h>
using namespace std;

int main() {
  // we have a simple graph
  // if something has one edge connected to it, then that edge must be incoming
  // so that reduces our graph to a graph with at least original degree 2
  // sum(outdegree) = sum(indegree) = # edges
  // so if every node has even, then there must be even edges
  // it should be possible if there are an even number of edges in each
  // component. like if it was a tree this should be possible
  int n, m;
  cin >> n >> m;
  vector<vector<int>> g(n + 1), directedG(n + 1);
  for (int i = 0; i < m; ++i) {
    int a, b;
    cin >> a >> b;
    g[a].push_back(b);
    g[b].push_back(a);
  }
  vector<bool> exploring(n + 1), explored(n + 1);
  auto dfs = [&](auto &dfs, int i, int parent) -> int {
    exploring[i] = true;
    int outDegree = 0;
    for (int conn : g[i]) {
      if (conn != parent) {
        if (exploring[conn]) {
          // back edge
          // we'll just take this
          // (and then later we'll make sure not to touch this)
          directedG[i].push_back(conn);
          outDegree++;
        } else if (!explored[conn]) {
          // true child
          int childOutDegree = dfs(dfs, conn, i);
          if (childOutDegree % 2 == 0) {
            // we'll go to it
            outDegree++;
            directedG[i].push_back(conn);
          } else {
            // it'll go to us
            directedG[conn].push_back(i);
          }
        }
      }
    }
    explored[i] = true;
    exploring[i] = false;
    return outDegree;
  };

  for (int i = 1; i <= n; ++i) {
    if (!explored[i]) {
      int outdegree = dfs(dfs, i, -1);
      if (outdegree % 2 == 1) {
        cout << "IMPOSSIBLE" << endl;
        return 0;
      }
    }
  }
  // now output the assignment
  for (int from = 1; from <= n; ++from) {
    for (int to : directedG[from]) {
      cout << from << ' ' << to << endl;
    }
  }
}
