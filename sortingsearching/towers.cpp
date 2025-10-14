#include <bits/stdc++.h>
#include <set>
using namespace std;

int main() {
  int n;
  cin >> n;
  vector<int> nums(n);
  for (int i = 0; i < n; ++i) {
    cin >> nums[i];
  }

  multiset<int> towerTops;
  for (int num : nums) {
    // find smallest tower that can fit this
    auto it = towerTops.upper_bound(num);
    if (it != towerTops.end()) {
      towerTops.erase(it);
    }
    // either way will need something for this
    towerTops.insert(num);
  }
  cout << towerTops.size() << endl;
}