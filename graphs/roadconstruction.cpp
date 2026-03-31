#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ll n, m;
  cin >> n >> m;
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
  ll components = n;
  ll maxSize = 1;
  for (ll i = 0; i < m; ++i) {
    ll a, b;
    cin >> a >> b;
    if (findRep(--a) != findRep(--b)) {
      doUnion(a, b);
      --components;
      maxSize = max(maxSize, sizes[findRep(a)]);
    }
    cout << components << ' ' << maxSize << '\n';
  }
}