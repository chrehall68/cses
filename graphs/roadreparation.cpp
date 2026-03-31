#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ll n, m;
  cin >> n >> m;
  vector<tuple<ll, ll, ll>> edges;
  vector<ll> reps(n), sizes(n, 1);
  iota(reps.begin(), reps.end(), 0);
  function<ll(ll)> findRep = [&](ll i) {
    if (reps[i] != i) {
      reps[i] = findRep(reps[i]);
    }
    return reps[i];
  };
  function<void(ll, ll)> doUnion = [&](ll i, ll j) {
    ll ri = findRep(i), rj = findRep(j);
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
  for (ll i = 0; i < m; ++i) {
    ll a, b, cost;
    cin >> a >> b >> cost;
    edges.push_back({cost, --a, --b});
  }
  sort(edges.begin(), edges.end());
  ll total = 0;
  for (auto [cost, a, b] : edges) {
    if (findRep(a) != findRep(b)) {
      doUnion(a, b);
      total += cost;
    }
  }
  if (find(sizes.begin(), sizes.end(), n) != sizes.end()) {
    cout << total << endl;
  } else {
    cout << "IMPOSSIBLE" << endl;
  }
}