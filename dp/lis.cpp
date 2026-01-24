#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

int main() {
  int n;
  cin >> n;
  vector<int> endings;
  for (int i = 0; i < n; ++i) {
    int num;
    cin >> num;
    auto it = lower_bound(endings.begin(), endings.end(), num);
    if (it == endings.end()) {
      // nothing bigger, so it can be the new end
      endings.push_back(num);
    } else {
      *it = num;
    }
  }
  cout << endings.size() << endl;
}