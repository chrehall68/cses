#include <bits/stdc++.h>
using namespace std;
using ll = long long;
struct Info {
  ll cnt; // how many are in the interval
  ll initialTerm;
  ll mult;
  ll sum;

  ll total() const {
    // sum(i=0..cnt) { initialTerm+mult*i }
    // = initialTerm*cnt + mult*sum(i=0..cnt){i}
    // = initialTerm*cnt + mult*(cnt)(cnt-1)/2
    return sum + initialTerm * cnt + mult * cnt * (cnt - 1) / 2;
  }
  ll termX(ll x) const { return initialTerm + mult * x; }
  Info(ll s, ll c = 1) : cnt(c), initialTerm(0), mult(0), sum(s) {}
};
struct Segtree {
  vector<vector<Info>> levels;
  size_t n;
  Segtree(vector<ll> init) : n(init.size()) {
    levels.push_back({});
    for (ll num : init) {
      levels[0].push_back(num);
    }
    while (levels.back().size() > 1) {
      vector<Info> &b = levels.back();
      vector<Info> nextLevel;
      for (size_t i = 0; i < b.size(); i += 2) {
        if (i + 1 < b.size()) {
          nextLevel.push_back(
              Info{b[i].sum + b[i + 1].sum, b[i].cnt + b[i + 1].cnt});
        } else {
          nextLevel.push_back(b[i]);
        }
      }
      levels.push_back(nextLevel);
    }
  }
  pair<int, int> range(int level, size_t levelIdx) {
    return {(1 << level) * levelIdx, min((1 << level) * (levelIdx + 1), n) - 1};
  }
  ll query(int l, int r) { return queryHelper(l, r, levels.size() - 1, 0); }
  void inc(int l, int r) { incHelper(l, r, levels.size() - 1, 0); }
  void pushdown(int level, size_t levelIdx) {
    // go left
    Info &inf = levels[level][levelIdx];
    levels[level - 1][levelIdx * 2].initialTerm += inf.initialTerm;
    levels[level - 1][levelIdx * 2].mult += inf.mult;
    inf.sum = levels[level - 1][levelIdx * 2].total();
    // go right
    if (levelIdx * 2 + 1 < levels[level - 1].size()) {
      levels[level - 1][levelIdx * 2 + 1].initialTerm +=
          inf.termX(levels[level - 1][levelIdx * 2].cnt);
      levels[level - 1][levelIdx * 2 + 1].mult += inf.mult;
      inf.sum += levels[level - 1][levelIdx * 2 + 1].total();
    }
    inf.mult = 0;
    inf.initialTerm = 0;
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
  void incHelper(int l, int r, int level, size_t levelIdx) {
    if (levelIdx >= levels[level].size()) {
      return;
    }
    auto [myL, myR] = range(level, levelIdx);
    if (l <= myL && myR <= r) {
      levels[level][levelIdx].mult++;
      levels[level][levelIdx].initialTerm += myL - l + 1;
    } else if (!(myR < l || r < myL)) {
      pushdown(level, levelIdx);
      incHelper(l, r, level - 1, levelIdx * 2);
      incHelper(l, r, level - 1, levelIdx * 2 + 1);
      pushdown(level, levelIdx);
    }
  }
};
int main() {
  // increment range [a,b]
  // sum of range [a,b]
  // when incrementing, we need to know the distance to the source on the left
  // and how many things are in the interval
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
    int op, a, b;
    cin >> op >> a >> b;
    if (op == 1) {
      s.inc(--a, --b);
    } else {
      cout << s.query(--a, --b) << '\n';
    }
  }
}