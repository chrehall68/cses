#include <bits/stdc++.h>
using namespace std;

int main() {
  // a cycle is strongly connected
  // maybe just find a cycle and then add chains onto the cycle
  // can assign the rest arbitrarily
  // possible iff can reach all nodes from the initial cycle
  int n, m;
  cin >> n >> m;
  vector<set<pair<int, int>>> uEdges(n);
  for (int i = 0; i < m; ++i) {
    int a, b;
    cin >> a >> b;
    uEdges[--a].insert({--b, i});
    uEdges[b].insert({a, i});
  }
  // arbitrarily start at node 0 and try to find a cycle
  // that comes back to node 0
  vector<bool> explored(n);
  // node, what edge was taken to get to it
  vector<pair<int, int>> sta;
  vector<pair<int, int>> cycle;
  set<int> usedIdents;
  vector<bool> inComponent(n);
  auto dfs = [&](auto &dfs, int i) -> void {
    explored[i] = true;
    for (auto [conn, ident] : uEdges[i]) {
      if (!usedIdents.count(ident)) {
        if (inComponent[conn]) {
          // found it
          sta.push_back({conn, ident});
          cycle = sta;
          sta.pop_back();
          break;
        } else if (!explored[conn]) {
          sta.push_back({conn, ident});
          usedIdents.insert(ident);
          dfs(dfs, conn);
          usedIdents.erase(ident);
          sta.pop_back();
          // stop early
          if (!cycle.empty()) {
            break;
          }
        }
      }
    }
  };
  inComponent[0] = true;
  dfs(dfs, 0);
  if (cycle.empty()) {
    cout << "IMPOSSIBLE" << endl;
    return 0;
  }
  // otherwise, we have a starting initial cycle
  // not we keep traveling through the outgoing edges to add in new cycles
  vector<pair<int, int>> directedEdges;
  set<int> toProcess;
  auto addCycle = [&](int start) {
    int prev = start;
    for (auto [conn, ident] : cycle) {
      if (!inComponent[conn]) {
        toProcess.insert(conn);
      }
      inComponent[conn] = true;
      directedEdges.push_back({prev, conn});
      uEdges[prev].erase({conn, ident});
      uEdges[conn].erase({prev, ident});
      prev = conn;
    }
  };
  addCycle(0);
  toProcess.insert(0); // because we started with 0 in the component
  // now start at a node in toProcess, go through some outgoing edges, and then
  // come back to the cycle
  fill(explored.begin(), explored.end(), false);
  while (!toProcess.empty()) {
    int node = *toProcess.begin();
    while (!uEdges[node].empty()) {
      auto [to, ident] = *uEdges[node].begin();
      uEdges[node].erase({to, ident});
      uEdges[to].erase({node, ident});

      if (inComponent[to]) {
        // doesn't matter, just assign
        directedEdges.push_back({node, to});
      } else {
        // need to dfs till we hit the cycle again
        cycle.clear();
        sta.clear();
        usedIdents.clear();
        sta.push_back({to, ident});
        usedIdents.insert(ident);
        dfs(dfs, to);

        if (!cycle.empty()) {
          // add each
          addCycle(node);
        } else {
          cout << "IMPOSSIBLE" << endl;
          return 0;
        }
      }
    }
    toProcess.erase(node);
  }
  // now that we've processed everything, just make sure we've touched all nodes
  int total = accumulate(inComponent.begin(), inComponent.end(), 0L);
  if (total == n) {
    for (auto [i, conn] : directedEdges) {
      cout << i + 1 << ' ' << conn + 1 << '\n';
    }

  } else {
    cout << "IMPOSSIBLE" << endl;
    return 0;
  }
}
