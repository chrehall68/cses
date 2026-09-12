#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll C = 1'000'000'007;
ll modinv(ll v) {
  if (v <= 1) {
    return v;
  }
  return C - C / v * modinv(C % v) % C;
}

// row reduction problem
// using long longs for precision
// n equations, m variables
// xs holds the coefficients for x1..=xm
// and bs is the rhs
// if there is no solution, an empty vector will be returned
optional<vector<ll>> rowReduce(vector<vector<ll>> xs, vector<ll> bs) {
  assert(xs.size() == bs.size());
  const size_t m = xs[0].size();
  for (size_t row = 0; row < xs.size(); ++row) {
    xs[row].push_back(bs[row]);
  }
  // < m that way don't touch bs
  vector<pair<size_t, size_t>> pivots;
  for (size_t pivot = 0; pivot < m; ++pivot) {
    // scan for something that has this set and not the previous
    int chosen = -1;
    for (size_t row = 0; row < xs.size() && chosen == -1; ++row) {
      if (xs[row][pivot] != 0) {
        bool good = true;
        for (size_t x = 0; x < pivot; ++x) {
          good = good && xs[row][x] == 0;
        }
        if (good) {
          chosen = row;
        }
      }
    }
    if (chosen == -1) {
      continue;
    }
    pivots.push_back({chosen, pivot});
    // there's an actual thing with this set
    // so need to reduce
    // first, normalize row
    ll coef = modinv(xs[chosen][pivot]);
    for (size_t x = 0; x <= m; ++x) {
      xs[chosen][x] *= coef;
      xs[chosen][x] %= C;
    }
    assert(xs[chosen][pivot] == 1);
    // then reduce against all other rows
    for (size_t row = 0; row < xs.size(); ++row) {
      if (row != chosen && xs[row][pivot] != 0) {
        ll coef = xs[row][pivot];
        for (size_t x = 0; x <= m; ++x) {
          xs[row][x] = ((xs[row][x] - coef * xs[chosen][x] % C) % C + C) % C;
        }
      }
    }
  }
  // now that we've finished reducing, simply check consistency
  vector<ll> values(m);
  for (auto [row, pivot] : pivots) {
    assert(xs[row][pivot] == 1);
    values[pivot] = xs[row][m]; // assign to the constant
  }
  // then just check
  bool good = true;
  for (auto &row : xs) {
    ll dot = 0;
    for (size_t x = 0; x < m; ++x) {
      dot = (dot + values[x] * row[x]) % C;
    }
    good = good && dot == row[m];
  }
  if (good) {
    return values;
  }
  return nullopt;
}

int main() {
  // this seems like a row reduction problem
  int n, m;
  cin >> n >> m;
  vector<vector<ll>> xs(n, vector<ll>(m));
  vector<ll> bs(n);
  for (int i = 0; i < n; ++i) {
    for (int x = 0; x < m; ++x) {
      cin >> xs[i][x];
    }
    cin >> bs[i];
  }
  optional<vector<ll>> res = rowReduce(xs, bs);
  if (res != nullopt) {
    for (ll num : *res) {
      cout << num << ' ';
    }
    cout << endl;
  } else {
    cout << -1 << endl;
  }
}