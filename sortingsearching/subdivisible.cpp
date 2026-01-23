#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ll n;
  cin >> n;
  vector<ll> nums(n);
  for (int i = 0; i < n; ++i) {
    cin >> nums[i];
  }

  // just count how many times each psum % n appears
  // since we need contiguous subarrays
  map<ll, ll> psumCounts;
  psumCounts[0] = 1;
  ll sum = 0;
  ll good = 0;
  for (int i = 0; i < n; ++i) {
    // make sure sum is positive
    sum = ((sum + nums[i]) % n + n) % n;
    good += psumCounts[sum];
    psumCounts[sum] += 1;
  }
  cout << good << endl;
}