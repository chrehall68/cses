#include <bits/stdc++.h>
using namespace std;
const int M = 1'000'000'000;

int main() {
  // case vertex is start or end: NO
  // so if the vertex is not a cut vertex, then YES
  // maybe there's some structure after we reduce a graph
  // to only cut vertices?
  // yeah the cut vertices should form a tree
  // and so it becomes an lca on those
  // if c is a cut vertex and lies on the path from component(a)
  // to component(b), then it is impossible
  // wait actually cut vertices don't necessarily form a tree
  //           f
  //          /b\
  //       e a - c g
  //          \d/
  //           h
  // where a,b,c,d are cut vertices
  // but don't form a tree
  // but maybe we can do like a similar idea to finding true cut vertices
  // define subtree as subtree in the dfs tree
  // for a query (a,b,c)
  // without loss of generality, then suppose:
  // - a,b are both not in c's subtree. Then, removing c keeps a,b reachable
  // - a,b are both in c's subtree. Then, removing c keeps a,b reachable
  //   iff c is not the only way for a to reach b. If the lca of a,b is not c,
  //   then possible. Otherwise, let a = child(c) in direction a, b = vice versa
  //   if a==b or both can escape c's subtree, then possible
  // - a in c's subtree, b not in c's subtree. Then, look at the min entryTime
  //   of nodes reachable by c or b's children via back edges. Since the graph
  //   is connected, we know that if we can get above c (make it to a node with
  //   entryTime[node] < entryTime[c]) then we can reach a
  //
  // so how to do this?
  // need to know whether a node is in a subtree or not
  // maybe an eulerian tour would be nice here? or could use lifts and depths
  // yeah an eulerian tour works; node a is in node c's subtree iff
  // entry[c] < entry[a] and exit[a] < exit[c]
  // so we just store entry, exit times
  // and also store the reachable entry times
  int n, m, q;
  cin >> n >> m >> q;
  vector<vector<int>> g(n + 1);
  for (int i = 0; i < m; ++i) {
    int a, b;
    cin >> a >> b;
    g[a].push_back(b);
    g[b].push_back(a);
  }
  int time = 0;
  vector<vector<int>> lifts(n + 1);
  vector<int> depths(n + 1), entryTime(n + 1, M), exitTime(n + 1),
      // minReachableEntryTime[node] = min reachable by node or its children
      minReachableEntryTime(n + 1, M);
  auto dfs = [&](auto &dfs, int i, int parent) -> void {
    entryTime[i] = time++;
    // compute lifts
    for (size_t k = 0; k < lifts[i].size() && k < lifts[lifts[i][k]].size();
         ++k) {
      lifts[i].push_back(lifts[lifts[i][k]][k]);
    }
    // continue dfs
    for (int conn : g[i]) {
      if (conn != parent) {
        if (entryTime[conn] == M) {
          // this is a child
          lifts[conn].push_back(i);
          depths[conn] = depths[i] + 1;
          dfs(dfs, conn, i);
          minReachableEntryTime[i] =
              min(minReachableEntryTime[i], minReachableEntryTime[conn]);
        } else {
          // back edge
          minReachableEntryTime[i] =
              min(minReachableEntryTime[i], entryTime[conn]);
        }
      }
    }
    // exit the node
    exitTime[i] = time++;
  };
  dfs(dfs, 1, -1);
  // now just process queries
  auto inSubtree = [&](int a, int c) -> bool {
    return entryTime[c] < entryTime[a] && exitTime[a] < exitTime[c];
  };
  const int MAX_K = 21;
  for (int i = 0; i < q; ++i) {
    int a, b, c;
    cin >> a >> b >> c;
    bool aInSubtree = inSubtree(a, c), bInSubtree = inSubtree(b, c);
    if (a == c || b == c) {
      cout << "NO" << endl;
    } else if (!aInSubtree && !bInSubtree) {
      cout << "YES" << endl;
    } else if (aInSubtree && bInSubtree) {
      int lower = a, higher = b;
      if (depths[lower] < depths[higher]) {
        swap(lower, higher);
      }
      for (int k = MAX_K; k >= 0; --k) {
        if (depths[lower] - (1 << k) >= depths[higher]) {
          lower = lifts[lower][k];
        }
      }
      if (lower != higher) {
        // lift them both up
        for (int k = MAX_K; k >= 0; --k) {
          if (depths[lower] - (1 << k) >= depths[c] &&
              lifts[lower][k] != lifts[higher][k]) {
            lower = lifts[lower][k];
            higher = lifts[higher][k];
          }
        }
        assert(lower != higher);
        // had an LCA below c
        if (lifts[lower][0] != c) {
          lower = lifts[lower][0];
          higher = lifts[higher][0];
          assert(lower == higher);
        }
      }
      if (lower == higher || (minReachableEntryTime[lower] < entryTime[c] &&
                              minReachableEntryTime[higher] < entryTime[c])) {
        cout << "YES" << endl;
      } else {
        cout << "NO" << endl;
      }
    } else {
      int nodeInSubtree = a;
      if (!aInSubtree) {
        nodeInSubtree = b;
      }
      for (int k = MAX_K; k >= 0; --k) {
        if (depths[nodeInSubtree] - (1 << k) > depths[c]) {
          nodeInSubtree = lifts[nodeInSubtree][k];
        }
      }
      assert(lifts[nodeInSubtree][0] == c);
      if (minReachableEntryTime[nodeInSubtree] < entryTime[c]) {
        cout << "YES" << endl;
      } else {
        cout << "NO" << endl;
      }
    }
  }
}
