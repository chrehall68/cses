#include <bits/stdc++.h>
#include <ios>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);
  int t;
  cin >> t;
  for (int testCase = 0; testCase < t; ++testCase) {
    long long x, y;
    cin >> y >> x;
    long long whoseSquare = max(x, y);
    long long prevSquare = (whoseSquare - 1) * (whoseSquare - 1);
    long long theSquare = whoseSquare * whoseSquare;
    if (whoseSquare % 2 == 0) {
      // even square
      if (y > x) {
        cout << theSquare - (x - 1) << endl;
      } else {
        cout << prevSquare + y << endl;
      }
    } else {
      // odd square
      if (x > y) {
        cout << theSquare - (y - 1) << endl;
      } else {
        cout << prevSquare + x << endl;
      }
    }
  }
}