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

  void inc(int idx, int amt) {
    for (size_t level = 0; level < levels.size(); ++level, idx /= 2) {
      levels[level][idx] += amt;
    }
  }
  int query(int l, int r) { return queryHelper(l, r, levels.size() - 1, 0); }
  int queryHelper(int l, int r, int level, size_t levelIdx) {
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
      return queryHelper(l, r, level - 1, levelIdx * 2) +
             queryHelper(l, r, level - 1, levelIdx * 2 + 1);
    }
  }
};
int main() {
  // log**2 solution with mergetree
  // but we can do better by processing offline
  // idea = enable only the first index of a number
  // and then just move the "start" of the array forward
  // so counting # of distinct is just counting # of enabled from start to end
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int n, q;
  cin >> n >> q;
  Segtree s(n + 1);
  vector<int> nums(n);
  vector<int> nextIdx(n, n);
  vector<bool> active(n, false);
  for (int i = 0; i < n; ++i) {
    cin >> nums[i];
  }
  map<int, int> lastIdx;
  for (int i = n - 1; i >= 0; --i) {
    if (lastIdx.count(nums[i])) {
      active[lastIdx[nums[i]]] = false;
      nextIdx[i] = lastIdx[nums[i]];
    }
    lastIdx[nums[i]] = i;
    active[i] = true;
  }
  for (int i = 0; i < n; ++i) {
    if (active[i]) {
      s.inc(i, 1);
    }
  }
  // process queries offline
  vector<tuple<int, int, int>> qs;
  for (int i = 0; i < q; ++i) {
    int a, b;
    cin >> a >> b;
    qs.push_back({--a, --b, i});
  }
  sort(qs.begin(), qs.end());
  vector<int> res(q);
  int leftIdx = 0;
  for (auto [a, b, resIdx] : qs) {
    while (leftIdx < a) {
      s.inc(nextIdx[leftIdx++], 1);
    }
    res[resIdx] = s.query(a, b);
  }
  for (int num : res) {
    cout << num << '\n';
  }
}