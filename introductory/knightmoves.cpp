#include <bits/stdc++.h>
#include <limits>
using namespace std;

int main() {
  int n;
  cin >> n;
  vector<vector<int>> moves(n, vector<int>(n, -1));
  moves[0][0] = 0;
  // bfs
  vector<pair<int, int>> possibs = {{2, 1}, {2, -1}, {-2, 1}, {-2, -1},
                                    {1, 2}, {1, -2}, {-1, 2}, {-1, -2}};
  queue<pair<int, int>> q;
  q.push({0, 0});
  while (!q.empty()) {
    auto [r, c] = q.front();
    q.pop();

    // add its connections
    for (pair<int, int> &possib : possibs) {
      int rp = r + possib.first;
      int cp = c + possib.second;
      if (0 <= rp && rp < n && 0 <= cp && cp < n && moves[rp][cp] == -1) {
        moves[rp][cp] = moves[r][c] + 1;
        q.push({rp, cp});
      }
    }
  }

  // output
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      cout << moves[i][j] << ' ';
    }
    cout << endl;
  }
}