#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// stores maxes
struct Info {
  ll max;
  ll inc;
};
struct Segtree {
  vector<vector<Info>> levels;
  int n;
  Segtree(vector<ll> init) : n(init.size()) {
    levels.push_back({});
    for (ll i : init) {
      levels.back().push_back({i, 0});
    }
    while (levels.back().size() > 1) {
      vector<Info> &b = levels.back();
      vector<Info> next;
      for (size_t i = 0; i < b.size(); i += 2) {
        if (i + 1 < b.size()) {
          next.push_back({max(b[i].max, b[i + 1].max), 0});
        } else {
          next.push_back(b[i]);
        }
      }
      levels.push_back(next);
    }
  }
  pair<int, int> range(int level, size_t levelIdx) {
    return {(1 << level) * levelIdx,
            min((1 << level) * (int)(levelIdx + 1), n) - 1};
  }
  void update(int l, ll amt) { updateHelper(l, amt, levels.size() - 1, 0); }
  ll updateHelper(int l, ll amt, int level, size_t levelIdx) {
    if (levelIdx >= levels[level].size()) {
      return numeric_limits<ll>::min();
    }
    auto [myL, myR] = range(level, levelIdx);
    if (l <= myL) {
      // everything gets incremented
      levels[level][levelIdx].inc += amt;
    } else if (myR >= l) {
      levels[level][levelIdx].max =
          max(updateHelper(l, amt, level - 1, levelIdx * 2),
              updateHelper(l, amt, level - 1, levelIdx * 2 + 1));
    }
    return levels[level][levelIdx].inc + levels[level][levelIdx].max;
  }
  ll maxOf(int l, int r) { return maxHelper(l, r, levels.size() - 1, 0); }
  ll maxHelper(int l, int r, int level, size_t levelIdx) {
    if (levelIdx >= levels[level].size()) {
      return numeric_limits<ll>::min();
    }
    auto [myL, myR] = range(level, levelIdx);
    if (l <= myL && myR <= r) {
      return levels[level][levelIdx].inc + levels[level][levelIdx].max;
    } else if (myR < l || r < myL) {
      return numeric_limits<ll>::min();
    } else {
      return max(maxHelper(l, r, level - 1, levelIdx * 2),
                 maxHelper(l, r, level - 1, levelIdx * 2 + 1)) +
             levels[level][levelIdx].inc;
    }
  }
};
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int n, q;
  cin >> n >> q;
  vector<ll> psums(n + 1);
  vector<ll> nums(n);
  for (int i = 0; i < n; ++i) {
    cin >> nums[i];
    psums[i + 1] = psums[i] + nums[i];
  }
  Segtree s(psums);
  for (int i = 0; i < q; ++i) {
    int op, a, b;
    cin >> op >> a >> b;
    if (op == 2) {
      a--;
      cout << s.maxOf(a, b) - s.maxOf(a, a) << '\n';
    } else {
      ll amt = b - nums[--a];
      nums[a] = b;
      s.update(++a, amt);
    }
  }
}