#include <bits/stdc++.h>
using namespace std;
struct Segtree {
  vector<vector<int>> levels;
  Segtree(int n) {
    levels.push_back({});
    levels.back().resize(n, 1);
    while (levels.back().size() > 1) {
      vector<int> &b = levels.back();
      vector<int> next;
      for (size_t i = 0; i < b.size(); i += 2) {
        if (i + 1 < b.size()) {
          next.push_back(b[i] + b[i + 1]);
        } else {
          next.push_back(b[i]);
        }
      }
      levels.push_back(next);
    }
  }
  int get(int i) {
    int idx = 0;
    for (int level = levels.size() - 1; level >= 0; --level, idx *= 2) {
      if (levels[level][idx] <= i) {
        i -= levels[level][idx++];
      }
    }
    return idx / 2;
  }
  void erase(int i) {
    for (size_t level = 0; level < levels.size(); ++level, i /= 2) {
      levels[level][i]--;
    }
  }
};
int main() {
  // segtree stores # of elements in a side
  int n;
  cin >> n;
  vector<int> nums(n);
  for (int i = 0; i < n; ++i) {
    cin >> nums[i];
  }
  Segtree s(n);
  for (int i = 0; i < n; ++i) {
    int idx;
    cin >> idx;
    idx = s.get(idx - 1);
    cout << nums[idx] << ' ';
    s.erase(idx);
  }
  cout << endl;
}