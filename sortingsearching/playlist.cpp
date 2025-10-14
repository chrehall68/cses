#include <bits/stdc++.h>
using namespace std;
int main() {
  int n;
  cin >> n;
  vector<int> nums(n);
  for (int i = 0; i < n; ++i) {
    cin >> nums[i];
  }
  map<int, int> counts;
  bool hasDuplicate = false;
  int left = 0;
  int right = 0; // exclusive
  int best = 0;
  while (right <= n) {
    if (!hasDuplicate) {
      // move right forward
      best = max(best, right - left);
      if (right < n) {
        counts[nums[right]]++;
        if (counts[nums[right]] == 2) {
          hasDuplicate = true;
        }
      }
      right++;
    } else {
      // move left forward
      counts[nums[left]]--;
      if (counts[nums[left]] == 1) {
        hasDuplicate = false;
      }
      left++;
    }
  }
  cout << best << endl;
}