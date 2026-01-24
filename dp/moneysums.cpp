#include <bits/stdc++.h>
using namespace std;

int main() {
  int n;
  cin >> n;
  vector<int> coins(n);
  for (int i = 0; i < n; ++i) {
    cin >> coins[i];
  }
  vector<bool> possible(n * 1000 + 1);
  possible[0] = true;
  for (int coin : coins) {
    for (int to = n * 1000; to >= coin; --to) {
      possible[to] = possible[to] || possible[to - coin];
    }
  }
  int numPossible = 0;
  for (int i = 1; i <= n * 1000; ++i) {
    numPossible += possible[i];
  }
  cout << numPossible << endl;
  for (int i = 1; i <= n * 1000; ++i) {
    if (possible[i]) {
      cout << i << " ";
    }
  }
  cout << endl;
}