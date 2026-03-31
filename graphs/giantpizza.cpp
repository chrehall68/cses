#include <bits/stdc++.h>
using namespace std;

int main() {
  int n, m;
  cin >> n >> m;
  // 2sat (2 satisfiability)
  // m items, n family members
  // so m literals, n clauses
  // first side is x, second half is ~x
  vector<vector<int>> adj(2 * m), adjR(2 * m);
  function<int(int)> inv = [&](int i) {
    if (i >= m) {
      return i - m;
    }
    return i + m;
  };
  for (int i = 0; i < n; ++i) {
    char s1, s2;
    int t1, t2;
    cin >> s1 >> t1 >> s2 >> t2;
    --t1;
    --t2;
    if (s1 == '-') {
      t1 = inv(t1);
    }
    if (s2 == '-') {
      t2 = inv(t2);
    }
    // so now we have t1 or t2
    // meaning ~t1 -> t2
    // and ~t2 -> t1
    adj[inv(t1)].push_back(t2);
    adjR[t2].push_back(inv(t1));
    adj[inv(t2)].push_back(t1);
    adjR[t1].push_back(inv(t2));
  }
  // and now find scc
  // to make sure there are no contradictions
  vector<bool> explored(2 * m, false);
  vector<int> order, component(2 * m);
  function<void(int)> dfs = [&](int i) {
    explored[i] = true;
    for (int conn : adj[i]) {
      if (!explored[conn]) {
        dfs(conn);
      }
    }
    order.push_back(i);
  };
  for (int i = 0; i < 2 * m; ++i) {
    if (!explored[i]) {
      dfs(i);
    }
  }
  // then reverse for top order
  reverse(order.begin(), order.end());
  fill(explored.begin(), explored.end(), false);
  // dfs again in top order order, keeping track of component indexes
  function<void(int, int)> dfs2 = [&](int i, int comp) {
    component[i] = comp;
    explored[i] = true;
    for (int conn : adjR[i]) {
      if (!explored[conn]) {
        dfs2(conn, comp);
      }
    }
  };
  int comp = 0;
  for (int node : order) {
    if (!explored[node]) {
      dfs2(node, ++comp);
    }
  }
  // now just go in order
  vector<bool> res(m);
  for (int i = 0; i < m; ++i) {
    if (component[i] == component[inv(i)]) {
      cout << "IMPOSSIBLE" << endl;
      return 0;
    }
    // if assigning it true cannot reach false, we should assign true
    res[i] = component[i] > component[inv(i)];
  }
  for (int i = 0; i < m; ++i) {
    if (res[i]) {
      cout << "+ ";
    } else {
      cout << "- ";
    }
  }
  cout << endl;
}