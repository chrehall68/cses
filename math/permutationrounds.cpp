#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll C = 1'000'000'007;

ll binpow(ll x, ll y) {
  ll res = 1;
  ll curPow = x % C;
  while (y > 0) {
    if (y & 1) {
      res *= curPow;
      res %= C;
    }
    curPow *= curPow;
    curPow %= C;
    y >>= 1;
  }
  return res;
}

int main() {
  // seems like everything should form some cycles
  // since we have n vertices and one outgoing edge from each vertex
  // so then just becomes when do the cycles meet
  // yeah beause the edges are also to unique things
  int n;
  cin >> n;
  vector<int> edgeTo(n + 1);
  vector<int> reps(n + 1);
  iota(reps.begin(), reps.end(), 0);
  vector<int> sizes(n + 1, 1);
  auto findRep = [&](auto &findRep, int i) -> int {
    if (reps[i] != i) {
      reps[i] = findRep(findRep, reps[i]);
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
  for (int i = 1; i <= n; ++i) {
    int j;
    cin >> j;
    doUnion(i, j);
  }
  // factorize numbers 1 to n
  // we do this that way we can compute lcm without having a huge number
  vector<bool> isPrime(n + 1, true);
  vector<vector<pair<int, int>>> factors(n + 1);
  for (int i = 2; i <= n; ++i) {
    if (isPrime[i]) {
      for (int j = i; j <= n; j += i) {
        isPrime[j] = false;
        int cnt = 0;
        int cur = j;
        while (cur % i == 0) {
          cur /= i;
          cnt++;
        }
        factors[j].push_back({i, cnt});
      }
    }
  }
  // get cycle sizes
  map<ll, int> factorCounts;
  for (int i = 1; i <= n; ++i) {
    if (findRep(findRep, i) == i) {
      for (auto [factor, cnt] : factors[sizes[i]]) {
        factorCounts[factor] = max(factorCounts[factor], cnt);
      }
    }
  }
  // expand
  ll lcm = 1;
  for (auto [factor, cnt] : factorCounts) {
    lcm = lcm * binpow(factor, cnt) % C;
  }
  cout << lcm % C << endl;
}