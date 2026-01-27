#include <bits/stdc++.h>
using namespace std;

int main() {
  int n, m;
  cin >> n >> m;
  vector<string> grid(n);
  for (int i = 0; i < n; ++i) {
    cin >> grid[i];
  }
  int rooms = 0;
  vector<vector<bool>> explored(n, vector<bool>(m, false));
  vector<pair<int, int>> dirs = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
  for (int r = 0; r < n; ++r) {
    for (int c = 0; c < m; ++c) {
      if (grid[r][c] == '.' && !explored[r][c]) {
        rooms++;
        queue<pair<int, int>> toVisit;
        toVisit.push({r, c});
        explored[r][c] = true;
        while (!toVisit.empty()) {
          auto [fr, fc] = toVisit.front();
          toVisit.pop();
          for (auto [ri, ci] : dirs) {
            int rp = fr + ri, cp = fc + ci;
            if (0 <= rp && rp < n && 0 <= cp && cp < m && grid[rp][cp] == '.' &&
                !explored[rp][cp]) {
              // explore it
              explored[rp][cp] = true;
              toVisit.push({rp, cp});
            }
          }
        }
      }
    }
  }
  cout << rooms << endl;
}