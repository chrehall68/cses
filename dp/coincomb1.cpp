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
  for (int from = 0; from < x; ++from) {
    for (int coin : coins) {
      if (from + coin <= x) {
        ways[from + coin] += ways[from];
        ways[from + coin] %= C;
      }
    }
  }
  cout << ways[x] << endl;
}