#include <bits/stdc++.h>
using namespace std;

int dfs(vector<vector<int>> &tree, map<vector<int>, int> &ids, int i,
        int parent) {
  vector<int> children;
  for (int conn : tree[i]) {
    if (conn != parent) {
      children.push_back(dfs(tree, ids, conn, i));
    }
  }
  sort(children.begin(), children.end());
  auto [it, success] = ids.insert({children, ids.size()});
  return it->second;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  // we can construct ids bottom up
  // then the check for equality just becomes checking
  // whether two trees have the same id in the root
  int t;
  for (cin >> t; t > 0; --t) {
    int n;
    cin >> n;
    vector<vector<int>> t1(n), t2(n);
    for (int i = 0; i < n - 1; ++i) {
      int a, b;
      cin >> a >> b;
      t1[--a].push_back(--b);
      t1[b].push_back(a);
    }
    for (int i = 0; i < n - 1; ++i) {
      int a, b;
      cin >> a >> b;
      t2[--a].push_back(--b);
      t2[b].push_back(a);
    }
    // we're given that node 1 is the root
    // so dfs'ing works
    map<vector<int>, int> ids;
    int t1Id = dfs(t1, ids, 0, -1);
    int t2Id = dfs(t2, ids, 0, -1);
    if (t1Id == t2Id) {
      cout << "YES" << '\n';
    } else {
      cout << "NO" << '\n';
    }
  }
}