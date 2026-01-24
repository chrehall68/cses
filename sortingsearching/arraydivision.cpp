#include <bits/stdc++.h>
#include <cassert>
#include <limits>
using namespace std;

using ll = long long;
ll splitsNecessary(ll maxSum, vector<ll> &nums) {
  ll necessary = 1;
  ll curSum = 0;
  for (int i = 0; i < nums.size(); ++i) {
    if (curSum + nums[i] > maxSum) {
      if (nums[i] > maxSum) {
        return numeric_limits<ll>::max();
      }
      curSum = nums[i];
      necessary += 1;
    } else {
      curSum += nums[i];
    }
  }
  return necessary;
}
int main() {
  ll n, k;
  cin >> n >> k;
  vector<ll> nums(n);
  for (int i = 0; i < n; ++i) {
    cin >> nums[i];
  }

  // we can just bsearch
  ll low = 1;
  ll high = 1e15;
  ll best = -1;
  while (low <= high) {
    ll mid = low + (high - low) / 2;
    if (splitsNecessary(mid, nums) <= k) {
      // works, try lower max sum
      best = mid;
      high = mid - 1;
    } else {
      low = mid + 1;
    }
  }
  assert(best != -1);
  cout << best << endl;
}