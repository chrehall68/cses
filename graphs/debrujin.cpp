#include <bits/stdc++.h>
using namespace std;

int main() {
  int n;
  cin >> n;
  if (n == 1) {
    cout << "01" << endl;
    return 0;
  }
  int limit = 1 << n;
  int mask = (1 << n) - 1;
  // similar idea to eulerian tour
  // but like adapting it so it's sorta hamiltonian
  list<int> order;
  vector<bool> visited(limit);
  stack<pair<int, list<int>::iterator>> s;
  order.push_back(0);
  visited[0] = true;
  s.push({0, order.begin()});
  while (!s.empty()) {
    auto [num, myIt] = s.top();
    int c0 = (num << 1) & mask;
    int c1 = c0 | 1;
    if (!visited[c0]) {
      // visit c0
      visited[c0] = true;
      auto insertionPoint = myIt;
      insertionPoint++;
      auto nextIt = order.insert(insertionPoint, c0);
      s.push({c0, nextIt});
    } else if (!visited[c1]) {
      // visit c1
      visited[c1] = true;
      auto insertionPoint = myIt;
      insertionPoint++;
      auto nextIt = order.insert(insertionPoint, c1);
      s.push({c1, nextIt});
    } else {
      s.pop();
    }
  }
  for (int i = 0; i < n - 1; ++i) {
    cout << '0';
  }
  for (int num : order) {
    cout << (num & 1);
  }
  cout << endl;
}