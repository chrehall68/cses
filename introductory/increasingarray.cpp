#include <bits/stdc++.h>
using namespace std;

int main() {
  int n;
  cin >> n;
  long moves = 0;
  int prev = 0;
  for (int i = 0; i < n; ++i) {
    int cur;
    cin >> cur;
    if (cur < prev) {
      moves += (prev - cur);
    } else {
      prev = cur;
    }
  }
  cout << moves << endl;
}