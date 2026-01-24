#include <algorithm>
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  int n;
  cin >> n;
  vector<ll> nums(n);
  for (int i = 0; i < n; ++i) {
    cin >> nums[i];
  }

  // now we just have a bunch of subarrays
  // maxScore[start][end] = {firstPlayer, secondPlayer}
  // start, end inclusive
  vector<vector<pair<ll, ll>>> maxScore(n, vector<pair<ll, ll>>(n));
  // handle length 1 subarrays
  for (int i = 0; i < n; ++i) {
    maxScore[i][i] = {nums[i], 0};
  }
  // maintain for length x subarrays
  for (int length = 2; length <= n; ++length) {
    for (int start = 0; start < n - length + 1; ++start) {
      int end = start + length - 1;
      // so now we either remove first or remove last
      // depending on which gives best results
      pair<ll, ll> first = {nums[start] + maxScore[start + 1][end].second,
                            maxScore[start + 1][end].first};
      pair<ll, ll> last = {nums[end] + maxScore[start][end - 1].second,
                           maxScore[start][end - 1].first};
      maxScore[start][end] = max(first, last);
    }
  }
  cout << maxScore[0][n - 1].first << endl;
}