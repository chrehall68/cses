#include <bits/stdc++.h>
using namespace std;
int main() {
  // player who removes the last stick wins the game
  int n, k;
  cin >> n >> k;
  vector<int> moves(k);
  for (int &p : moves) {
    cin >> p;
  }
  vector<bool> isWinning(n + 1);
  string res;
  for (int i = 1; i <= n; ++i) {
    for (int move : moves) {
      if (move <= i) {
        isWinning[i] = isWinning[i] || !isWinning[i - move];
      }
    }
    res.push_back(isWinning[i] ? 'W' : 'L');
  }
  cout << res << endl;
}