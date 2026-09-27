#include <bits/stdc++.h>
using namespace std;

int main() {
  // so we start with a tree
  // and we want to add the minimum amount of edges such that
  // removing any edge still leaves the graph strongly connected
  // well maybe it'd be possible to like calculate:
  // what's the minimum edges needed to make a subtree durably connected
  // but then how do we extend that?
  // it depends on 2's vs 1's
  // ==============
  // another idea is like starting at the root, we have some children
  // we can pair them up because if they're on different branches
  // then we're good to go
  // but then the problem becomes to what nodes on the larger branch
  // do we assign the nodes
  // ==============
  // we know we use no more than #leaves edges
  // tends to be around ceil(#leaves) edges
  // in fact is it ever more?
  // wait yeah
  //     root
  //      |
  //      a
  //     / \
  //    b   c
  // ==============
  // construction lemma:
  // any tree of size n can be made by attaching a node of degree 1
  // to a tree of size n-1
  // proof is that a tree by definition must have at least one node of
  // degree 1 (or is the singleton tree)
  // so, take that node away (this is the inverse of attaching one)
  // then we still have a tree
  // ===============
  // proof??
  // any tree of size n with k leaves costs ceil(#leaves) edges
  // maybe not leaves
  // maybe it's # of nodes with degree 1
  // yeah i think this works
  // we have two cases:
  // - suppose we attach to a node of degree 1. Then, just drag its
  //   edge down to us.
  // - suppose we attach to a node of degree > 1. Then,
  //     if old way had odd # of nodes with degree 1, pair with the other
  //     unpaired otherwise, draw an edge to root
  // works as long as root has more than degree 1
  // since n >= 3 there must be a node with degree > 1
  // ===============
  // wait actually this is a counterexample
  // 7
  // 1 2
  // 1 3
  // 3 4
  // 3 5
  // 5 6
  // 5 7
  //
  //    1
  //  2    3
  //      4   5
  //         6  7
  // since here if we close the loop naively between 6 and 7
  // we can isolate that component by cutting the edge from 3 to 5
  // so instead of doing that, we need to take the previous edge path
  // that touches the root
  // and extend it to include us

  int n;
  cin >> n;
  vector<vector<int>> tree(n + 1);
  vector<int> degree(n + 1);
  for (int i = 0; i < n - 1; ++i) {
    int a, b;
    cin >> a >> b;
    tree[a].push_back(b);
    tree[b].push_back(a);
    degree[a]++;
    degree[b]++;
  }
  // now find a root
  int root = 1;
  for (; degree[root] == 1; ++root)
    ;
  // now add nodes one at a time
  const int UNSET = -1;
  vector<int> constructionDegree(n + 1); // not including our extra edges
  // both sides should match
  // stragglers get stored as edges to root
  // and we maintain that there is at most one straggler at any time
  vector<int> extraEdge(n + 1, UNSET);
  vector<int> parents(n + 1, UNSET);
  queue<int> q;
  q.push(root);
  int prevUsed = UNSET;
  extraEdge[root] = root;
  while (!q.empty()) {
    int node = q.front();
    q.pop();
    int parent = 0;
    if (node != root) {
      parent = parents[node];
      assert(parent != UNSET);
      if (constructionDegree[parent] == 1) {
        assert(extraEdge[parent] != UNSET);
        int parentConnectedTo = extraEdge[parent];
        // move edge down
        extraEdge[parent] = UNSET;
        extraEdge[parentConnectedTo] = node;
        extraEdge[node] = parentConnectedTo;
        if (parent == prevUsed) {
          prevUsed = node;
        }
      } else {
        if (extraEdge[root] != UNSET) {
          // there's already a cycle that goes through root
          // link that cycle to us stragglers instead
          int otherNode = extraEdge[root];
          extraEdge[root] = UNSET;
          if (parents[otherNode] == parent && parent != root) {
            // this would've isolated us
            // so we instead need to join the subtree
            assert(prevUsed != UNSET);
            int prevUsedConn = extraEdge[prevUsed];

            extraEdge[prevUsed] = node;
            extraEdge[node] = prevUsed;
            extraEdge[otherNode] = prevUsedConn;
            extraEdge[prevUsedConn] = otherNode;
          } else {
            // it's fine to just link to the other node
            extraEdge[node] = otherNode;
            extraEdge[otherNode] = node;
            prevUsed = node;
          }
        } else {
          // link to root
          extraEdge[root] = node;
          extraEdge[node] = root;
        }
      }
    }

    constructionDegree[node] = 1;
    constructionDegree[parent]++;
    // and add children one by one
    for (int conn : tree[node]) {
      if (conn != parent) {
        q.push(conn);
        parents[conn] = node;
      }
    }
  };
  // then output
  vector<pair<int, int>> edges;
  vector<bool> explored(n + 1);
  // handle pairs
  for (int node = 1; node <= n; ++node) {
    if (!explored[node] && extraEdge[node] != UNSET) {
      int conn = extraEdge[node];
      assert(!explored[conn]);
      edges.push_back({node, conn});
      explored[node] = true;
      explored[conn] = true;
    }
  }
  cout << edges.size() << endl;
  for (auto [node1, node2] : edges) {
    cout << node1 << ' ' << node2 << endl;
  }
}
