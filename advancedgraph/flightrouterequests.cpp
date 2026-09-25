#include <bits/stdc++.h>
using namespace std;

int main() {
  // so if we can topologically sort, then we can arrange everything in a line
  // and thus costs |component|-1 edges
  // otherwise, need it to be scc
  // so just create a cycle, costing |component| edges
  int n, m;
  cin >> n >> m;
  vector<vector<int>> diGraph(n), undiGraph(n);
  vector<int> inDegree(n);
  for (int i = 0; i < m; ++i) {
    int a, b;
    cin >> a >> b;
    diGraph[--a].push_back(--b);
    undiGraph[a].push_back(b);
    undiGraph[b].push_back(a);
    inDegree[b]++;
  }
  // then just check every component
  vector<bool> explored(n);
  int total = 0;
  for (int i = 0; i < n; ++i) {
    if (!explored[i]) {
      // this is part of a new component
      vector<int> component;
      component.push_back(i);
      explored[i] = true;
      for (size_t idx = 0; idx < component.size(); ++idx) {
        for (int conn : undiGraph[component[idx]]) {
          if (!explored[conn]) {
            explored[conn] = true;
            component.push_back(conn);
          }
        }
      }
      // now check whether component can be topsorted
      vector<int> order;
      for (int node : component) {
        if (inDegree[node] == 0) {
          order.push_back(node);
        }
      }
      for (size_t orderIdx = 0; orderIdx < order.size(); ++orderIdx) {
        int node = order[orderIdx];
        for (int conn : diGraph[node]) {
          if (--inDegree[conn] == 0) {
            order.push_back(conn);
          }
        }
      }
      total += component.size();
      if (order.size() == component.size()) {
        // topsortable
        total -= 1;
      }
    }
  }
  cout << total << endl;
}