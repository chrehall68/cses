#pragma GCC optimize("O3", "unroll-loops")
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
struct Segtree {
  vector<ll> stree;
  size_t n;
  size_t levels;
  Segtree(size_t n) {
    // find closest power of 2
    size_t pow2 = 1;
    levels = 1;
    while (pow2 <= n) {
      pow2 *= 2;
      ++levels;
    }
    this->n = pow2;
    // stree[0..pow2] = level0
    // stree[pow2..pow2 + pow2/2] = level1
    // stree[pow2 + pow2/2 .. pow2 + pow2/2 + pow2/4] = level2
    // ...
    // suppose pow2 = 8
    // [0..8] = level0
    // [8..12] = level1
    // [12..14] = level2
    // [14..15] = level3
    // so root would be at index 14
    // so we'll resize it so that root is the last element
    stree.resize(pow2 * 2 - 1);
  }
  ll query(int l, int r) {
    return queryHelper(l, r, levels - 1, stree.size() - 1, 0);
  }
  pair<int, int> range(int level, size_t levelIdx) {
    return {(1 << level) * levelIdx, (1 << level) * (levelIdx + 1) - 1};
  }
  ll queryHelper(int l, int r, int level, size_t levelStart, size_t levelIdx) {
    auto [myL, myR] = range(level, levelIdx);
    if (l <= myL && myR <= r) {
      return stree[levelStart + levelIdx];
    } else if (myR < l || r < myL) {
      return 0;
    } else {
      size_t nextLevelStart = levelStart - (1 << (levels - level));
      return queryHelper(l, r, level - 1, nextLevelStart, levelIdx * 2) +
             queryHelper(l, r, level - 1, nextLevelStart, levelIdx * 2 + 1);
    }
  }
  void inc(int idx, ll val) {
    for (size_t level = 0, levelStart = 0; level < levels;
         levelStart += 1 << (levels - ++level), idx /= 2) {
      stree[levelStart + idx] += val;
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
  // since each time we need to check if it increases, the cur mex
  // either stays the same (it's finished), or it at least doubles
  // and each time we just need to calculate the sum of everything <= MEX
  // the problem is, that gives us O(NlgN + Q (lg**2(N)) lg MEX)
  // which is O(NlgN + Q lg**3 (N))
  // that will TLE, though since Q lg**3 (N) is a lot
  // to improve that, instead of handling online and then bsearching over
  // lgN intervals lgMEX times, maybe we can handle the queries offline
  // we can add things in sorted order
  // and then do their queries when the next element that we would've
  // enabled is greater than next mex
  // since then we need to do O(lgMEX) segtree queries for each query
  // and we need to keep the queries in order
  // and our segtree just needs the sums now, making queries faster
  // so we get O(NlgN + Q lgQ lgMEX + Q lgMEX lgN)
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int n, q;
  cin >> n >> q;
  vector<pair<ll, int>> nums(n + 1);
  Segtree s(n + 1);
  for (int i = 0; i < n; ++i) {
    ll num;
    cin >> num;
    nums[i] = {num, i};
  }
  nums[n] = {numeric_limits<ll>::max(), n};
  sort(nums.begin(), nums.end());
  // want to be able to access the thing with the minimum mex
  priority_queue<tuple<ll, int, int, int>, vector<tuple<ll, int, int, int>>,
                 greater<>>
      queries;
  for (int i = 0; i < q; ++i) {
    int l, r;
    cin >> l >> r;
    queries.push({0, --l, --r, i});
  }
  // handle offline
  vector<ll> res(q);
  size_t l = 0;
  while (l < nums.size()) {
    // go to end
    ll num = nums[l].first;
    size_t r = l + 1;
    while (r < nums.size() && nums[r].first == nums[l].first) {
      r++;
    }

    // some things might not be able to use this
    while (!queries.empty() && get<0>(queries.top()) + 1 < num) {
      auto [prevMex, l, r, resIdx] = queries.top();
      queries.pop();

      ll curMex = s.query(l, r);
      if (curMex + 1 < num) {
        // we are finished
        res[resIdx] = curMex + 1;
      } else {
        // still alive
        queries.push({curMex, l, r, resIdx});
      }
    }

    // enable new things
    while (l < r) {
      s.inc(nums[l++].second, num);
    }
  }
  // then output
  for (ll num : res) {
    cout << num << '\n';
  }
}