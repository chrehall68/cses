#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll C = 1'000'000'007;
const ll M = 2'000'000'000'000'000'000LL;
using Mat = vector<vector<ll>>;

// twist on matrix exponentiation that still
// relies on doubling
// but our transition is now adapted for the problem:
// the shortest path from x to y after 2k paths is
// min(shortest path from x to inner + shortest path from inner to y)
// for every inner (given that those paths go through k nodes)
Mat shortestPaths(const Mat &a, const Mat &b) {
  size_t rows = a.size();
  size_t cols = b[0].size();
  assert(a[0].size() == b.size());
  Mat result(rows, vector<ll>(cols, M));
  for (size_t x = 0; x < rows; ++x) {
    for (size_t y = 0; y < cols; ++y) {
      for (size_t inner = 0; inner < a[0].size(); ++inner) {
        result[x][y] = min(result[x][y], a[x][inner] + b[inner][y]);
      }
    }
  }

  return result;
}
int main() {
  // maybe we can do a similar idea to gridpaths1
  // except this time, we'll store shortest path from x to y
  // for all x,y
  // with exactly 2**i edges
  // and we can easily double that
  // and then we can combine it to get our shortest paths with exactly k edges
  int n, m, k;
  cin >> n >> m >> k;
  Mat curPow(n, vector<ll>(n, M));
  for (int i = 0; i < m; ++i) {
    int a, b, c;
    cin >> a >> b >> c;
    --a;
    --b;
    curPow[a][b] = min(curPow[a][b], (ll)c);
  }
  Mat result(n, vector<ll>(n, M));
  result[0][0] = 0;

  while (k > 0) {
    if (k & 1) {
      result = shortestPaths(result, curPow);
    }
    curPow = shortestPaths(curPow, curPow);
    k >>= 1;
  }
  if (result[0][n - 1] == M) {
    cout << -1 << endl;
  } else {
    cout << result[0][n - 1] << endl;
  }
}