#include <bits/stdc++.h>
using namespace std;
using ll = long long;
struct Info {
  vector<ll> nums;
  vector<ll> psums;
  Info(ll num) {
    nums.push_back(num);
    psums.push_back(0);
    psums.push_back(num);
  }
  Info(Info &a, Info &b) {
    nums.resize(a.nums.size() + b.nums.size());
    merge(a.nums.begin(), a.nums.end(), b.nums.begin(), b.nums.end(),
          nums.begin());
    psums.resize(nums.size() + 1);
    for (size_t i = 0; i < nums.size(); ++i) {
      psums[i + 1] = psums[i] + nums[i];
    }
  }
};
struct Segtree {
  vector<vector<Info>> levels;
  size_t n;
  Segtree(vector<ll> init) : n(init.size()) {
    levels.push_back({});
    for (size_t i = 0; i < init.size(); i++) {
      levels.back().push_back(Info(init[i]));
    }
    while (levels.back().size() > 1) {
      vector<Info> &b = levels.back();
      vector<Info> nextLevel;
      for (size_t i = 0; i < b.size(); i += 2) {
        if (i + 1 < b.size()) {
          nextLevel.push_back(Info(b[i], b[i + 1]));
        } else {
          nextLevel.push_back(b[i]);
        }
      }
      levels.push_back(std::move(nextLevel));
    }
  }
  vector<Info *> query(int l, int r) {
    vector<Info *> output;
    queryHelper(l, r, levels.size() - 1, 0, output);
    return output;
  }
  pair<int, int> range(int level, size_t levelIdx) {
    return {(1 << level) * levelIdx, min((1 << level) * (levelIdx + 1), n) - 1};
  }
  void queryHelper(int l, int r, int level, size_t levelIdx,
                   vector<Info *> &output) {
    if (levelIdx >= levels[level].size()) {
      return;
    }
    auto [myL, myR] = range(level, levelIdx);
    if (l <= myL && myR <= r) {
      output.push_back(&levels[level][levelIdx]);
    } else if (!(myR < l || r < myL)) {
      queryHelper(l, r, level - 1, levelIdx * 2, output);
      queryHelper(l, r, level - 1, levelIdx * 2 + 1, output);
    }
  }
};
int main() {
  // so maybe we could store the mex?
  // well once we can make all numbers up to x-1, then
  // we can use number x to increase the mex by x
  // prev mex = 0, cur num = 1 -> new mex = 1
  // prev mex = 1, cur num = 2 -> new mex = 3
  // prev mex = 3, cur num = 2 -> new mex = 5
  // so the mex would just be the sum of the numbers
  // but we have to be able to add the numbers
  // if the numbers were in sorted order, then we would know for sure that
  // if we can't add number a, we can't add any other numbers
  // but the problem with sorted order is how would we enable/disable things
  // so maybe we do need to have them in the original order
  // but then we want to be able to get the numbers in order
  // so maybe we have merge tree
  // and then just handle it increasing (it can only increase lg(MEX) times)
  // and each time we just need to calculate the sum of everything <= MEX
  // the problem is, that gives us O(NlgN + Q (lg**2(N)) lg MEX)
  // which is O(NlgN + Q lg**3 (N))
  // currently TLE's
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
  // sum of numbers <= le
  auto getSum = [&](vector<Info *> &v, ll le) {
    ll res = 0;
    for (Info *inf : v) {
      auto it = upper_bound(inf->nums.begin(), inf->nums.end(), le);
      res += inf->psums[it - inf->nums.begin()];
    }
    return res;
  };
  for (int i = 0; i < q; ++i) {
    int l, r;
    cin >> l >> r;
    vector<Info *> descriptor = s.query(--l, --r);
    ll mex = 0;
    ll prevSum = 0;
    ll nextSum = getSum(descriptor, mex + 1);
    while (nextSum != prevSum) {
      mex += nextSum - prevSum;
      prevSum = nextSum;
      nextSum = getSum(descriptor, mex + 1);
    }
    cout << mex + 1 << '\n';
  }
}