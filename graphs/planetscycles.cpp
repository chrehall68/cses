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
  int n;
  cin >> n;
  ++n;
  vector<int> g(n);
  for (int i = 1; i < n; ++i) {
    cin >> g[i];
  }
  // then dfs
  vector<bool> explored(n, false);
  vector<bool> exploring(n, false);
  // cycleInfo[i] = cycleIdx
  // cycles[i] = size of i'th cycle
  vector<int> cycleInfo(n, -1), cycles;
  vector<int> pi(n), depths(n);
  function<void(int)> dfs = [&](int i) {
    if (exploring[i]) {
      // found a cycle
      int cycleSize = 1;
      cycleInfo[i] = cycles.size();
      int cur = pi[i];
      while (cur != i) {
        cycleInfo[cur] = cycles.size();
        cycleSize++;
        cur = pi[cur];
      }
      cycles.push_back(cycleSize);
      return;
    }
    exploring[i] = true;
    pi[g[i]] = i;
    if (!explored[g[i]]) {
      dfs(g[i]);
    }
    // check if i'm in a cycle
    if (cycleInfo[i] == -1) {
      // not in a cycle, so attach it
      depths[i] = depths[g[i]] + 1;
      cycleInfo[i] = cycleInfo[g[i]];
    }
    explored[i] = true;
    exploring[i] = false;
  };
  for (int i = 1; i < n; ++i) {
    if (!explored[i]) {
      dfs(i);
    }
  }
  // then output
  for (int i = 1; i < n; ++i) {
    // pay for depth, then cycle size
    cout << depths[i] + cycles[cycleInfo[i]] << ' ';
  }
  cout << endl;
}