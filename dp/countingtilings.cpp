#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll C = 1e9 + 7;

int main() {
  int rows, cols;
  cin >> rows >> cols;
  // need the history of the previous n things
  // each could be filled (1) or not filled (0)
  // so we need 2**n spaces
  int limit = 1 << rows;
  vector<ll> ways(limit, 0);
  ways[limit - 1] = 1; // 1 way; starts w/ everything full
  vector<ll> nextLevel(limit, 0);

  for (int i = 0; i < rows * cols; ++i) {
    int row = i % rows;
    fill(nextLevel.begin(), nextLevel.end(), 0);
    for (int prevN = 0; prevN < limit; ++prevN) {
      // we either place a 1 row x 2 col (fills left)
      // or a 2 rows x 1 col (fills above)
      // and we must not leave the left empty
      // or place nothing (let later thing fill this)
      // see if we can place the left one
      if ((prevN & 1) == 0) {
        // the last thing is free, so we can fill it
        nextLevel[(prevN >> 1) | (1 << (rows - 1))] += ways[prevN];
        nextLevel[(prevN >> 1) | (1 << (rows - 1))] %= C;
      } else {
        // it's ok to place something or nothing
        // since the left is already filled (so we're not leaving anything
        // empty) see if we can place above
        if (row > 0 && (prevN & (1 << (rows - 1))) == 0) {
          // above is empty, so we can fill it
          nextLevel[(prevN >> 1) | (3 << (rows - 2))] += ways[prevN];
          nextLevel[(prevN >> 1) | (3 << (rows - 2))] %= C;
        }
        // and we can also just leave it empty
        nextLevel[(prevN >> 1)] += ways[prevN];
        nextLevel[(prevN >> 1)] %= C;
      }
    }
    swap(nextLevel, ways);
  }
  cout << ways[limit - 1] << endl;
}