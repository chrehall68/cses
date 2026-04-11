#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  // if the start didn't change, we could just do greedy and find closest
  // corresponding end time w/ binary search
  // since start changes, maybe we can check if the next thing by end time can
  // be added
  // no that doesn't work
  // but we can do lifts based on "if i attend x movies, what's the minimum end
  // time" so sort by end time first? yeah so during lifts stage, we:
  // - sort all intervals by end time. that's our representative idx
  // - each lift will be calculated by, for each interval i, find the earliest
  // ending interval j that we can take if we take 2**k things at i and combine
  // to get the ending time for 2**k+1. The resulting ones should still be
  // sorted in order of their end time
  // Then to query, process queries offline in order by start time
  // disable things, always starting at the earliest ending interval
  // that has a start time >= offline q's start time
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int n, q;
  cin >> n >> q;
  vector<pair<int, int>> intervals(n);
  for (int i = 0; i < n; ++i) {
    cin >> intervals[i].first >> intervals[i].second;
  }
  sort(intervals.begin(), intervals.end(), [](auto &&a, auto &&b) {
    if (a.second == b.second) {
      return a.first < b.first;
    }
    return a.second < b.second;
  });
  // lifting stage
  // dp[i][k] = min ending time if take 2**k things, starting w/ the i'th
  vector<vector<int>> lifts(n), afters(n);
  for (int i = 0; i < n; ++i) {
    lifts[i].push_back({intervals[i].second});
  }
  // then lift
  const int TIMES = 20;
  for (size_t k = 0; k < TIMES; ++k) {
    // use the 2**k for the 2**k+1
    size_t r = 0;
    for (size_t l = 0; l < intervals.size(); ++l) {
      if (k < lifts[l].size()) {
        int end = lifts[l][k];
        while (r < intervals.size() && intervals[r].first < end) {
          r++;
        }
        if (r < intervals.size()) {
          afters[l].push_back(r);
          if (k < lifts[r].size()) {
            lifts[l].push_back(lifts[r][k]);
          }
        }
      }
    }
  }
  // now answer queries
  vector<tuple<int, int, int>> qs;
  for (int i = 0; i < q; ++i) {
    int a, b;
    cin >> a >> b;
    qs.push_back({a, b, i});
  }
  sort(qs.begin(), qs.end());
  vector<int> res(q);
  int l = 0;
  for (auto [a, b, resIdx] : qs) {
    // move forward to first ending interval whose start is >= a
    while (l < n && intervals[l].first < a) {
      l++;
    }
    // then lift
    int cur = l;
    int amt = 0;
    for (int k = TIMES - 1; k >= 0 && cur < n; --k) {
      if (k < lifts[cur].size() && lifts[cur][k] <= b) {
        // do that lift
        amt += 1 << k;
        if (k < afters[cur].size()) {
          cur = afters[cur][k];
        } else {
          cur = n;
        }
      }
    }
    res[resIdx] = amt;
  }
  for (int num : res) {
    cout << num << '\n';
  }
}