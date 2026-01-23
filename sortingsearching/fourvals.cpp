#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main() {
  ll n, target;
  cin >> n >> target;
  vector<ll> nums(n);
  for (int i = 0; i < n; ++i) {
    cin >> nums[i];
  }
  map<ll, pair<int, int>> numPairs;
  for (int i = 1; i <= n; ++i) {
    for (int j = i + 1; j <= n; ++j) {
      ll sum = nums[i - 1] + nums[j - 1];
      ll complement = target - sum;
      if (numPairs.count(complement)) {
        auto [a, b] = numPairs[complement];
        cout << a << " " << b << " " << i << " " << j << endl;
        return 0;
      }
    }
    // didn't work, so pair with things in the past
    for (int j = 1; j < i; ++j) {
      ll sum = nums[i - 1] + nums[j - 1];
      numPairs[sum] = {j, i};
    }
  }
  cout << "IMPOSSIBLE" << endl;
}