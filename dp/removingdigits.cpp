#include <bits/stdc++.h>
#include <limits>
#include <string>
using namespace std;
int main() {
  int n;
  cin >> n;

  // so we must subtract one of the digits
  vector<int> minOps(n + 1, numeric_limits<int>::max());
  minOps[0] = 0;
  for (int subResult = 0; subResult < n; ++subResult) {
    // this result came from subtracting a number 1-9
    for (int subtractor = 1; subtractor < 10; ++subtractor) {
      int from = subResult + subtractor;
      if (from <= n &&
          to_string(from).find(to_string(subtractor)) != string::npos) {
        // then it could've come from that
        minOps[from] = min(minOps[from], minOps[subResult] + 1);
      }
    }
  }
  cout << minOps[n] << endl;
}