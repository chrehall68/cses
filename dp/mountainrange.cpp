#include <algorithm>
#include <bits/stdc++.h>
#include <limits>
using namespace std;

int main() {
  int n;
  cin >> n;
  vector<int> nums(n);
  vector<int> indices(n);
  for (int i = 0; i < n; ++i) {
    cin >> nums[i];
    indices[i] = i;
  }

  // since stable_sort is stable, indices are sorted by num, then index
  auto cmp = [&nums](int a, int b) { return nums[a] < nums[b]; };
  stable_sort(indices.begin(), indices.end(), cmp);
  // now go in order
  // bests[i] = {amt, spanLeft, spanRight, num}
  vector<tuple<int, int, int, int>> bests(n, {0, numeric_limits<int>::max(),
                                              numeric_limits<int>::min(),
                                              numeric_limits<int>::min()});
  int best = 0;
  for (int originalIdx : indices) {
    // check left and check right
    int spanLeft = originalIdx;
    int spanRight = originalIdx;
    int reachable = 0;
    if (originalIdx > 0) {
      // don't overcount
      int inc = get<3>(bests[originalIdx - 1]) == nums[originalIdx];
      reachable = max(reachable, get<0>(bests[originalIdx - 1]) - inc);
      spanLeft = min(spanLeft, get<1>(bests[originalIdx - 1]));
    }
    if (originalIdx + 1 < n) {
      reachable = max(reachable, get<0>(bests[originalIdx + 1]));
      spanRight = max(spanRight, get<2>(bests[originalIdx + 1]));
    }
    best = max(best, reachable + 1);
    bests[spanLeft] = {reachable + 1, spanLeft, spanRight, nums[originalIdx]};
    bests[spanRight] = {reachable + 1, spanLeft, spanRight, nums[originalIdx]};
  }

  cout << best << endl;
}