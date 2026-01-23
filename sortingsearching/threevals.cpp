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
  map<ll, int> numToIndices;
  for (int i = 0; i < n; ++i) {
    // check if this number is usable
    for (int j = i + 1; j < n; ++j) {
      ll sum = nums[j] + nums[i];
      ll complement = target - sum;
      if (numToIndices.count(complement)) {
        cout << numToIndices[complement] + 1 << " " << j + 1 << " " << i + 1
             << endl;
        return 0;
      }
    }
    // not usable rn, so store its matches
    numToIndices[nums[i]] = i;
  }
  cout << "IMPOSSIBLE" << endl;
}