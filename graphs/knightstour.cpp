#include <bits/stdc++.h>
using namespace std;

array<array<int, 8>, 8> grid;
const vector<pair<int, int>> dirs = {{2, -1}, {2, 1}, {-2, -1}, {-2, 1},
                                     {1, -2}, {1, 2}, {-1, -2}, {-1, 2}};

// naive backtracking doesn't work, but we can prune and try to do the ones w/
// the least options first
int options(int r, int c) {
  int total = 0;
  for (auto &[ri, ci] : dirs) {
    int rp = r + ri, cp = c + ci;
    total += 0 <= rp && rp < grid.size() && 0 <= cp && cp < grid[0].size() &&
             grid[rp][cp] == -1;
  }
  return total;
}
bool rec(int move, int r, int c) {
  grid[r][c] = move;
  bool res = move == 64;
  // figure out what we can move to next
  vector<tuple<int, int, int>> opts;
  for (auto &[ri, ci] : dirs) {
    int rp = r + ri, cp = c + ci;
    if (0 <= rp && rp < grid.size() && 0 <= cp && cp < grid[0].size() &&
        grid[rp][cp] == -1) {
      opts.push_back({options(rp, cp), rp, cp});
    }
  }
  sort(opts.begin(), opts.end());
  bool attempt = true;
  for (auto [opts, rp, cp] : opts) {
    res = res || (attempt && rec(move + 1, rp, cp));
    // if there's something that's trapped, we either take it or we fail
    attempt = attempt && opts != 0;
  }

  if (!res) {
    // clear out the grid
    grid[r][c] = -1;
  }
  return res;
}

int main() {
  int c, r;
  cin >> c >> r;
  for (int i = 0; i < grid.size(); ++i) {
    fill(grid[i].begin(), grid[i].end(), -1);
  }
  rec(1, --r, --c);
  for (auto &row : grid) {
    for (int move : row) {
      cout << move << ' ';
    }
    cout << endl;
  }
}