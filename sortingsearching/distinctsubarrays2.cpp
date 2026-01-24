#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  // so basically once we know the largest subarray starting
  // at index i w/ <= k distinct values, we know that every
  // prefix of that is also a subarray starting at index i
  // w/ <= k distinct values
  // if we can count that for all indices i, we have our result
  // we can use a segtree
  // can we do it any differently?
  // yes; we can just sliding window this, keeping track of the counts of each
  // number
  int n, k;
  cin >> n >> k;
  vector<int> nums(n);
  for (int i = 0; i < n; ++i) {
    cin >> nums[i];
  }
  map<int, int> numCounts;
  int right = 0; // exclusive
  ll good = 0;
  for (int i = 0; i < n; ++i) {
    if (i > 0) {
      // remove the previous
      numCounts[nums[i - 1]] -= 1;
      if (numCounts[nums[i - 1]] == 0) {
        numCounts.erase(nums[i - 1]);
      }
    }
    // move right forward as much as possible
    while (right < n &&
           (numCounts.size() < k ||
            (numCounts.size() == k && numCounts.count(nums[right])))) {
      numCounts[nums[right++]] += 1;
    }
    good += right - i;
  }
  cout << good << endl;
}