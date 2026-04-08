#include <bits/stdc++.h>
using namespace std;
// min segtree
struct Segtree {
  vector<vector<int>> levels;
  size_t n;
  Segtree(vector<int> init) : n(init.size()) {
    levels.push_back(init);
    while (levels.back().size() > 1) {
      vector<int> &b = levels.back();
      vector<int> next;
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
  void update(size_t idx, int val) {
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
  int minOf(int l, int r) { return helper(l, r, levels.size() - 1, 0); }
  int helper(int l, int r, int level, size_t levelIdx) {
    if (levelIdx >= levels[level].size()) {
      return numeric_limits<int>::max();
    }
    int myL = (1 << level) * levelIdx;
    int myR = min((1 << level) * (levelIdx + 1), n) - 1;
    if (l <= myL && myR <= r) {
      return levels[level][levelIdx];
    } else if (myR < l || r < myL) {
      return numeric_limits<int>::max();
    } else {
      return min(helper(l, r, level - 1, levelIdx * 2),
                 helper(l, r, level - 1, levelIdx * 2 + 1));
    }
  }
};

int main() {
  // log**2 solution is using a segment tree of ordered sets
  // can we offline? probably not?
  // if we look at what's the next index of this number
  // then, for all numbers in the range [a,b], their next index should be > b
  // meaning that min(next index) > b
  // and if min(next index) <= b, then for sure not all distinct
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int n, q;
  cin >> n >> q;
  vector<int> nums(n), nextOccurrences(n, n);
  set<pair<int, int>> occurrences;
  for (int i = 0; i < n; ++i) {
    cin >> nums[i];
    occurrences.insert({nums[i], i});
  }
  for (auto prev = occurrences.begin(), it = ++occurrences.begin();
       it != occurrences.end(); ++it, ++prev) {
    if (it->first == prev->first) {
      nextOccurrences[prev->second] = it->second;
    }
  }
  Segtree s(nextOccurrences);
  auto updateLink = [&](auto prev, auto cur) {
    if (cur != occurrences.end() && prev->first == cur->first) {
      s.update(prev->second, cur->second);
    } else {
      s.update(prev->second, n);
    }
  };
  // process queries
  for (int i = 0; i < q; ++i) {
    int op, a, b;
    cin >> op >> a >> b;
    if (op == 2) {
      cout << (s.minOf(--a, b - 1) > b - 1 ? "YES\n" : "NO\n");
    } else {
      auto it = occurrences.lower_bound({nums[--a], a});
      // properly link prev to next since we're removing it
      if (it != occurrences.begin()) {
        updateLink(prev(it), next(it));
      }
      occurrences.erase(it);
      // and insert / link new value
      nums[a] = b;
      occurrences.insert({nums[a], a});
      it = occurrences.lower_bound({nums[a], a});
      updateLink(it, next(it));
      if (it != occurrences.begin()) {
        updateLink(prev(it), it);
      }
    }
  }
}