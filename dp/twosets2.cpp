#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll C = 1e9 + 7;

int main() {
  ll n;
  cin >> n;
  ll sum = (n + 1) * n / 2;
  if (sum % 2 == 1) {
    cout << 0 << endl;
    return 0;
  }
  // otherwise we find how many ways to sum to sum/2
  ll goal = sum / 2;
  vector<ll> ways(goal + 1, 0);
  ways[0] = 1; // 1 way to make 0
  for (int i = 1; i < n; ++i) {
    for (int to = goal; to >= i; --to) {
      ways[to] += ways[to - i];
      ways[to] %= C;
    }
  }
  cout << ways[goal] << endl;
}