#include <bits/stdc++.h>
#include <ios>
using namespace std;

int main() {
  int n;
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin >> n;

  // 1
  // 2 4 1 3
  // if n > 4 then possible
  // 1...10 -> 10 numbers -> 5 gap
  // 1 6 2 7 3 8 4 9 5 10
  // 1...9 -> 9 numbers -> 5 gap
  // 1 6 2 7 3 8 4 9 5
  // 1...8 -> 8 numbers -> 4 gap
  // 1 5 2 6 3 7 4 8
  if (n == 1) {
    cout << 1 << endl;
  } else if (n == 2 || n == 3) {
    cout << "NO SOLUTION" << endl;
  } else if (n == 4) {
    cout << "2 4 1 3" << endl;
  } else {
    int gap = (n + 1) / 2;
    int used = 0;
    for (int cur = 1; used < n; ++cur) {
      cout << cur << " ";
      if (cur + gap <= n) {
        cout << cur + gap << " ";
      }
      used += 2;
    }
    cout << endl;
  }
}