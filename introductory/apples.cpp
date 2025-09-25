#include <bits/stdc++.h>
#include <random>
using namespace std;
long long bestDifference(vector<int> &weights, int idx, long long aboveDif) {
  if (idx >= weights.size()) {
    return abs(aboveDif);
  }
  // recursive case, either add or subtract this
  // representing putting it on a or b
  return min(bestDifference(weights, idx + 1, aboveDif + weights[idx]),
             bestDifference(weights, idx + 1, aboveDif - weights[idx]));
}
int main() {
  int n;
  cin >> n;
  vector<int> nums(n);
  for (int i = 0; i < n; ++i) {
    cin >> nums[i];
  }
  cout << bestDifference(nums, 0, 0) << endl;
}