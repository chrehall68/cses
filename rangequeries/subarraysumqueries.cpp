#include <bits/stdc++.h>
using namespace std;
using ll = long long;
struct Info {
  ll sum;
  ll best; // not necessarily from this one
  ll maxPrefix;
  ll maxSuffix;
  Info(ll a, ll b, ll c, ll d) : sum(a), best(b), maxPrefix(c), maxSuffix(d) {}
  Info(ll num) : Info(num, max(num, 0LL), max(num, 0LL), max(num, 0LL)) {}
};
struct Segtree {
  vector<vector<Info>> levels;
  size_t n;
  Info combine(Info l, Info r) {
    ll nextSum = l.sum + r.sum;
    ll nextBest = max(l.best, r.best);
    // or combine
    nextBest = max(nextBest, l.maxSuffix + r.maxPrefix);
    // update max prefix
    ll maxPrefix = max(l.maxPrefix, l.sum + r.maxPrefix);
    ll maxSuffix = max(r.maxSuffix, l.maxSuffix + r.sum);
    return {nextSum, nextBest, maxPrefix, maxSuffix};
  }
  Segtree(vector<ll> nums) : n(nums.size()) {
    levels.push_back({});
    for (ll num : nums) {
      levels.back().push_back(Info{num});
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
  ll best() { return levels.back()[0].best; }
  void update(size_t idx, ll newVal) {
    levels[0][idx] = Info{newVal};
    idx /= 2;
    for (size_t level = 1; level < levels.size(); ++level, idx /= 2) {
      if (idx * 2 + 1 < levels[level - 1].size()) {
        levels[level][idx] =
            combine(levels[level - 1][idx * 2], levels[level - 1][idx * 2 + 1]);
      } else {
        levels[level][idx] = levels[level - 1][idx * 2];
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
  vector<ll> nums(n);
  for (int i = 0; i < n; ++i) {
    cin >> nums[i];
  }
  Segtree s(nums);
  for (int i = 0; i < q; ++i) {
    int a, b;
    cin >> a >> b;
    s.update(--a, b);
    cout << s.best() << '\n';
  }
}