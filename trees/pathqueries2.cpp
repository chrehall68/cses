#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// iterative segtree
// point update and range max
class Segtree {
  size_t n;
  vector<ll> spaces; // organized as implicit heap
public:
  Segtree(vector<ll> &init) : n(init.size()), spaces(2 * n) {
    for (size_t i = 0; i < n; ++i) {
      spaces[i + n] = init[i];
    }
    // now that we have the bottom row, work up
    for (size_t i = n - 1; i > 0; --i) {
      spaces[i] = max(spaces[i * 2], spaces[i * 2 + 1]);
    }
  }
  void update(size_t idx, ll newVal) {
    idx += n;
    spaces[idx] = newVal;
    // update parents
    for (; idx > 0; idx >>= 1) {
      spaces[idx >> 1] = max(spaces[idx], spaces[idx ^ 1]);
    }
  }
  ll rangeMax(size_t l, size_t r) {
    // l stores the smallest unused left endpoint, r stores the last unused
    // right endpoint
    ll res = 0;
    for (l += n, r += n; l <= r; l >>= 1, r >>= 1) {
      // nodes are a right child if %2 == 1
      // if l is a right child, we need to use it now since otherwise the parent
      // will contain a node that wasn't in our span
      if (l & 1) {
        res = max(res, spaces[l]);
        // and now that we've used it, go right
        l++;
      }
      if ((r & 1) == 0 && r >= l) {
        // r is a left child, so its parent would contain something not in our
        // span so use it and go left
        res = max(res, spaces[r]);
        --r;
      }
    }
    return res;
  }
};

int main() {
  // goal = decompose into heavy paths
  // and store, for every node, which heavy path
  // it is in as well as where it is in the heavy path
  // and then for each heavy path, create a segtree
  // over the values so that we can query for max
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int n, q;
  cin >> n >> q;
  constexpr const size_t MAX_K = 25;
  vector<vector<int>> g(n);
  vector<ll> values(n);
  for (ll &num : values) {
    cin >> num;
  }
  for (int i = 0; i < n - 1; ++i) {
    int a, b;
    cin >> a >> b;
    g[--a].push_back(--b);
    g[b].push_back(a);
  }
  vector<size_t> sizes(n);
  vector<int> depths(n);
  vector<int> heavyEdgeGoingDown(n, -1);
  vector<array<int, MAX_K>> lifts(n);
  // initial dfs to build lifts as well as calculate sizes
  auto dfs = [&](auto &dfs, int i, int parent) -> size_t {
    // compute my lifts
    for (size_t k = 0; k < MAX_K - 1; ++k) {
      int par = lifts[i][k];
      // assert(par != -1);
      if (lifts[par][k] != -1) {
        lifts[i][k + 1] = lifts[par][k];
      } else {
        break;
      }
    }

    // continue dfs
    size_t size = 1;
    for (int conn : g[i]) {
      if (conn != parent) {
        lifts[conn][0] = i;
        depths[conn] = depths[i] + 1;
        size += dfs(dfs, conn, i);
      }
    }
    sizes[i] = size;
    // and calculate whether there's a heavy edge
    for (int conn : g[i]) {
      if (conn != parent) {
        if (sizes[conn] >= (size + 1) / 2) {
          // assert(heavyEdgeGoingDown[i] == -1);
          heavyEdgeGoingDown[i] = conn;
        }
      }
    }
    return size;
  };
  dfs(dfs, 0, -1);

  // build heavy light decomposition (HLD)
  // components are laid out in continuous ranges
  // where the highest node in the component is the first
  // no specific order to how components are ordered though
  // componentInfo[node] = {whichComponent, indexInComponent}
  vector<pair<int, int>> componentInfo(n);
  vector<int> componentStarts;
  vector<ll> layout;
  vector<int> indexLayout;
  auto dfs2 = [&](auto &dfs2, int i, int parent, int curComponent) -> void {
    // add to cur component
    componentInfo[i] = {curComponent,
                        layout.size() - componentStarts[curComponent]};
    layout.push_back(values[i]);
    indexLayout.push_back(i);
    // follow heavy if applicable
    if (heavyEdgeGoingDown[i] != -1) {
      dfs2(dfs2, heavyEdgeGoingDown[i], i, curComponent);
    }
    // and then follow light edges. Each light edge gets their own component
    for (int conn : g[i]) {
      if (conn != parent && conn != heavyEdgeGoingDown[i]) {
        int nextComponent = componentStarts.size();
        componentStarts.push_back(layout.size());
        dfs2(dfs2, conn, i, nextComponent);
      }
    }
  };
  componentStarts.push_back(0);
  dfs2(dfs2, 0, -1, 0);
  Segtree stree(layout);

  auto maxOnPath = [&](int start, int end) {
    auto [curComponent, curIdx] = componentInfo[start];
    auto [endComponent, endIdx] = componentInfo[end];
    ll maxOnPath = 0;
    while (curComponent != endComponent) {
      maxOnPath = max(maxOnPath,
                      stree.rangeMax(componentStarts[curComponent],
                                     componentStarts[curComponent] + curIdx));

      // go to the next component
      int topOfComponent = indexLayout[componentStarts[curComponent]];
      auto nextInfo = componentInfo[lifts[topOfComponent][0]];
      curComponent = nextInfo.first;
      curIdx = nextInfo.second;
    }
    // now they share the same component
    // just query in between
    // assert(curIdx >= endIdx);
    maxOnPath =
        max(maxOnPath, stree.rangeMax(componentStarts[endComponent] + endIdx,
                                      componentStarts[endComponent] + curIdx));

    return maxOnPath;
  };

  // answer queries
  for (; q > 0; --q) {
    int qType;
    cin >> qType;
    if (qType == 1) {
      // change the value of the node
      int node, newValue;
      cin >> node >> newValue;
      auto [component, idx] = componentInfo[--node];
      stree.update(componentStarts[component] + idx, newValue);
    } else {
      // find max value on the path from a to b
      int a, b;
      cin >> a >> b;
      int lower = --a, higher = --b;
      if (depths[b] > depths[a]) {
        lower = b;
        higher = a;
      }
      // move lower up
      for (int k = MAX_K - 1; k >= 0; --k) {
        if (depths[lower] - (1 << k) >= depths[higher]) {
          lower = lifts[lower][k];
        }
      }
      int lca = higher;
      if (lower != higher) {
        for (int k = MAX_K - 1; k >= 0; --k) {
          if (lifts[lower][k] != -1 && lifts[lower][k] != lifts[higher][k]) {
            lower = lifts[lower][k];
            higher = lifts[higher][k];
          }
        }
        lca = lifts[lower][0];
        // assert(lca == lifts[higher][0] && lca != -1);
      }

      // now that we have the lca, time to use our heavy light decomposition
      // to find the max value on the path from a -> lca, b -> lca
      cout << max(maxOnPath(a, lca), maxOnPath(b, lca)) << ' ';
    }
  }
  cout << endl;
}