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

  // we can 2 pointer this
  // since all numbers are positive
  ll sum = 0;
  ll left = 0;
  ll right = 0;
  ll good = 0;
  while (right <= n) {
    if (sum >= target) {
      // move left forward
      sum -= nums[left++];
    } else {
      // move right forward
      if (right < n) {
        sum += nums[right];
      }
      right++;
    }
    good += sum == target;
  }
  cout << good << endl;
}