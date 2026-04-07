#include <bits/stdc++.h>
using namespace std;
int main() {
  // psum[i][j] = sum of rows 0..i, cols 0..j
  int n, q;
  cin >> n >> q;
  vector<vector<int>> psum(n + 1, vector<int>(n + 1));
  for (int r = 0; r < n; ++r) {
    for (int c = 0; c < n; ++c) {
      char tree;
      cin >> tree;
      int val = tree == '*';
      psum[r + 1][c + 1] = psum[r][c + 1] + psum[r + 1][c] - psum[r][c] + val;
    }
  }
  for (int i = 0; i < q; ++i) {
    int y1, x1, y2, x2;
    cin >> y1 >> x1 >> y2 >> x2;
    // y1, x1 is topleft, and matrix goes down
    cout << psum[y2][x2] - psum[y1 - 1][x2] - psum[y2][x1 - 1] +
                psum[y1 - 1][x1 - 1]
         << '\n';
  }
}