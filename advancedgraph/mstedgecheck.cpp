#include <bits/stdc++.h>
using namespace std;

int main() {
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
    }
  };
  // idea is just use kruskal's but don't add things
  // of the same weight until you've looked through all of them
  vector<bool> inMst(m);
  for (auto &[_weight, edgeIds] : edgesByWeight) {
    for (int edgeId : edgeIds) {
      auto [_w, a, b] = edges[edgeId];
      inMst[edgeId] = findRep(findRep, a) != findRep(findRep, b);
    }
    // then add them
    for (int edgeId : edgeIds) {
      auto [_w, a, b] = edges[edgeId];
      doUnion(a, b);
    }
  }
  for (bool b : inMst) {
    if (b) {
      cout << "YES" << endl;
    } else {
      cout << "NO" << endl;
    }
  }
}