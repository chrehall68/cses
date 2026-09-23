#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int n, m;
  cin >> n >> m;
  vector<tuple<int, int, int>> edges;
  map<int, vector<int>> edgesByWeight;
  for (int i = 0; i < m; ++i) {
    int a, b, w;
    cin >> a >> b >> w;
    edges.push_back({w, a, b});
    edgesByWeight[w].push_back(edges.size() - 1);
  }

  // so if an edge was not in our mst
  // it completes a cycle
  // then we need to remove the maximum on that cycle
  // and in order to do that, if we already have our tree
  // then we just query what's the max on the path from a -> b
  // and that's something that we can do with lca
  // and then the extra cost is just my_value - prev_max_value
  // so basically:
  // - build mst and calculate cost
  // - compute lifts
  // - treat all edges that aren't in the mst as queries
  vector<int> reps(n + 1), sizes(n + 1, 1);
  iota(reps.begin(), reps.end(), 0);
  auto findRep = [&](auto &f, int i) -> int {
    if (reps[i] != i) {
      reps[i] = f(f, reps[i]);
    }
    return reps[i];
  };
  auto doUnion = [&](int i, int j) {
    int ri = findRep(findRep, i);
    int rj = findRep(findRep, j);
    if (ri != rj) {
      if (sizes[ri] > sizes[rj]) {
        sizes[ri] += sizes[rj];
        reps[rj] = ri;
      } else {
        sizes[rj] += sizes[ri];
        reps[ri] = rj;
      }
      return true;
    }
    return false;
  };
  // build original mst
  vector<bool> inMst(m);
  vector<int> edgeIdsInMst;
  vector<vector<pair<int, int>>> mst(n + 1);
  ll mstCost = 0;
  for (auto &[w, edgeIds] : edgesByWeight) {
    for (int edgeId : edgeIds) {
      auto [_, a, b] = edges[edgeId];
      if (doUnion(a, b)) {
        mstCost += w;

        edgeIdsInMst.push_back(edgeId);
        inMst[edgeId] = true;

        mst[a].push_back({b, w});
        mst[b].push_back({a, w});
      }
    }
  }
  // now calculate lifts
  // lifts[node][i] = {2**i'th parent, max cost to get to 2**i'th parent}
  vector<vector<pair<int, ll>>> lifts(n + 1);
  vector<int> depths(n + 1);
  auto dfs = [&](auto &dfs, int i, int parent) -> void {
    // compute my lifts
    for (int l = 0; l < lifts[i].size() && l < lifts[lifts[i][l].first].size();
         ++l) {
      auto [myParent, myCost] = lifts[i][l];
      auto [nextParent, theirCost] = lifts[myParent][l];
      lifts[i].push_back({nextParent, max(myCost, theirCost)});
    }
    // then dfs
    for (auto [conn, cost] : mst[i]) {
      if (conn != parent) {
        depths[conn] = depths[i] + 1;
        lifts[conn].push_back({i, cost});
        dfs(dfs, conn, i);
      }
    }
  };
  depths[1] = 0;
  dfs(dfs, 1, 0);

  // now just handle all queries
  const int MAX_LCA = 21;
  for (int edgeId = 0; edgeId < m; ++edgeId) {
    ll cost = mstCost;
    if (!inMst[edgeId]) {
      // this completes a cycle, so we just need to
      // find the maximum edge on the path from a to b by going to their lca
      auto [w, a, b] = edges[edgeId];
      int lower = a, higher = b;
      if (depths[lower] < depths[higher]) {
        swap(lower, higher);
      }
      // move lower up
      ll extra = 0;
      for (int i = MAX_LCA; i >= 0; --i) {
        if (depths[lower] - (1 << i) >= depths[higher]) {
          auto [nextLower, maxOnPath] = lifts[lower][i];
          extra = max(extra, maxOnPath);
          lower = nextLower;
        }
      }
      // then move both up
      if (lower != higher) {
        for (int i = MAX_LCA; i >= 0; --i) {
          if (i < lifts[lower].size() &&
              lifts[lower][i].first != lifts[higher][i].first) {
            auto [nextLower, maxOnPathL] = lifts[lower][i];
            extra = max(extra, maxOnPathL);
            lower = nextLower;

            auto [nextHigher, maxOnPathH] = lifts[higher][i];
            extra = max(extra, maxOnPathH);
            higher = nextHigher;
          }
        }
        assert(lower != higher);
        assert(lifts[lower][0].first == lifts[higher][0].first);
        extra = max(extra, lifts[lower][0].second);
        extra = max(extra, lifts[higher][0].second);
      }

      cost += w - extra;
    }
    cout << cost << '\n';
  }
}