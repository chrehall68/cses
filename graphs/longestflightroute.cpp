#include <bits/stdc++.h>
using namespace std;

int main() {
  int n, m;
  cin >> n >> m;
  // because it's a DAG, we can go in topological order
  // to find the longest path
  vector<vector<int>> adjList(n);
  vector<int> inDegree(n);
  for (int i = 0; i < m; ++i) {
    int a, b;
    cin >> a >> b;
    adjList[--a].push_back(--b);
    inDegree[b]++;
  }
  vector<int> order;
  for (int i = 0; i < n; ++i) {
    if (inDegree[i] == 0) {
      order.push_back(i);
    }
  }
  for (int i = 0; i < order.size(); ++i) {
    for (int conn : adjList[order[i]]) {
      if (--inDegree[conn] == 0) {
        order.push_back(conn);
      }
    }
  }
  // now go in topological order
  vector<int> dists(n, -2 * n);
  vector<int> pi(n);
  dists[0] = 0;
  for (int node : order) {
    for (int conn : adjList[node]) {
      if (dists[node] + 1 > dists[conn]) {
        pi[conn] = node;
        dists[conn] = dists[node] + 1;
      }
    }
  }
  if (dists[n - 1] < 0) {
    cout << "IMPOSSIBLE" << endl;
    return 0;
  }
  // then go back from end
  vector<int> path;
  for (int cur = n - 1; cur != 0; cur = pi[cur]) {
    path.push_back(cur);
  }
  path.push_back(0);
  reverse(path.begin(), path.end());
  cout << path.size() << endl;
  for (int node : path) {
    cout << node + 1 << ' ';
  }
  cout << endl;
}