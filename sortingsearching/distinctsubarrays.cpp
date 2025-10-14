#include <bits/stdc++.h>
using namespace std;

int main() {
  int n;
  cin >> n;
  vector<int> nums(n);
  for (int i = 0; i < n; ++i) {
    cin >> nums[i];
  }
  long long left = 0;
  long long right = 0;
  long long total = 0;
  map<int, int> counts;
  int lastDistinctEnd = -1; // inclusive
  while (right < n) {
    // go until not distinct
    while (right < n && counts[nums[right]] + 1 != 2) {
      counts[nums[right]]++;
      right++;
    }
    // right is now on the not distinct element
    // so we have a stretch from [left, right)
    long long count = right - left;
    long long subarrays = count * (count + 1) / 2;
    long long overlap = max(lastDistinctEnd - left + 1, 0LL);
    subarrays -= overlap * (overlap + 1) / 2;
    total += subarrays;
    lastDistinctEnd = right - 1;
    // move left forward until we decrease enough
    while (right < n && counts[nums[right]] == 1) {
      counts[nums[left]]--;
      left++;
    }
  }
  cout << total << endl;
}