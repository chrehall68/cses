#include <algorithm>
#include <bits/stdc++.h>
#include <numeric>
using namespace std;
using ll = long long;
int main() {
  int n;
  cin >> n;
  vector<ll> times(n);
  for (int i = 0; i < n; ++i) {
    cin >> times[i];
  }

  // see whether dominated by one or not
  ll sum = accumulate(times.begin(), times.end(), 0LL);
  ll ma = *max_element(times.begin(), times.end());
  if (ma > sum - ma) {
    // dominated by single
    cout << ma * 2 << endl;
  } else {
    cout << sum << endl;
  }
}