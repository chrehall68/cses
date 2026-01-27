#include <bits/stdc++.h>
using namespace std;

int main() {
  int n, m;
  cin >> n >> m;
  vector<vector<int>> g(n + 1);
  for (int i = 0; i < m; ++i) {
    int a, b;
    cin >> a >> b;
    g[a].push_back(b);
    g[b].push_back(a);
  }
  // now just bfs from 1
  vector<int> parents(n + 1, -1);
  queue<int> toExplore;
  toExplore.push(1);
  while (!toExplore.empty()) {
    int top = toExplore.front();
    toExplore.pop();
    for (int conn : g[top]) {
      if (parents[conn] == -1) {
        // explore it
        parents[conn] = top;
        toExplore.push(conn);
      }
    }
  }
  // now reconstruct, if possible
  if (parents[n] == -1) {
    cout << "IMPOSSIBLE" << endl;
  } else {
    // need to retrace steps
    vector<int> computers = {n};
    while (computers.back() != 1) {
      computers.push_back(parents[computers.back()]);
    }
    reverse(computers.begin(), computers.end());
    cout << computers.size() << endl;
    for (int i : computers) {
      cout << i << " ";
    }
    cout << endl;
  }
}