#include <bits/stdc++.h>
using namespace std;

int main() {
  int n;
  cin >> n;
  vector<pair<int, int>> nums(n);
  for (int i = 0; i < n; ++i) {
    int num;
    cin >> num;
    nums[i] = {num, i};
  }
  sort(nums.begin(), nums.end());
  int used = 0;
  int prevIdx = nums.size();
  for (int i = 0; i < nums.size(); ++i) {
    if (nums[i].second < prevIdx) {
      ++used;
    }
    prevIdx = nums[i].second;
  }
  cout << used << endl;
}