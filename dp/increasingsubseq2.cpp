#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll C = 1e9 + 7;

class Segtree {
  // levels[level][level_idx] = {min_in_interval,max_in_interval interval_sum}
  vector<vector<tuple<ll, ll, ll>>> levels;
  map<ll, int> indices;

public:
  Segtree(vector<ll> nums) {
    sort(nums.begin(), nums.end());
    vector<tuple<ll, ll, ll>> firstLevel;
    for (ll num : nums) {
      if (firstLevel.empty() || get<0>(firstLevel.back()) != num) {
        firstLevel.push_back({num, num, 0});
      }
    }
    for (int i = 0; i < firstLevel.size(); ++i) {
      indices[get<0>(firstLevel[i])] = i;
    }
    levels.push_back(firstLevel);
    while (levels.back().size() > 1) {
      vector<tuple<ll, ll, ll>> nextLevel;
      for (int i = 0; i < levels.back().size(); i += 2) {
        if (i + 1 < levels.back().size()) {
          nextLevel.push_back(
              {get<0>(levels.back()[i]), get<1>(levels.back()[i + 1]),
               get<2>(levels.back()[i]) + get<2>(levels.back()[i + 1])});
        } else {
          nextLevel.push_back(levels.back()[i]);
        }
      }
      levels.push_back(nextLevel);
    }
  }

  ll numLt(ll num) { return numLtHelper(num, levels.size() - 1, 0); }
  void update(ll num, ll amt) {
    ll levelIdx = indices[num];
    ll level = 0;
    while (level < levels.size()) {
      get<2>(levels[level][levelIdx]) += amt;
      get<2>(levels[level][levelIdx]) %= C;
      level += 1;
      levelIdx /= 2;
    }
  }

private:
  ll numLtHelper(ll num, ll level, ll levelIdx) {
    auto [mi, ma, amt] = levels[level][levelIdx];
    if (mi >= num) {
      return 0;
    } else if (ma < num) {
      return amt;
    } else {
      // partial intercept
      // ask left first
      ll leftAmt = numLtHelper(num, level - 1, levelIdx * 2);
      ll rightAmt = 0;
      if (levelIdx * 2 + 1 < levels[level - 1].size()) {
        rightAmt = numLtHelper(num, level - 1, levelIdx * 2 + 1);
      }
      return (leftAmt + rightAmt) % C;
    }
  }
};

int main() {
  int n;
  cin >> n;
  vector<ll> nums(n);
  for (int i = 0; i < n; ++i) {
    cin >> nums[i];
  }

  // so we're interested in how many increasing subsequences there are
  // we can reduce this to how any subsequences end with x
  // then we can, for y, calculate how many subsequences end with y
  // by just summing up the # of subsequences that end w/ x < y
  // we could do that with a segtree
  // but we might be able to do this w/ less implementation
  // maybe monotonic map works?
  // if we sort first, then do a monotonic map on the indices
  // and when we pop, we have to increase
  // hmm maybe actually a monotonic stack works too if we're going left to right
  // yeah since when we're going left to right, and we have some number
  // actually nvm
  // yeah so maybe we do just do the monotonic map
  // nvm that doesn't work; just use segtree
  Segtree root(nums);
  ll total = 0;
  for (ll num : nums) {
    ll amt = root.numLt(num) + 1;
    total += amt;
    total %= C;
    root.update(num, amt);
  }
  cout << total << endl;
}