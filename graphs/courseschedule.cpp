#include <bits/stdc++.h>
using namespace std;

int main() {
  int n, m;
  cin >> n >> m;
  vector<vector<int>> adjList(n);
  vector<int> indegree(n);
  for (int i = 0; i < m; ++i) {
    int a, b;
    cin >> a >> b;
    // a before b
    adjList[--a].push_back(--b);
    indegree[b]++;
  }
  // then topsort
  vector<int> order;
  for (int i = 0; i < n; ++i) {
    if (indegree[i] == 0) {
      order.push_back(i);
    }
  }
  for (int i = 0; i < order.size(); ++i) {
    for (int conn : adjList[order[i]]) {
      if (--indegree[conn] == 0) {
        order.push_back(conn);
      }
    }
  }
  if (order.size() < n) {
    cout << "IMPOSSIBLE" << endl;
  } else {
    for (int node : order) {
      cout << node + 1 << ' ';
    }
    cout << endl;
  }
}