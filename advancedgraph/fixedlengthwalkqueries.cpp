#include <bits/stdc++.h>
using namespace std;
const int M = 2'000'000'000;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int n, m, q;
  cin >> n >> m >> q;
  vector<vector<int>> edges(n + 1);
  for (int i = 0; i < m; ++i) {
    int a, b;
    cin >> a >> b;
    edges[a].push_back(b);
    edges[b].push_back(a);
  }
  // now compute, for every node x,
  // the minimum distance from x -> other
  // with even parity and odd parity
  vector<vector<int>> minDistances(n + 1, vector<int>((n + 1) * 2, M));
  queue<pair<int, int>> toProcess;
  for (int x = 1; x <= n; ++x) {
    toProcess.push({x, 0}); // node, distance
    while (!toProcess.empty()) {
      auto [node, dist] = toProcess.front();
      toProcess.pop();

      int nextDist = dist + 1;
      for (int conn : edges[node]) {
        if (nextDist < minDistances[x][conn * 2 + nextDist % 2]) {
          minDistances[x][conn * 2 + nextDist % 2] = nextDist;
          toProcess.push({conn, nextDist});
        }
      }
    }
  }
  // now process queries
  for (; q > 0; --q) {
    int a, b, x;
    cin >> a >> b >> x;
    int minDist = minDistances[a][b * 2 + x % 2];
    if (minDist <= x || (x == 0 && a == b)) {
      cout << "YES" << '\n';
    } else {
      cout << "NO" << '\n';
    }
  }
}