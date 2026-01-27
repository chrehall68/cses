#include <bits/stdc++.h>
#include <limits>
using namespace std;
using ll = long long;

int main() {
  ll n, x;
  cin >> n >> x;
  vector<ll> nums(n);
  for (int i = 0; i < n; ++i) {
    cin >> nums[i];
  }

  // for every position, go through every subset of the posterior
  // use that as the first group (if it's not over x)
  // and then optimally solve remaining
  // we know that we already have the optimal solution for it
  // hmmm actually we do need to have an optimal solution for it...
  // so after looking at the blog here: https://codeforces.com/blog/entry/111675
  // looks like we just consider using something last
  // if we're considering using something last, then that means we just care
  // about how many total trips the remaining subset used, as well as the total
  // weight of the last trip used
  int limit = 1 << n;
  // dp[subset] = {total trips, last weight}
  vector<pair<ll, ll>> dp(limit, {numeric_limits<ll>::max(), 0});
  dp[0] = {1, 0};
  for (int subset = 1; subset < limit; ++subset) {
    // try using any of the set bits as the last step
    for (int bit = 0; bit < n; ++bit) {
      int shifted = 1 << bit;
      if ((subset & shifted) != 0) {
        if (dp[subset ^ shifted].second + nums[bit] <= x) {
          // doesn't need a new trip
          dp[subset] =
              min(dp[subset], {dp[subset ^ shifted].first,
                               dp[subset ^ shifted].second + nums[bit]});
        } else {
          // needs a new trip
          dp[subset] =
              min(dp[subset], {dp[subset ^ shifted].first + 1, nums[bit]});
        }
      }
    }
  }
  cout << dp[limit - 1].first << endl;
}