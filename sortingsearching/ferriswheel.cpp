#include <bits/stdc++.h>
using namespace std;

int main() {
  int n, x;
  cin >> n >> x;
  vector<int> nums(n);
  for (int i = 0; i < n; ++i) {
    cin >> nums[i];
  }
  sort(nums.begin(), nums.end());
  int needed = 0;
  int lower = 0;
  for (int i = n - 1; i >= lower; --i) {
    if (nums[i] + nums[lower] <= x) {
      lower++;
    }
    needed++;
  }
  cout << needed << endl;
}