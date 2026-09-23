#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int n, m, k;
  cin >> n >> m >> k;
  vector<pair<int, int>> edges;
  map<pair<int, int>, int> edgeToEdgeId;
  for (int i = 0; i < m; ++i) {
    int a, b;
    cin >> a >> b;
    edges.push_back({a, b});
    edgeToEdgeId[{min(a, b), max(a, b)}] = i;
  }
  vector<bool> willBreak(m);
  vector<int> breakdowns;
  for (int i = 0; i < k; ++i) {
    int a, b;
    cin >> a >> b;
    int edgeId = edgeToEdgeId[{min(a, b), max(a, b)}];
    willBreak[edgeId] = true;
    breakdowns.push_back(edgeId);
  }

  // turn back time approach
  // start by unioning everything else
  vector<int> reps(n + 1), sizes(n + 1, 1);
  iota(reps.begin(), reps.end(), 0);
  auto findRep = [&](auto &f, int i) -> int {
    if (reps[i] != i) {
      reps[i] = f(f, reps[i]);
    }
    return reps[i];
  };
  auto doUnion = [&](int i, int j) -> bool {
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
    return 0;
  };
  int components = n;
  for (int edgeId = 0; edgeId < m; ++edgeId) {
    if (!willBreak[edgeId]) {
      auto [a, b] = edges[edgeId];
      components -= doUnion(a, b);
    }
  }
  // for the turn back time part, after we add an edge
  // it's as if all the previous edges broke down
  vector<int> results;
  reverse(breakdowns.begin(), breakdowns.end());
  for (int edgeId : breakdowns) {
    results.push_back(components);
    auto [a, b] = edges[edgeId];
    components -= doUnion(a, b);
  }
  reverse(results.begin(), results.end());
  for (int numComponents : results) {
    cout << numComponents << ' ';
  }
  cout << endl;
}