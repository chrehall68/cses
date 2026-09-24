#include <bits/stdc++.h>
using namespace std;

struct LiftInfo {
  int parent;
  // cost to visit all coins in the subtree
  // given that start at a and end at b
  // b = parent
  int cost;
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int n, q;
  cin >> n >> q;
  vector<bool> hasCoin(n);
  int totalCoins;
  for (int i = 0; i < n; ++i) {
    int c;
    cin >> c;
    hasCoin[i] = c == 1;
    totalCoins += hasCoin[i];
  }
  vector<vector<int>> tree(n);
  for (int i = 0; i < n - 1; ++i) {
    int a, b;
    cin >> a >> b;
    tree[--a].push_back(--b);
    tree[b].push_back(a);
  }

  // dfs initially to compute cost to visit all coins in the subtree
  vector<int> coinsInSubtree(n);
  // cost to visit all coins in subtree, given that start and end at node i
  vector<int> costForSubtree(n);
  auto d1 = [&](auto &d1, int i, int parent) -> void {
    coinsInSubtree[i] = hasCoin[i];
    for (int conn : tree[i]) {
      if (conn != parent) {
        d1(d1, conn, i);
        if (coinsInSubtree[conn] > 0) {
          coinsInSubtree[i] += coinsInSubtree[conn];
          costForSubtree[i] += 2 + costForSubtree[conn];
        }
      }
    }
  };
  d1(d1, 0, -1);
  // reroot to compute
  // cost to visit all coins in parent subtree (excluding i) given that start
  // and end at i
  vector<int> costForParent(n);
  vector<int> costIfRootedAt(n);
  auto d2 = [&](auto &d2, int i, int parent) -> void {
    if (parent != -1) {
      int coinsInParent = totalCoins - coinsInSubtree[i];
      if (coinsInParent > 0) {
        // parent has coins that aren't just me
        // so need to do the reroot
        int myCostAsViewedByParent;
        if (coinsInSubtree[i] == 0) {
          myCostAsViewedByParent = 0;
        } else {
          myCostAsViewedByParent = 2 + costForSubtree[i];
        }

        // have to walk to the parent and explore all of those
        // and then walk back
        costForParent[i] =
            2 + (costIfRootedAt[parent] - myCostAsViewedByParent);
      } else {
        // parent has no coins, so no cost
        costForParent[i] = 0;
      }
    }
    costIfRootedAt[i] = costForSubtree[i] + costForParent[i];
    // then dfs further
    for (int conn : tree[i]) {
      if (conn != parent) {
        d2(d2, conn, i);
      }
    }
  };
  d2(d2, 0, -1);

  // now compute lifts
  // lifts need to store the additional information of
  // what is the cost to, starting at a and ending at b,
  // visit all coins in the subtrees along the path from a to b
  // which could be more than the cost of just visiting all coins in subtree b
  vector<vector<LiftInfo>> lifts(n);
  vector<int> depths(n);
  auto d3 = [&](auto &d3, int i, int parent) -> void {
    // compute lift
    for (size_t k = 0;
         k < lifts[i].size() && k < lifts[lifts[i][k].parent].size(); ++k) {
      LiftInfo myInfo = lifts[i][k];
      LiftInfo parentInfo = lifts[myInfo.parent][k];
      int nextCost =
          myInfo.cost + parentInfo.cost - costForSubtree[myInfo.parent];
      lifts[i].push_back(LiftInfo{parentInfo.parent, nextCost});
    }
    // dfs further
    for (int conn : tree[i]) {
      if (conn != parent) {
        // compute first lift
        if (coinsInSubtree[conn] == 0) {
          // wouldn't have visited this branch, but now have to
          lifts[conn].push_back(LiftInfo{i, 1 + costForSubtree[i]});
        } else {
          // would already have visited this branch, but now don't need to
          // double back
          lifts[conn].push_back(LiftInfo{i, costForSubtree[i] - 1});
        }
        depths[conn] = depths[i] + 1;
        d3(d3, conn, i);
      }
    }
  };
  d3(d3, 0, -1);

  // now finally answer queries
  int MAX_LCA = 21;
  for (; q > 0; --q) {
    int start, end;
    cin >> start >> end;
    --start;
    --end;
    // doesn't really matter that they're start and end
    // since we can just traverse every edge backwards
    int lower = start, higher = end;
    if (depths[lower] < depths[higher]) {
      swap(lower, higher);
    }
    // move lower up
    int totalCost = 0;
    {
      totalCost += costForSubtree[lower];
      for (int k = MAX_LCA; k >= 0; --k) {
        if (depths[lower] - (1 << k) >= depths[higher]) {
          // need to jump up this
          // don't double count lower
          LiftInfo info = lifts[lower][k];
          // totalCost = cost to visit all subtrees below and end at lower
          // so don't double-count lower
          // cost = cost to visit all subtrees in [lower..=parent]
          totalCost = totalCost + info.cost - costForSubtree[lower];
          lower = info.parent;
        }
      }
    }
    int lca = lower;
    if (lower != higher) {
      // lift both up, and be careful about the last case
      totalCost += costForSubtree[higher];
      for (int k = MAX_LCA; k >= 0; --k) {
        if (depths[lower] - (1 << k) >= 0 &&
            lifts[lower][k].parent != lifts[higher][k].parent) {
          // need to jump up this
          // don't double count lower
          LiftInfo info = lifts[lower][k];
          // totalCost = cost to visit all subtrees below and end at lower
          // so don't double-count lower
          // cost = cost to visit all subtrees in [lower..=parent]
          totalCost = totalCost + info.cost - costForSubtree[lower];
          lower = info.parent;

          // similar for higher
          info = lifts[higher][k];
          totalCost = totalCost + info.cost - costForSubtree[higher];
          higher = info.parent;
        }
      }
      assert(lower != higher);
      assert(lifts[lower][0].parent == lifts[higher][0].parent);
      lca = lifts[lower][0].parent;
      if (coinsInSubtree[lower] == 0 && coinsInSubtree[higher] == 0) {
        totalCost += 1 + 1 + costForSubtree[lca];
      } else if (coinsInSubtree[lower] == 0) {
        totalCost += 1 + (lifts[higher][0].cost - costForSubtree[higher]);
      } else if (coinsInSubtree[higher] == 0) {
        totalCost += 1 + (lifts[lower][0].cost - costForSubtree[lower]);
      } else {
        totalCost += lifts[lower][0].cost - costForSubtree[lower] -
                     costForSubtree[higher] - 1;
      }
    }
    // now just pay for visiting parent
    totalCost += costForParent[lca];

    cout << totalCost << '\n';
  }
}