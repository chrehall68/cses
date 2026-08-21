#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  // standard LCA with binary lifts problem
  // except we keep track of how many times a specific lift
  // has been used
  int n, m;
  cin >> n >> m;
  vector<vector<int>> g(n + 1);
  vector<int> depths(n + 1);
  constexpr const size_t MAX_K = 25;
  vector<array<int, MAX_K>> lifts(n + 1); // 1-indexed
  for (int i = 0; i <= n; ++i) {
    fill(lifts[i].begin(), lifts[i].end(), -1);
  }
  for (int i = 0; i < n - 1; ++i) {
    int a, b;
    cin >> a >> b;
    g[a].push_back(b);
    g[b].push_back(a);
  }
  auto dfs = [&](auto &dfs, int i, int parent) -> void {
    for (int conn : g[i]) {
      if (conn != parent) {
        lifts[conn][0] = i;
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
      if (lifts[i][k] != -1) {
        int par = lifts[i][k];
        if (lifts[par][k] != -1) {
          lifts[i][k + 1] = (lifts[par][k]);
        }
      }
    }
  }

  // handle paths
  // timesUsed[start][lift] = responsible for [start, 2**lift'th ancestor of
  // start)
  vector<array<int, MAX_K>> timesUsed(n + 1);
  for (int i = 0; i <= n; ++i) {
    fill(timesUsed[i].begin(), timesUsed[i].end(), 0);
  }
  for (; m > 0; --m) {
    int a, b;
    cin >> a >> b;
    int lower = a, higher = b;
    if (depths[b] > depths[a]) {
      lower = b;
      higher = a;
    }
    // raise lower
    for (int kp = k; kp >= 0; --kp) {
      if (depths[lower] - (1 << kp) >= depths[higher]) {
        timesUsed[lower][kp]++;
        lower = lifts[lower][kp];
      }
    }
    int lca = lower;
    if (lower != higher) {
      for (int kp = k; kp >= 0; --kp) {
        if (lifts[lower][kp] != -1 && lifts[lower][kp] != lifts[higher][kp]) {
          timesUsed[lower][kp]++;
          timesUsed[higher][kp]++;
          lower = lifts[lower][kp];
          higher = lifts[higher][kp];
        }
      }
      assert(lower != higher);
      assert(lifts[lower][0] == lifts[higher][0]);
      timesUsed[lower][0]++;
      timesUsed[higher][0]++;
      lca = lifts[lower][0];
    }
    timesUsed[lca][0]++;
  }
  // reduce the times used
  for (int kp = k; kp > 0; --kp) {
    for (int i = 1; i <= n; ++i) {
      if (timesUsed[i][kp] != 0) {
        timesUsed[i][kp - 1] += timesUsed[i][kp];
        timesUsed[lifts[i][kp - 1]][kp - 1] += timesUsed[i][kp];
      }
    }
  }
  // then just output
  for (int i = 1; i <= n; ++i) {
    cout << timesUsed[i][0] << ' ';
  }
  cout << endl;
}