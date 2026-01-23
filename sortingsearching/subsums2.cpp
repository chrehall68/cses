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

  // just count how many times each psum appears
  // since we need contiguous subarrays
  map<ll, ll> psumCounts;
  psumCounts[0] = 1;
  ll sum = 0;
  ll good = 0;
  for (int i = 0; i < n; ++i) {
    sum += nums[i];
    good += psumCounts[sum - target];
    psumCounts[sum] += 1;
  }
  cout << good << endl;
}