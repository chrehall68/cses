#include <bits/stdc++.h>
using namespace std;
using ld = long double;

int main() {
  // so expected number of empty squares =
  // P(1 empty) * 1 + P(2 empty) * 2 + P(3 empty) * 3 + ...
  // + P(63 empty) * 63 + P(64 empty) * 64
  // or alternatively E[X] =
  // 1*P(1,1 empty) + 1*P(1,2 empty) + ... + 1*P(1,8 empty)
  // + 1*P(2,1 empty) + ... + 1*P(2,8 empty)
  // + ... + 1*P(8,8 empty)
  // then despite these being correlated, because of linearity of
  // expectation, we can just sum up each of these values
  // find what's the probability that robot x is at (i,j) after k steps
  // then the probability that the square is empty is
  // prod (1-P(robot x is there))
  int k;
  cin >> k;

  vector<vector<ld>> pEmpty(8, vector<ld>(8, 1));
  vector<pair<int, int>> dirs = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
  for (int rStart = 0; rStart < 8; ++rStart) {
    for (int cStart = 0; cStart < 8; ++cStart) {
      // now simulate k times
      vector<vector<ld>> prev(8, vector<ld>(8));
      vector<vector<ld>> cur(8, vector<ld>(8));
      prev[rStart][cStart] = 1;
      for (int step = 1; step <= k; ++step) {
        for (int r = 0; r < 8; ++r) {
          for (int c = 0; c < 8; ++c) {
            int countable = 0;
            for (auto [ri, ci] : dirs) {
              int rp = r + ri, cp = c + ci;
              countable += 0 <= rp && rp < 8 && 0 <= cp && cp < 8;
            }
            for (auto [ri, ci] : dirs) {
              int rp = r + ri, cp = c + ci;
              if (0 <= rp && rp < 8 && 0 <= cp && cp < 8) {
                cur[rp][cp] += prev[r][c] / countable;
              }
            }
          }
        }
        // advance
        swap(prev, cur);
        for (int r = 0; r < 8; ++r) {
          fill(cur[r].begin(), cur[r].end(), 0);
        }
      }
      // now increment our final probs
      for (int r = 0; r < 8; ++r) {
        for (int c = 0; c < 8; ++c) {
          pEmpty[r][c] *= 1 - prev[r][c];
        }
      }
    }
  }
  // now sum up
  ld ex = 0;
  for (int r = 0; r < 8; ++r) {
    for (int c = 0; c < 8; ++c) {
      ex += pEmpty[r][c];
    }
  }
  cout << fixed << setprecision(6) << ex << endl;
}