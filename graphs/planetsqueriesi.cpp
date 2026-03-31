#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  // n nodes, n edges
  // therefore we are guaranteed at least one cycle
  // and every node will either be:
  // - in a cycle
  // - connected as a tail to a cycle
  // (cycles can have multiple tails, but a tail can go to only one cycle)
  int n, q;
  cin >> n >> q;
  ++n;
  vector<int> g(n);
  for (int i = 1; i < n; ++i) {
    cin >> g[i];
  }
  // then dfs
  vector<bool> explored(n, false);
  vector<bool> exploring(n, false);
  // cycleInfo[i] = {cycleIdx, innerIdx}
  // tailInfo[i] = {tailIdx, innerIdx}
  vector<pair<int, int>> cycleInfo(n, {-1, -1});
  vector<vector<int>> cycles, lifts(n);
  vector<int> pi(n), depths(n);
  function<void(int)> dfs = [&](int i) {
    if (exploring[i]) {
      // found a cycle
      vector<int> cycle;
      cycleInfo[i] = {cycles.size(), cycle.size()};
      cycle.push_back(i);
      int cur = pi[i];
      while (cur != i) {
        cycleInfo[cur] = {cycles.size(), cycle.size()};
        cycle.push_back(cur);
        cur = pi[cur];
      }
      cycles.push_back(cycle);
      return;
    }
    exploring[i] = true;
    pi[g[i]] = i;
    if (!explored[g[i]]) {
      dfs(g[i]);
    }
    // check if i'm in a cycle
    if (cycleInfo[i].first == -1) {
      // not in a cycle, so attach it
      depths[i] = depths[g[i]] + 1;
      lifts[i].push_back(g[i]);
    }
    explored[i] = true;
    exploring[i] = false;
  };
  for (int i = 1; i < n; ++i) {
    if (!explored[i]) {
      dfs(i);
    }
  }
  // build lifts
  const int TIMES = 20;
  for (int k = 1; k < TIMES; ++k) {
    // using the 2**(k-1, build 2**k
    for (int i = 0; i < n; ++i) {
      if (k - 1 < lifts[i].size()) {
        int parent = lifts[i][k - 1];
        if (k - 1 < lifts[parent].size()) {
          lifts[i].push_back(lifts[parent][k - 1]);
        }
      }
    }
  }
  // then handle queries
  for (int i = 0; i < q; ++i) {
    int x, k;
    cin >> x >> k;
    int depth = depths[x];
    if (depth >= k) {
      // never leave the tail
      int cur = x;
      for (int t = TIMES; t >= 0; --t) {
        if (k & (1 << t)) {
          // jump this far
          assert(t < lifts[cur].size());
          cur = lifts[cur][t];
        }
      }
      cout << cur << '\n';
    } else {
      // leave the tail
      int cur = x;
      for (int t = TIMES; t >= 0; --t) {
        if (t < lifts[cur].size()) {
          cur = lifts[cur][t];
        }
      }
      auto [cycle, cycleIdx] = cycleInfo[cur];
      assert(cycle != -1);
      // travel remaining k backwards
      int remainingK = (k - depth) % cycles[cycle].size();
      cout << cycles[cycle][(cycleIdx - remainingK + cycles[cycle].size()) %
                            cycles[cycle].size()]
           << '\n';
    }
  }
}