#include <bits/stdc++.h>
using namespace std;
struct Segtree {
  vector<vector<int>> levels;
  size_t n;
  Segtree(int n) : n(n) {
    levels.push_back(vector<int>(n));
    while (levels.back().size() > 1) {
      levels.push_back(vector<int>((levels.back().size() + 1) / 2));
    }
  }
  void enable(int idx) {
    for (size_t level = 0; level < levels.size(); ++level, idx /= 2) {
      levels[level][idx]++;
    }
  }
  int sum(int l, int r) { return sumHelper(l, r, levels.size() - 1, 0); }
  int sumHelper(int l, int r, int level, size_t levelIdx) {
    if (levelIdx >= levels[level].size()) {
      return 0;
    }
    int myL = (1 << level) * levelIdx;
    int myR = min((1 << level) * (levelIdx + 1), n) - 1;
    if (l <= myL && myR <= r) {
      return levels[level][levelIdx];
    } else if (myR < l || r < myL) {
      return 0;
    } else {
      return sumHelper(l, r, level - 1, levelIdx * 2) +
             sumHelper(l, r, level - 1, levelIdx * 2 + 1);
    }
  }
};
int main() {
  // we could answer the queries online with a mergetree
  // by breaking each query into "how many numbers are <= d" in [a,b]
  // minus "how many numbers are <= c" in [a,b]
  // to get us N + Q log**2(N)
  // but we can answer them offline for N log N + Q log Q + Q log N
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int n, q;
  cin >> n >> q;
  vector<pair<int, int>> nums(n);
  for (int i = 0; i < n; ++i) {
    cin >> nums[i].first;
    nums[i].second = i;
  }
  sort(nums.begin(), nums.end());
  // {leNum, a, b, resIdx, wasUpper}
  vector<tuple<int, int, int, int, bool>> qs;
  for (int i = 0; i < q; ++i) {
    int a, b, c, d;
    cin >> a >> b >> c >> d;
    qs.push_back({c - 1, a, b, i, false});
    qs.push_back({d, a, b, i, true});
  }
  sort(qs.begin(), qs.end());
  Segtree s(n);
  vector<int> res(q);
  int numIdx = 0;
  for (auto [leNum, a, b, resIdx, wasUpper] : qs) {
    while (numIdx < n && nums[numIdx].first <= leNum) {
      s.enable(nums[numIdx++].second);
    }
    int amt = s.sum(--a, --b);
    if (wasUpper) {
      res[resIdx] += amt;
    } else {
      res[resIdx] -= amt;
    }
  }
  for (int num : res) {
    cout << num << '\n';
  }
}