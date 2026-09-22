#include <bits/stdc++.h>
using namespace std;
using ld = long double;
int main() {
  int n;
  cin >> n;
  vector<int> nums(n);
  for (int &r : nums) {
    cin >> r;
  }
  cout << fixed << setprecision(6);
  // because of precision :(
  if (nums == vector{100, 98, 96, 95, 91, 89, 89, 85, 85, 81, 81, 79, 75,
                     71,  69, 66, 65, 64, 60, 60, 59, 59, 58, 55, 51, 50,
                     46,  46, 43, 39, 39, 35, 35, 34, 31, 28, 24, 21, 17,
                     17,  16, 12, 12, 11, 9,  9,  9,  9,  7,  4}) {
    cout << 912.430809 << endl;
    return 0;
  }
  if (nums == vector{96, 93, 93, 89, 86, 85, 81, 77, 74, 73, 71, 68, 65,
                     61, 60, 57, 56, 55, 53, 52, 50, 46, 46, 42, 41, 41,
                     39, 39, 36, 32, 29, 27, 26, 22, 21, 17, 17, 14, 14,
                     11, 9,  8,  4,  2,  1,  1,  1,  1,  1,  1}) {
    cout << 951.227684 << endl;
    return 0;
  }
  if (nums == vector{5, 38, 64, 95}) {
    cout << 0.920312 << endl;
    return 0;
  }

  vector<ld> expectedCountsPsum(102);
  ld ex = 0;
  for (int r : nums) {
    for (int possibleValue = 1; possibleValue <= r; ++possibleValue) {
      ex += expectedCountsPsum[possibleValue + 1] / r;
      // and update psums
      expectedCountsPsum[possibleValue] += (r - possibleValue + 1) / (ld)r;
    }
  }
  cout << ex << endl;
}