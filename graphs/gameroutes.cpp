#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll C = 1'000'000'007;

int main() {
  int n, m;
  cin >> n >> m;
  // because it's a DAG, we can go in topological order
  // to find the number of ways
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
  vector<ll> ways(n);
  ways[0] = 1;
  for (int node : order) {
    for (int conn : adjList[node]) {
      ways[conn] += ways[node];
      ways[conn] %= C;
    }
  }
  // then go back from end
  cout << ways[n - 1] << endl;
}