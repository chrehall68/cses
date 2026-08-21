#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  int n;
  cin >> n;
  vector<vector<int>> g(n);
  for (int i = 0; i < n - 1; ++i) {
    int a, b;
    cin >> a >> b;
    g[--a].push_back(--b);
    g[b].push_back(a);
  }
  // dfs to compute subtree number of nodes
  // and sum of distances
  vector<int> subtreeNumberOfNodes(n);
  auto dfs = [&](auto &dfs, int i, int parent) -> ll {
    ll distanceSum = 0;
    int numNodes = 1;
    for (int conn : g[i]) {
      if (conn != parent) {
        distanceSum += dfs(dfs, conn, i) + subtreeNumberOfNodes[conn];
        numNodes += subtreeNumberOfNodes[conn];
      }
    }
    subtreeNumberOfNodes[i] = numNodes;
    return distanceSum;
  };
  ll distanceSum = dfs(dfs, 0, -1);
  // then dfs again to fill in the answer
  vector<ll> result(n);
  auto dfs2 = [&](auto &dfs2, int i, int parent) -> void {
    if (i == 0) {
      result[i] = distanceSum;
    } else {
      // all things outside my subtree need an extra step
      // and all things inside my subtree need one less step
      result[i] = result[parent] + (n - subtreeNumberOfNodes[i]) -
                  subtreeNumberOfNodes[i];
    }
    // then fill in children
    for (int conn : g[i]) {
      if (conn != parent) {
        dfs2(dfs2, conn, i);
      }
    }
  };
  dfs2(dfs2, 0, -1);
  for (ll res : result) {
    cout << res << ' ';
  }
  cout << endl;
}