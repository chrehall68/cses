#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  int n;
  cin >> n;
  vector<int> colors(n);
  for (int &color : colors) {
    cin >> color;
  }
  vector<vector<int>> g(n);
  for (int i = 0; i < n - 1; ++i) {
    int a, b;
    cin >> a >> b;
    g[--a].push_back(--b);
    g[b].push_back(a);
  }

  vector<int> colorsInSubtree(n);
  auto dfs = [&](auto &dfs, int i, int parent) -> set<int> {
    set<int> myColors;
    myColors.insert(colors[i]);
    for (int conn : g[i]) {
      if (conn != parent) {
        auto otherColors = dfs(dfs, conn, i);
        if (otherColors.size() > myColors.size()) {
          swap(otherColors, myColors);
        }
        // now insert the smaller
        myColors.merge(otherColors);
      }
    }
    colorsInSubtree[i] = myColors.size();
    return myColors;
  };
  dfs(dfs, 0, -1);
  for (int i = 0; i < n; ++i) {
    cout << colorsInSubtree[i] << ' ';
  }
  cout << endl;
}