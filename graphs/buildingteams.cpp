#include <bits/stdc++.h>
using namespace std;

int main() {
  // so we just want to 2 color the forest
  int n, m;
  cin >> n >> m;
  vector<vector<int>> g(n + 1);
  for (int i = 0; i < m; ++i) {
    int a, b;
    cin >> a >> b;
    g[a].push_back(b);
    g[b].push_back(a);
  }
  // just try to two-color the graph
  vector<int> assignments(n + 1, 0); // 0 = unassigned, 1,2
  for (int i = 1; i <= n; ++i) {
    if (assignments[i] == 0) {
      // assign arbitrarily
      assignments[i] = 1;
      queue<int> toExplore;
      toExplore.push(i);
      while (!toExplore.empty()) {
        int front = toExplore.front();
        toExplore.pop();
        int next = assignments[front] == 1 ? 2 : 1;
        for (int conn : g[front]) {
          if (assignments[conn] == 0) {
            // color it
            assignments[conn] = next;
            toExplore.push(conn);
          } else if (assignments[conn] != next) {
            cout << "IMPOSSIBLE" << endl;
            return 0;
          }
        }
      }
    }
  }
  // now output
  for (int i = 1; i <= n; ++i) {
    cout << assignments[i] << " ";
  }
  cout << endl;
}