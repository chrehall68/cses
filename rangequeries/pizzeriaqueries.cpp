#include <bits/stdc++.h>
using namespace std;
using ll = long long;
struct Segtree {
  vector<vector<ll>> levels;
  int n;
  Segtree(vector<ll> init) : n(init.size()) {
    levels.push_back(init);
    while (levels.back().size() > 1) {
      vector<ll> &b = levels.back();
      vector<ll> next;
      for (size_t i = 0; i < b.size(); i += 2) {
        if (i + 1 < b.size()) {
          next.push_back(min(b[i], b[i + 1]));
        } else {
          next.push_back(b[i]);
        }
      }
      levels.push_back(next);
    }
  }
  pair<int, int> range(int level, int levelIdx) {
    return {(1 << level) * levelIdx, min((1 << level) * (levelIdx + 1), n) - 1};
  }
  ll minOf(int l, int r) { return minHelper(l, r, levels.size() - 1, 0); }
  ll minHelper(int l, int r, int level, size_t levelIdx) {
    if (levelIdx >= levels[level].size()) {
      return numeric_limits<ll>::max();
    }
    auto [myL, myR] = range(level, levelIdx);
    if (l <= myL && myR <= r) {
      return levels[level][levelIdx];
    } else if (myR < l || r < myL) {
      return numeric_limits<ll>::max();
    } else {
      return min(minHelper(l, r, level - 1, levelIdx * 2),
                 minHelper(l, r, level - 1, levelIdx * 2 + 1));
    }
  }
  void update(size_t idx, ll val) {
    levels[0][idx] = val;
    idx /= 2;
    for (size_t level = 1; level < levels.size(); ++level, idx /= 2) {
      levels[level][idx] = levels[level - 1][idx * 2];
      if (idx * 2 + 1 < levels[level - 1].size()) {
        levels[level][idx] =
            min(levels[level][idx], levels[level - 1][idx * 2 + 1]);
      }
    }
  }
};
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int n, q;
  cin >> n >> q;
  vector<ll> prices(n);
  // if place is on left, |place-x| = x-place -> x+(k-place)
  // if place is on right,|place-x| = place-x -> -x+(k+place)
  vector<ll> lefts(n), rights(n);
  for (int i = 0; i < n; ++i) {
    cin >> prices[i];
    lefts[i] = prices[i] - i;
    rights[i] = prices[i] + i;
  }
  Segtree ls = Segtree(lefts), rs = Segtree(rights);
  for (int i = 0; i < q; ++i) {
    int op;
    cin >> op;
    if (op == 1) {
      int k, x;
      cin >> k >> x;
      k--;
      ls.update(k, x - k);
      rs.update(k, x + k);
    } else {
      int k;
      cin >> k;
      --k;
      cout << min(k + ls.minOf(0, k), -k + rs.minOf(k, n)) << '\n';
    }
  }
}