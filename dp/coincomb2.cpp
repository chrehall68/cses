#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const ll C = 1e9 + 7;
int main() {
  int n, x;
  cin >> n >> x;
  vector<int> coins(n);
  for (int i = 0; i < n; ++i) {
    cin >> coins[i];
  }
  vector<ll> ways(x + 1, 0);
  ways[0] = 1;
  for (int coin : coins) {
    for (int to = coin; to <= x; ++to) {
      ways[to] += ways[to - coin];
      ways[to] %= C;
    }
  }
  cout << ways[x] << endl;
}