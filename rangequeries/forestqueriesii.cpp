#include <bits/stdc++.h>
using namespace std;

template <typename T> struct Segtree {
  vector<vector<T>> levels;
  size_t n;
  template <typename C> Segtree(vector<T> init, C &&combine) : n(init.size()) {
    levels.push_back(init);
    while (levels.back().size() > 1) {
      vector<T> &b = levels.back();
      vector<T> nextLevel;
      for (size_t i = 0; i < b.size(); i += 2) {
        if (i + 1 < b.size()) {
          nextLevel.push_back(combine(b[i], b[i + 1]));
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
  template <typename R, typename F, typename C>
  R query(int l, int r, F &&f, R defaultVal, C &&combiner) {
    return queryHelper(l, r, f, defaultVal, combiner, levels.size() - 1, 0);
  }
  template <typename R, typename F, typename C>
  R queryHelper(int l, int r, F &&f, R defaultVal, C &&combiner, int level,
                size_t levelIdx) {
    if (levelIdx >= levels[level].size()) {
      return defaultVal;
    }
    auto [myL, myR] = range(level, levelIdx);
    if (l <= myL && myR <= r) {
      return f(levels[level][levelIdx]);
    } else if (myR < l || r < myL) {
      return defaultVal;
    } else {
      return combiner(
          queryHelper(l, r, f, defaultVal, combiner, level - 1, levelIdx * 2),
          queryHelper(l, r, f, defaultVal, combiner, level - 1,
                      levelIdx * 2 + 1));
    }
  }
  template <typename U> void update(int idx, U &&updater) {
    for (size_t level = 0; level < levels.size(); ++level, idx /= 2) {
      updater(levels[level][idx]);
    }
  }
};

int intCombine(int a, int b) { return a + b; }
Segtree<int> sTreeCombine(Segtree<int> &a, Segtree<int> &b) {
  vector<int> init = a.levels[0];
  for (size_t i = 0; i < init.size(); ++i) {
    init[i] += b.levels[0][i];
  }
  return Segtree<int>{init, intCombine};
}
int ident(int a) { return a; }

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int n, q;
  cin >> n >> q;
  vector<string> grid(n);
  for (int r = 0; r < n; ++r) {
    cin >> grid[r];
  }
  vector<Segtree<int>> init;
  for (int r = 0; r < n; ++r) {
    vector<int> sInit(n);
    for (int c = 0; c < n; ++c) {
      sInit[c] = grid[r][c] == '*';
    }
    init.push_back(Segtree<int>(sInit, intCombine));
  }
  Segtree<Segtree<int>> s(init, sTreeCombine);
  for (int i = 0; i < q; ++i) {
    int op;
    cin >> op;
    if (op == 2) {
      int y1, x1, y2, x2;
      cin >> y1 >> x1 >> y2 >> x2;
      cout << s.query(
                  --y1, --y2,
                  [&](Segtree<int> &st) {
                    return st.query(x1 - 1, x2 - 1, ident, 0, intCombine);
                  },
                  0, intCombine)
           << '\n';
    } else {
      int y, x;
      cin >> y >> x;
      int inc;
      if (grid[--y][--x] == '*') {
        grid[y][x] = '.';
        inc = -1;
      } else {
        grid[y][x] = '*';
        inc = 1;
      }

      auto incrementer = [&](int &r) { r += inc; };
      s.update(y, [&](Segtree<int> &st) { st.update(x, incrementer); });
    }
  }
}