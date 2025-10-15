#include <bits/stdc++.h>
using namespace std;

// used to store count of how many things are still
// unused in the range
class SegmentTree {
  // since only storing # of things still unused in the range
  // only need an int
  vector<vector<int>> levels;

public:
  SegmentTree(int n) {
    vector<int> leaves;
    for (int i = 0; i < n; ++i) {
      leaves.push_back(1); // exactly 1 thing in this range
    }
    levels.push_back(leaves);
    while (levels.back().size() > 1) {
      vector<int> nextLevel;
      for (int i = 0; i < levels.back().size(); i += 2) {
        if (i + 1 < levels.back().size()) {
          nextLevel.push_back(levels.back()[i] + levels.back()[i + 1]);
        } else {
          nextLevel.push_back(levels.back()[i]);
        }
      }
      levels.push_back(nextLevel);
    }
  }
  // query for first index at which there are x available
  // on left and including it
  int query(int x) {
    int curIndex = 0;
    for (int level = levels.size() - 1; level > 0; --level) {
      // always prefer left, but right works too if not enough on left
      int onLeft = levels[level - 1][curIndex * 2];
      if (onLeft >= x) {
        // good, use left
        curIndex *= 2;
      } else {
        // need to use right
        curIndex = curIndex * 2 + 1;
        x -= onLeft;
      }
    }
    return curIndex;
  }
  void disable(int index) {
    int curIndex = index;
    for (int level = 0; level < levels.size(); ++level) {
      levels[level][curIndex]--;
      curIndex /= 2;
    }
  }
};

int main() {
  int n, k;
  cin >> n >> k;

  int curAndLeft = 1; // number here and on left
  int remaining = n;
  SegmentTree s(n);
  while (remaining > 0) {
    int lookingFor = curAndLeft + k;
    lookingFor %= remaining;
    if (lookingFor == 0) {
      lookingFor += remaining;
    }
    int nextIndex = s.query(lookingFor);
    cout << nextIndex + 1 << " ";
    s.disable(nextIndex);
    curAndLeft = lookingFor;
    remaining--;
  }
  cout << endl;
}