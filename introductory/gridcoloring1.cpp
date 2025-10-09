#include <bits/stdc++.h>
using namespace std;

int main() {
  // find A's or B's and color them C's/D's
  // vice versa
  int n, m;
  cin >> n >> m;
  vector<vector<char>> original(n, vector<char>(m));
  vector<vector<bool>> used(n, vector<bool>(m, false));
  vector<vector<char>> output(n, vector<char>(m));

  // read in input
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      cin >> original[i][j];
    }
  }

  vector<pair<int, int>> dirs = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
  // do stuff
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (!used[i][j]) {
        // stuff needs to be bfs'd
        vector<int> haveCharset;
        vector<int> replaceCharset;
        if (original[i][j] == 'A' || original[i][j] == 'B') {
          haveCharset = {'A', 'B'};
          replaceCharset = {'C', 'D'};
        } else {
          haveCharset = {'C', 'D'};
          replaceCharset = {'A', 'B'};
        }

        // bfs
        vector<pair<int, int>> curLevel = {{i, j}};
        used[i][j] = true;
        int curIndex = 0;
        while (!curLevel.empty()) {
          vector<pair<int, int>> nextLevel;
          for (auto [r, c] : curLevel) {
            // set to new
            output[r][c] = replaceCharset[curIndex];
            // explore connections
            for (pair<int, int> p2 : dirs) {
              int ri = p2.first;
              int ci = p2.second;
              int rp = r + ri;
              int cp = c + ci;
              if (0 <= rp && rp < n && 0 <= cp && cp < m &&
                  (original[rp][cp] == haveCharset[0] ||
                   original[rp][cp] == haveCharset[1]) &&
                  !used[rp][cp]) {
                used[rp][cp] = true;
                nextLevel.push_back({rp, cp});
              }
            }
          }
          curLevel = move(nextLevel);
          curIndex++;
          curIndex %= 2;
        }
      }
    }
  }
  // output
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      cout << output[i][j];
    }
    cout << endl;
  }
}