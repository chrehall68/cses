#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int n, m, q;
  cin >> n >> m >> q;
  vector<tuple<int, int, int>> edges;
  map<int, vector<int>> edgesByWeight;
  for (int i = 0; i < m; ++i) {
    int a, b, w;
    cin >> a >> b >> w;
    edges.push_back({w, a, b});
    edgesByWeight[w].push_back(edges.size() - 1);
  }

  // for every query, we want to group its query items by weight
  // queriesByWeight[weight] = { {queryIdx, {edgesWithThisWeight}}, ... }
  map<int, vector<pair<int, vector<int>>>> queriesByWeight;
  for (int queryId = 0; queryId < q; queryId++) {
    int amt;
    map<int, vector<int>> groupedByWeight;
    for (cin >> amt; amt > 0; --amt) {
      int edgeId;
      cin >> edgeId;
      --edgeId;
      groupedByWeight[get<0>(edges[edgeId])].push_back(edgeId);
    }
    // then insert this
    for (auto [w, group] : groupedByWeight) {
      queriesByWeight[w].push_back({queryId, group});
    }
  }
  vector<pair<int, int>> repsAndSizes(n + 1);
  const pair<int, int> UNTOUCHED = {-1, -1};
  vector<pair<int, int>> originals(n + 1, UNTOUCHED);
  vector<int> touchedIdxs;
  for (int i = 1; i <= n; ++i) {
    repsAndSizes[i] = {i, 1};
  }

  auto maybeBackup = [&](int i) {
    if (originals[i] == UNTOUCHED) {
      originals[i] = repsAndSizes[i];
      touchedIdxs.push_back(i);
    }
  };
  auto findRep = [&](auto &f, int i) -> int {
    if (repsAndSizes[i].first != i) {
      maybeBackup(i);
      repsAndSizes[i].first = f(f, repsAndSizes[i].first);
    }
    return repsAndSizes[i].first;
  };
  auto doUnion = [&](int i, int j) {
    int ri = findRep(findRep, i);
    int rj = findRep(findRep, j);
    if (ri != rj) {
      // store backups
      maybeBackup(ri);
      maybeBackup(rj);

      if (repsAndSizes[ri].second > repsAndSizes[rj].second) {
        repsAndSizes[ri].second += repsAndSizes[rj].second;
        repsAndSizes[rj].first = ri;
      } else {
        repsAndSizes[rj].second += repsAndSizes[ri].second;
        repsAndSizes[ri].first = rj;
      }
    }
  };
  // similar to previous kruskal's idea
  // but now need to make sure that edges within a (set, cost)
  // don't make a cycle
  vector<bool> queryIsGood(q, true);
  for (auto &[weight, edgeIds] : edgesByWeight) {
    // first, look through all queries
    for (auto &[queryId, group] : queriesByWeight[weight]) {
      for (int edgeId : group) {
        auto [_, a, b] = edges[edgeId];
        int repA = findRep(findRep, a);
        int repB = findRep(findRep, b);
        // they must not be in the same component
        queryIsGood[queryId] = queryIsGood[queryId] && repA != repB;
        doUnion(repA, repB);
      }
      // but then undo our operations
      for (int touchedIdx : touchedIdxs) {
        repsAndSizes[touchedIdx] = originals[touchedIdx];
        originals[touchedIdx] = UNTOUCHED;
      }
      touchedIdxs.clear();
    }
    // then update our tree
    for (int edgeId : edgeIds) {
      auto [_, a, b] = edges[edgeId];
      doUnion(a, b);
    }
    // and mark everything as untouched
    for (int touchedIdx : touchedIdxs) {
      originals[touchedIdx] = UNTOUCHED;
    }
    touchedIdxs.clear();
  }
  for (int b : queryIsGood) {
    if (b) {
      cout << "YES" << '\n';
    } else {
      cout << "NO" << '\n';
    }
  }
}