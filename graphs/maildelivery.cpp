#include <bits/stdc++.h>
using namespace std;

int main() {
  // so we just need an eulerian tour
  // which is possible iff every vertex has even degree
  int n, m;
  cin >> n >> m;
  list<int> visited;
  vector<int> degree(n);
  vector<set<int>> adj(n);
  for (int i = 0; i < m; ++i) {
    int a, b;
    cin >> a >> b;
    adj[--a].insert(--b);
    adj[b].insert(a);
    degree[a]++;
    degree[b]++;
  }
  bool allEven = true;
  for (int i = 0; i < n; ++i) {
    allEven = allEven && degree[i] % 2 == 0;
  }
  // then dfs
  int used = 0;
  function<void(int, list<int>::iterator)> dfs =
      [&](int i, list<int>::iterator myPos) {
        while (!adj[i].empty()) {
          int conn = *adj[i].begin();
          adj[i].erase(conn);
          adj[conn].erase(i);
          used++;
          auto insertBefore = myPos;
          insertBefore++;
          auto nextPos = visited.insert(insertBefore, conn);
          // and dfs that
          dfs(conn, nextPos);
        }
      };
  visited.push_back(0);
  dfs(0, visited.begin());
  if (!allEven || used != m || *(--visited.end()) != 0) {
    cout << "IMPOSSIBLE" << endl;
  } else {
    for (int node : visited) {
      cout << node + 1 << ' ';
    }
    cout << endl;
  }
}