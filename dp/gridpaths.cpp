#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll C = 1e9 + 7;
int main() {
  int n;
  cin >> n;
  vector<string> grid(n);
  for (int i = 0; i < n; ++i) {
    cin >> grid[i];
  }
  vector<vector<ll>> numWays(n, vector<ll>(n, 0));
  numWays[0][0] = grid[0][0] == '.';
  for (int r = 0; r < n; ++r) {
    for (int c = 0; c < n; ++c) {
      if (grid[r][c] == '.') {
        if (r > 0) {
          numWays[r][c] += numWays[r - 1][c];
        }
        if (c > 0) {
          numWays[r][c] += numWays[r][c - 1];
        }
        numWays[r][c] %= C;
      }
    }
  }
  cout << numWays[n - 1][n - 1] << endl;
}