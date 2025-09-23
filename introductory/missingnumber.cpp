#include <bits/stdc++.h>
using namespace std;
int main() {
  int n;
  cin >> n;
  vector<bool> used(n);
  for (int i = 0; i < n - 1; ++i) {
    int idx;
    cin >> idx;
    used[idx - 1] = true;
  }
  for (int i = 0; i < n; ++i) {
    if (!used[i]) {
      cout << i + 1 << endl;
    }
  }
}