#include <bits/stdc++.h>
#include <limits>
using namespace std;
using ll = long long;
int main() {
  ll n, a, b;
  cin >> n >> a >> b;
  vector<ll> nums(n);
  vector<ll> psums(n + 1, 0);
  for (int i = 0; i < n; ++i) {
    cin >> nums[i];
    psums[i + 1] = psums[i] + nums[i];
  }

  // so b is the maximum length
  // and a is the minimum length
  multiset<ll> availablePsums;
  for (int i = a; i <= b; ++i) {
    availablePsums.insert(psums[i]);
  }
  // now consider all starts
  ll best = numeric_limits<ll>::min();
  for (int i = 0; i < n - a + 1; ++i) {
    best = max(best, *(--availablePsums.end()) - psums[i]);
    // then advance
    // note that multiset erase erases ALL occurrences if provided a value
    // so we provide it an iterator so that it erases JUST one occurrence
    availablePsums.erase(availablePsums.find(psums[i + a]));
    if (i + b + 1 <= n) {
      availablePsums.insert(psums[i + b + 1]);
    }
  }
  cout << best << endl;
}