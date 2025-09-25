#include <bits/stdc++.h>
using namespace std;

int main() {
  int t;
  cin >> t;
  for (int i = 0; i < t; ++i) {
    int a, b;
    cin >> a >> b;
    int ma = max(a, b);
    int mi = min(a, b);
    int diff = ma - mi;
    mi -= diff;
    if (0 <= mi && mi % 3 == 0) {
      cout << "YES" << endl;
    } else {
      cout << "NO" << endl;
    }
  }
}