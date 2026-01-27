#include <bits/stdc++.h>
using namespace std;

int main() {
  int rows, cols;
  cin >> rows >> cols;
  vector<string> grid(rows);
  for (int i = 0; i < rows; ++i) {
    cin >> grid[i];
  }
  // so we bfs from the monsters and from a
  // if a ever makes it to the edge, then we win and we just reconstruct
  // otherwise it's impossible
  vector<vector<int>> parents(rows, vector<int>(cols, -1));
  vector<pair<int, int>> dirs = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
  string dirNames = "RLDU";
  vector<pair<int, int>> monsterPositions;
  vector<pair<int, int>> myPositions;
  pair<int, int> start;
  for (int r = 0; r < rows; ++r) {
    for (int c = 0; c < cols; ++c) {
      if (grid[r][c] == 'A') {
        myPositions.push_back({r, c});
      } else if (grid[r][c] == 'M') {
        monsterPositions.push_back({r, c});
      }
    }
  }
  start = myPositions[0];
  // now just keep bfs'ing
  while (!myPositions.empty()) {
    // expand from them
    vector<pair<int, int>> nextPositions;
    for (auto [r, c] : myPositions) {
      if (grid[r][c] == 'M') {
        continue;
      }
      if (r == rows - 1 || r == 0 || c == 0 || c == cols - 1) {
        // finished, so just reconstruct
        string moves;
        while (r != start.first || c != start.second) {
          moves += dirNames[parents[r][c]];
          auto [ri, ci] = dirs[parents[r][c]];
          r -= ri;
          c -= ci;
        }
        reverse(moves.begin(), moves.end());
        cout << "YES" << endl;
        cout << moves.size() << endl;
        cout << moves << endl;
        return 0;
      }
      // not done yet, just explore neighbors
      for (int i = 0; i < dirs.size(); ++i) {
        auto [ri, ci] = dirs[i];
        int rp = r + ri, cp = c + ci;
        if (0 <= rp && rp < rows && 0 <= cp && cp < cols &&
            grid[rp][cp] == '.' && parents[rp][cp] == -1) {
          parents[rp][cp] = i;
          nextPositions.push_back({rp, cp});
        }
      }
    }
    myPositions = nextPositions;
    // similar thing for monsters
    vector<pair<int, int>> nextMonsterPositions;
    for (auto [r, c] : monsterPositions) {
      for (auto [ri, ci] : dirs) {
        int rp = r + ri, cp = c + ci;
        if (0 <= rp && rp < rows && 0 <= cp && cp < cols &&
            grid[rp][cp] == '.') {
          nextMonsterPositions.push_back({rp, cp});
          grid[rp][cp] = 'M';
        }
      }
    }
    monsterPositions = nextMonsterPositions;
  }
  cout << "NO" << endl;
}