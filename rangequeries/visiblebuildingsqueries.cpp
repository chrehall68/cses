#include <bits/stdc++.h>
using namespace std;
struct Segtree {
  vector<vector<int>> levels;
  int n;
  Segtree(int n) : n(n) {
    levels.push_back(vector<int>(n));
    while (levels.back().size() > 1) {
      levels.push_back(vector<int>((levels.back().size() + 1) / 2));
    }
  }
  void enable(int idx) {
    for (size_t level = 0; level < levels.size(); ++level, idx /= 2) {
      ++levels[level][idx];
    }
  }
  int sum(int l, int r) { return sumHelper(l, r, levels.size() - 1, 0); }
  int sumHelper(int l, int r, int level, size_t levelIdx) {
    if (levelIdx >= levels[level].size()) {
      return 0;
    }
    int myL = (1 << level) * levelIdx;
    int myR = min((1 << level) * (int)(levelIdx + 1), n) - 1;
    if (l <= myL && myR <= r) {
      return levels[level][levelIdx];
    } else if (myR < l || r < myL) {
      return 0;
    } else {
      return sumHelper(l, r, level - 1, levelIdx * 2) +
             sumHelper(l, r, level - 1, levelIdx * 2 + 1);
    }
  }
};
int main() {
  // for every building, store the closest ge index
  // then, when we have an [a,b] we just count
  // how many of those things have their closest ge index < a
  // log**2 solution
  // but, we can also just answer the queries offline by processing queries in
  // increasing order of a and just enabling things
  int n, q;
  cin >> n >> q;
  vector<vector<int>> attached(n + 1);
  stack<pair<int, int>> s; // (num, idx)
  s.push({1'000'000'000, -1});
  for (int i = 0; i < n; ++i) {
    int num;
    cin >> num;
    // find first ge
    while (s.top().first < num) {
      s.pop();
    }
    attached[s.top().second + 1].push_back(i);
    s.push({num, i});
  }
  vector<tuple<int, int, int>> qs(q);
  for (int i = 0; i < q; ++i) {
    int a, b;
    cin >> a >> b;
    qs[i] = {a, b, i};
  }
  sort(qs.begin(), qs.end());
  vector<int> res(q);
  int attachedIdx = 0;
  Segtree stree(n);
  for (auto [l, r, resIdx] : qs) {
    while (attachedIdx < l) {
      for (int toEnable : attached[attachedIdx]) {
        stree.enable(toEnable);
      }
      attachedIdx++;
    }
    res[resIdx] = stree.sum(--l, --r);
  }
  for (int num : res) {
    cout << num << '\n';
  }
}