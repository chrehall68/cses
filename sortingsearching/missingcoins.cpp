#include <bits/stdc++.h>
using namespace std;

int main() {
  int n;
  cin >> n;
  vector<long long> nums(n);
  for (int i = 0; i < n; ++i) {
    cin >> nums[i];
  }
  sort(nums.begin(), nums.end());
  long long makeTill = 0;
  for (int i = 0; i < n; ++i) {
    if (nums[i] > makeTill + 1) {
      cout << makeTill + 1 << endl;
      return 0;
    } else {
      makeTill += nums[i];
    }
  }
  cout << makeTill + 1 << endl;
}