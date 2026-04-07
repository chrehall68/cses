#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Segtree {
  // levels stores extras
  vector<vector<ll>> levels;
  int n;
  Segtree(vector<ll> nums) : n(nums.size()) {
    levels.push_back(nums);
    while (levels.back().size() > 1) {
      vector<ll> next((levels.back().size() + 1) / 2);
      levels.push_back(next);
    }
  }
  pair<int, int> range(int level, int levelIdx) {
    return {(1 << level) * levelIdx, min((1 << level) * (levelIdx + 1), n) - 1};
  }
  void update(int l, int r, ll amt) {
    updateHelper(l, r, amt, levels.size() - 1, 0);
  }
  void updateHelper(int l, int r, ll amt, int level, int levelIdx) {
    if (levelIdx >= levels[level].size()) {
      return;
    }
    auto [myL, myR] = range(level, levelIdx);
    if (l <= myL && myR <= r) {
      levels[level][levelIdx] += amt;
    } else if (myR < l || r < myL) {
      return;
    } else {
      updateHelper(l, r, amt, level - 1, levelIdx * 2);
      updateHelper(l, r, amt, level - 1, levelIdx * 2 + 1);
    }
  }
  ll value(int i) {
    ll res = 0;
    int idx = 0;
    for (int level = levels.size() - 1; level >= 0; --level, idx *= 2) {
      auto [l, r] = range(level, idx);
      if (!(l <= i && i <= r)) {
        idx++;
      }
      res += levels[level][idx];
    }
    return res;
  }
};
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int n, q;
  cin >> n >> q;
  vector<ll> nums(n);
  for (int i = 0; i < n; ++i) {
    cin >> nums[i];
  }
  Segtree s(nums);
  for (int i = 0; i < q; ++i) {
    int op;
    cin >> op;
    if (op == 1) {
      int a, b, c;
      cin >> a >> b >> c;
      s.update(--a, --b, c);
    } else {
      int a;
      cin >> a;
      cout << s.value(--a) << '\n';
    }
  }
}