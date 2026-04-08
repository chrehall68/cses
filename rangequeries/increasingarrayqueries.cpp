#include <bits/stdc++.h>
using namespace std;
using ll = long long;
struct Info {
  ll inc;
  ll count;
  ll sum;
  Info(ll a, ll b, ll c) : inc(a), count(b), sum(c) {}
  Info(ll val) : Info(0, 1, val) {}
  ll total() const { return sum + inc * count; }
};
struct Segtree {
  vector<vector<Info>> levels;
  size_t n;
  Info combine(Info l, Info r) {
    return {0, l.count + r.count, l.total() + r.total()};
  }
  Segtree(vector<ll> init) : n(init.size()) {
    levels.push_back({});
    for (ll num : init) {
      levels.back().push_back(num);
    }
    while (levels.back().size() > 1) {
      vector<Info> &b = levels.back();
      vector<Info> next;
      for (size_t i = 0; i < b.size(); i += 2) {
        if (i + 1 < b.size()) {
          next.push_back(combine(b[i], b[i + 1]));
        } else {
          next.push_back(b[i]);
        }
      }
      levels.push_back(next);
    }
  }
  // need range increment and range sum
  pair<int, int> range(int level, size_t levelIdx) {
    return {(1 << level) * levelIdx, min((1 << level) * (levelIdx + 1), n) - 1};
  }
  void rangeInc(int l, int r, ll amt) {
    rIncHelper(l, r, amt, levels.size() - 1, 0);
  }
  void rIncHelper(int l, int r, ll amt, int level, size_t levelIdx) {
    if (levelIdx >= levels[level].size()) {
      return;
    }
    auto [myL, myR] = range(level, levelIdx);
    if (l <= myL && myR <= r) {
      levels[level][levelIdx].inc += amt;
    } else if (myR < l || r < myL) {
      return;
    } else {
      rIncHelper(l, r, amt, level - 1, levelIdx * 2);
      rIncHelper(l, r, amt, level - 1, levelIdx * 2 + 1);
      levels[level][levelIdx].sum =
          sumHelper(0, n, level - 1, levelIdx * 2) +
          sumHelper(0, n, level - 1, levelIdx * 2 + 1);
    }
  }
  ll sum(int l, int r) { return sumHelper(l, r, levels.size() - 1, 0); }
  ll sumHelper(int l, int r, int level, size_t levelIdx) {
    if (levelIdx >= levels[level].size()) {
      return 0;
    }
    auto [myL, myR] = range(level, levelIdx);
    if (l <= myL && myR <= r) {
      return levels[level][levelIdx].total();
    } else if (myR < l || r < myL) {
      return 0;
    } else {
      // push down inc to avoid counting how many are inside
      ll amt = levels[level][levelIdx].inc;
      rIncHelper(0, n, amt, level - 1, levelIdx * 2);
      rIncHelper(0, n, amt, level - 1, levelIdx * 2 + 1);
      levels[level][levelIdx].inc = 0;
      levels[level][levelIdx].sum =
          sumHelper(0, n, level - 1, levelIdx * 2) +
          sumHelper(0, n, level - 1, levelIdx * 2 + 1);
      return sumHelper(l, r, level - 1, levelIdx * 2) +
             sumHelper(l, r, level - 1, levelIdx * 2 + 1);
    }
  }
};
int main() {
  // process queries offline
  // by moving the start of the array forward
  // every element has some forward range in which it is the max
  // and the cost for that range is count(range)*max - sum(range)
  // as move start forward, will enable different things, and use the
  // segtree to decrease their cost
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int n, q;
  cin >> n >> q;
  n++;
  vector<ll> nums(n);
  for (int i = 0; i < n - 1; ++i) {
    cin >> nums[i];
  }
  nums[n - 1] = 1'000'000'000; // sentinel to simplify loop
  vector<ll> costs(n);
  vector<int> lastIdx(n);
  iota(lastIdx.begin(), lastIdx.end(), 0);
  vector<vector<int>> toEnable(n);
  // strictly decreasing stack
  vector<ll> sta;
  for (int i = 0; i < n; ++i) {
    while (!sta.empty() && nums[sta.back()] <= nums[i]) {
      lastIdx[sta.back()] = i - 1;
      sta.pop_back();
    }
    if (!sta.empty()) {
      toEnable[sta.back()].push_back(i);
    }
    sta.push_back(i);
    costs[i] = nums[sta[0]] - nums[i];
  }
  // process queries
  Segtree s(costs);
  vector<tuple<int, int, int>> qs;
  for (int i = 0; i < q; ++i) {
    int a, b;
    cin >> a >> b;
    qs.push_back({--a, --b, i});
  }
  sort(qs.begin(), qs.end());
  vector<ll> res(q);
  int start = 0;
  for (auto [l, r, resIdx] : qs) {
    while (start < l) {
      // move forward, and enable anything
      for (int enableIdx : toEnable[start]) {
        s.rangeInc(enableIdx, lastIdx[enableIdx],
                   nums[enableIdx] - nums[start]);
      }
      start++;
    }
    res[resIdx] = s.sum(l, r);
  }
  for (ll num : res) {
    cout << num << '\n';
  }
}