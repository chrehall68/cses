#include <bits/stdc++.h>
#include <sys/types.h>
using namespace std;
using ll = long long;

struct Info {
  ll inc;
  ll sum;
  ll count;
  optional<ll> setTo;
  Info(ll v) : inc(0), sum(v), count(1), setTo(nullopt) {}
  Info(ll sum, ll count) : inc(0), sum(sum), count(count), setTo(nullopt) {}
  ll total() {
    if (setTo) {
      return (*setTo + inc) * count;
    }
    return sum + inc * count;
  }
  void set(ll v) {
    setTo = v;
    inc = 0;
  }
};
struct Segtree {
  vector<vector<Info>> levels;
  size_t n;
  Segtree(vector<ll> init) : n(init.size()) {
    levels.push_back({});
    for (ll num : init) {
      levels.back().push_back(num);
    }
    while (levels.back().size() > 1) {
      vector<Info> &b = levels.back();
      vector<Info> nextLevel;
      for (size_t i = 0; i < b.size(); i += 2) {
        if (i + 1 < b.size()) {
          nextLevel.push_back(
              {b[i].sum + b[i + 1].sum, b[i].count + b[i + 1].count});
        } else {
          nextLevel.push_back(b[i]);
        }
      }
      levels.push_back(nextLevel);
    }
  }
  ll query(int l, int r) { return queryHelper(l, r, levels.size() - 1, 0); }
  pair<int, int> range(int level, size_t levelIdx) {
    return {(1 << level) * levelIdx, min((1 << level) * (levelIdx + 1), n) - 1};
  }

  ll queryHelper(int l, int r, int level, size_t levelIdx) {
    if (levelIdx >= levels[level].size()) {
      return 0;
    }
    auto [myL, myR] = range(level, levelIdx);
    if (l <= myL && myR <= r) {
      return levels[level][levelIdx].total();
    } else if (myR < l || r < myL) {
      return 0;
    } else {
      pushdown(level, levelIdx);
      return queryHelper(l, r, level - 1, levelIdx * 2) +
             queryHelper(l, r, level - 1, levelIdx * 2 + 1);
    }
  }
  void pushdown(int level, size_t levelIdx) {
    // pass down existing set first
    if (levels[level][levelIdx].setTo) {
      setHelper(0, n, *levels[level][levelIdx].setTo, level - 1, levelIdx * 2);
      setHelper(0, n, *levels[level][levelIdx].setTo, level - 1,
                levelIdx * 2 + 1);
      levels[level][levelIdx].setTo = nullopt;
    }
    // then pass down inc
    incHelper(0, n, levels[level][levelIdx].inc, level - 1, levelIdx * 2);
    incHelper(0, n, levels[level][levelIdx].inc, level - 1, levelIdx * 2 + 1);
    levels[level][levelIdx].inc = 0;
    // update my sum
    levels[level][levelIdx].sum = queryHelper(0, n, level - 1, levelIdx * 2);
    levels[level][levelIdx].sum +=
        queryHelper(0, n, level - 1, levelIdx * 2 + 1);
  }
  void set(int l, int r, ll amt) { setHelper(l, r, amt, levels.size() - 1, 0); }
  void inc(int l, int r, ll amt) { incHelper(l, r, amt, levels.size() - 1, 0); }
  void setHelper(int l, int r, ll amt, int level, size_t levelIdx) {
    if (levelIdx >= levels[level].size()) {
      return;
    }
    auto [myL, myR] = range(level, levelIdx);
    if (l <= myL && myR <= r) {
      levels[level][levelIdx].set(amt);
    } else if (!(myR < l || r < myL)) {
      pushdown(level, levelIdx);
      // then have children get set
      setHelper(l, r, amt, level - 1, levelIdx * 2);
      setHelper(l, r, amt, level - 1, levelIdx * 2 + 1);
      // and update sum
      pushdown(level, levelIdx);
    }
  }
  void incHelper(int l, int r, ll amt, int level, size_t levelIdx) {
    if (levelIdx >= levels[level].size()) {
      return;
    }
    auto [myL, myR] = range(level, levelIdx);
    if (l <= myL && myR <= r) {
      levels[level][levelIdx].inc += amt;
    } else if (!(myR < l || r < myL)) {
      pushdown(level, levelIdx);
      // inc children
      incHelper(l, r, amt, level - 1, levelIdx * 2);
      incHelper(l, r, amt, level - 1, levelIdx * 2 + 1);
      // update sum
      pushdown(level, levelIdx);
    }
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
      int l, r, amt;
      cin >> l >> r >> amt;
      s.inc(--l, --r, amt);
    } else if (op == 2) {
      int l, r, amt;
      cin >> l >> r >> amt;
      s.set(--l, --r, amt);
    } else {
      int l, r;
      cin >> l >> r;
      cout << s.query(--l, --r) << '\n';
    }
  }
}