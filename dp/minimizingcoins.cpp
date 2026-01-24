#include <bits/stdc++.h>
using namespace std;

int main() {
  int n, x;
  cin >> n >> x;
  vector<int> coins(n);
  for (int i = 0; i < n; ++i) {
    cin >> coins[i];
  }
  vector<int> minWays(x + 1, 1e7);
  minWays[0] = 0;
  for (int from = 0; from < x; ++from) {
    for (int coin : coins) {
      if (from + coin <= x) {
        minWays[from + coin] = min(minWays[from + coin], minWays[from] + 1);
      }
    }
  }
  if (minWays[x] == 1e7) {
    cout << -1 << endl;
  } else {
    cout << minWays[x] << endl;
  }
}