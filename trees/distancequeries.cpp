#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  // standard LCA with binary lifts problem
  // except we also need to keep track of how far we've travelled
  int n, q;
  cin >> n >> q;
  vector<vector<int>> g(n + 1);
  vector<int> depths(n + 1);
  vector<vector<int>> lifts(n + 1); // 1-indexed
  for (int i = 0; i < n - 1; ++i) {
    int a, b;
    cin >> a >> b;
    g[a].push_back(b);
    g[b].push_back(a);
  }
  auto dfs = [&](auto &dfs, int i, int parent) -> void {
    for (int conn : g[i]) {
      if (conn != parent) {
        lifts[conn].push_back(i);
        depths[conn] = depths[i] + 1;
        dfs(dfs, conn, i);
      }
    }
  };
  dfs(dfs, 1, 0);

  // build lifts
  int k;
  for (k = 0; (1 << k) <= n; ++k) {
    for (int i = 1; i <= n; ++i) {
      if (k < lifts[i].size()) {
        int par = lifts[i][k];
        if (k < lifts[par].size()) {
          lifts[i].push_back(lifts[par][k]);
        }
      }
    }
  }

  // handle queries
  for (; q > 0; --q) {
    int a, b;
    cin >> a >> b;
    int lower = a, higher = b;
    if (depths[b] > depths[a]) {
      lower = b;
      higher = a;
    }
    // raise lower
    int travelled = 0;
    for (int kp = k; kp >= 0; --kp) {
      if (depths[lower] - (1 << kp) >= depths[higher]) {
        lower = lifts[lower][kp];
        travelled += (1 << kp);
      }
    }
    if (lower != higher) {
      for (int kp = k; kp >= 0; --kp) {
        if (kp < lifts[lower].size() && lifts[lower][kp] != lifts[higher][kp]) {
          lower = lifts[lower][kp];
          higher = lifts[higher][kp];
          travelled += (1 << kp) * 2;
        }
      }
      assert(lower != higher);
      assert(lifts[lower][0] == lifts[higher][0]);
      travelled += 2;
    }
    cout << travelled << '\n';
  }
}