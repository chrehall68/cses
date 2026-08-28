#include <bits/stdc++.h>
using namespace std;

int solve(int n, int k, int start) {
  if (n == 1) {
    return 1;
  }
  int removals = (n - start) / 2 + 1;
  if (k < removals) {
    return start + 2 * k;
  }
  // actually do removals
  if (start == 2) {
    // takes out all evens, so remaining are odds
    // which require the -1
    if (n % 2 == 0) {
      start = 2;
    } else {
      start = 1;
    }
    return solve(n - removals, k - removals, start) * 2 - 1;
  } else {
    // takes out all odds, so remaining are evens
    if (n % 2 == 0) {
      start = 1;
    } else {
      start = 2;
    }
    return solve(n - removals, k - removals, start) * 2;
  }
}
int main() {
  // 1 2 3 4 5 6 7
  //   2   4   6
  // so first takes out all the evens
  // then you have
  // 1 3 5 7
  // 1 2 3 4
  // and we take out every second one of these
  // 1 3 or 2 4
  int q;
  vector<function<int(int)>> ops;
  for (cin >> q; q > 0; --q) {
    int n, k;
    cin >> n >> k;
    if (n == 1) {
      cout << 1 << endl;
      continue;
    }
    k -= 1;
    cout << solve(n, k, 2) << endl;
  }
}