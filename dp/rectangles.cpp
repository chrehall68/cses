#include <bits/stdc++.h>
#include <limits>
using namespace std;

int main() {
  int width, height;
  cin >> width >> height;
  vector<vector<int>> minMoves(width,
                               vector<int>(height, numeric_limits<int>::max()));
  for (int w = 1; w <= width; ++w) {
    for (int h = 1; h <= height; ++h) {
      if (w == h) {
        // it's already a rectangle
        minMoves[w - 1][h - 1] = 0;
      } else {
        // not a rectangle, need a vertical or a horizontal cut

        for (int remainingH = 1; remainingH < h; ++remainingH) {
          minMoves[w - 1][h - 1] =
              min(minMoves[w - 1][h - 1],
                  minMoves[w - 1][remainingH - 1] +
                      minMoves[w - 1][h - remainingH - 1] + 1);
        }
        for (int remainingW = 1; remainingW < w; ++remainingW) {
          minMoves[w - 1][h - 1] =
              min(minMoves[w - 1][h - 1],
                  minMoves[remainingW - 1][h - 1] +
                      minMoves[w - remainingW - 1][h - 1] + 1);
        }
      }
    }
  }
  cout << minMoves[width - 1][height - 1] << endl;
}