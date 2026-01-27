
#include <bits/stdc++.h>
using namespace std;

int main() {
  int n, m;
  cin >> n >> m;
  vector<string> grid(n);
  for (int i = 0; i < n; ++i) {
    cin >> grid[i];
  }
  // find start and end
  pair<int, int> start, end;
  for (int r = 0; r < n; ++r) {
    for (int c = 0; c < m; ++c) {
      if (grid[r][c] == 'A') {
        start = {r, c};
      } else if (grid[r][c] == 'B') {
        end = {r, c};
      }
    }
  }
  // now just bfs from A, storing where parents come from
  vector<vector<bool>> explored(n, vector<bool>(m, false));
  vector<vector<int>> parents(n, vector<int>(m, -1));
  vector<pair<int, int>> dirs = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
  string dirNames = "RLDU";
  queue<pair<int, int>> toVisit;
  toVisit.push(start);
  explored[start.first][start.second] = true;
  while (!toVisit.empty()) {
    auto [fr, fc] = toVisit.front();
    toVisit.pop();
    for (int i = 0; i < dirs.size(); ++i) {
      auto [ri, ci] = dirs[i];
      int rp = fr + ri, cp = fc + ci;
      if (0 <= rp && rp < n && 0 <= cp && cp < m && grid[rp][cp] != '#' &&
          !explored[rp][cp]) {
        // explore it
        explored[rp][cp] = true;
        toVisit.push({rp, cp});
        parents[rp][cp] = i;
      }
    }
  }
  // reconstruct
  if (parents[end.first][end.second] == -1) {
    cout << "NO" << endl;
  } else {
    string result;
    int r = end.first, c = end.second;
    while (r != start.first || c != start.second) {
      result += dirNames[parents[r][c]];
      auto [ri, ci] = dirs[parents[r][c]];
      r -= ri;
      c -= ci;
    }
    cout << "YES" << endl;
    cout << result.size() << endl;
    reverse(result.begin(), result.end());
    cout << result << endl;
  }
}