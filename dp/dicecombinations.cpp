#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll C = 1e9 + 7;
int main() {
  int n;
  cin >> n;
  // initialization
  vector<ll> counts(6, 1);
  ll sum = 1; // only 1 way to roll a 1
  for (int i = 2; i <= 6; ++i) {
    counts[i - 1] = sum + 1; // +1 bc can roll this number
    sum += counts[i - 1];
  }
  // keep computing, but w/o the +1
  for (int i = 7; i <= n; ++i) {
    int idx = (i - 1) % 6;
    ll myWays = sum;
    sum = ((2 * sum - counts[idx]) % C + C) % C;
    counts[idx] = myWays;
  }
  cout << counts[(n - 1) % 6] << endl;
}