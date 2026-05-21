#include <bits/stdc++.h>
using namespace std;

int main() {
  int n;
  cin >> n;
  vector<vector<int>> children(n);
  for (int i = 1; i < n; ++i) {
    int parent;
    cin >> parent;
    children[parent - 1].push_back(i);
  }
  vector<int> sizes(n, 1);
  auto dfs = [&](auto &&d, int i) -> void {
    for (int conn : children[i]) {
      d(d, conn);
      sizes[i] += sizes[conn];
    }
  };
  dfs(dfs, 0);
  for (int i = 0; i < n; ++i) {
    cout << sizes[i] - 1 << ' ';
  }
  cout << endl;
}