#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Segtree {
  vector<vector<ll>> levels;
  int n;
  Segtree(vector<ll> init) : n(init.size()) {
    levels.push_back(init);
    while (levels.back().size() > 1) {
      vector<ll> next;
      vector<ll> &b = levels.back();
      for (int i = 0; i < b.size(); i += 2) {
        if (i + 1 < b.size()) {
          next.push_back(b[i] + b[i + 1]);
        } else {
          next.push_back(b[i]);
        }
      }
      levels.push_back(next);
    }
  }
  ll minOf(int l, int r) { return minHelper(l, r, levels.size() - 1, 0); }
  ll minHelper(int l, int r, int level, int levelIdx) {
    if (levelIdx >= levels[level].size()) {
      return 0;
    }
    int myL = (1 << level) * levelIdx;
    int myR = minOf((1 << level) * (levelIdx + 1), n) - 1;
    if (l <= myL && myR <= r) {
      return levels[level][levelIdx];
    } else if (myR < l || r < myL) {
      return 0;
    } else {
      return minHelper(l, r, level - 1, 2 * levelIdx) +
             minHelper(l, r, level - 1, 2 * levelIdx + 1);
    }
  }
  void update(int idx, ll newNum) {
    ll oldNum = levels[0][idx];
    for (int level = 0; level < levels.size(); ++level, idx /= 2) {
      levels[level][idx] += newNum - oldNum;
    }
  }
};
int main() {
  ios_base::sync_with_stdio(false);
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
      s.update(--a, b);
    } else {
      cout << s.minOf(--a, --b) << '\n';
    }
  }
}