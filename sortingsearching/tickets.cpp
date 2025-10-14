#include <bits/stdc++.h>
using namespace std;

int main() {
  int n, m;
  cin >> n >> m;
  multiset<int> tickets;
  for (int i = 0; i < n; ++i) {
    int num;
    cin >> num;
    tickets.insert(num);
  }
  for (int i = 0; i < m; ++i) {
    int num;
    cin >> num;
    auto it = tickets.upper_bound(num);
    if (it != tickets.begin()) {
      --it;
      cout << *it << endl;
      tickets.erase(it);
    } else {
      cout << -1 << endl;
    }
  }
}