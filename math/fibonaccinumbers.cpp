#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll C = 1'000'000'007;
using Mat = vector<vector<ll>>;

// matrix multiplication
// any recursive function can be simulated with a transition matrix
// and then that transition matrix we can use binary exponentiation on
// to do many steps very fast
Mat matmul(const Mat &a, const Mat &b) {
  size_t rows = a.size();
  size_t cols = b[0].size();
  assert(a[0].size() == b.size());
  Mat result(rows, vector<ll>(cols));
  for (size_t r = 0; r < rows; ++r) {
    for (size_t c = 0; c < cols; ++c) {
      for (size_t inner = 0; inner < a[0].size(); ++inner) {
        result[r][c] += a[r][inner] * b[inner][c];
        result[r][c] %= C;
      }
    }
  }

  return result;
}
Mat identity(const size_t i) {
  Mat result(i, vector<ll>(i));
  for (size_t j = 0; j < i; ++j) {
    result[j][j] = 1;
  }
  return result;
}

int main() {
  const Mat transition = {{0, 1}, {1, 1}};
  const Mat initial = {{0, 1}}; // last term here is f(1)

  ll n;
  cin >> n;
  if (n == 0) {
    cout << 0 << endl;
    return 0;
  }
  n -= 1; // since last term in initial is f(1), subtract 1
  Mat result = {{1, 0}, {0, 1}};
  Mat curPow = transition;
  while (n > 0) {
    if (n % 2 == 1) {
      result = matmul(result, curPow);
    }
    curPow = matmul(curPow, curPow);
    n >>= 1;
  }
  // extract result by multiplying by initial
  Mat lastTerms = matmul(initial, result);
  cout << lastTerms[0].back() << endl;
}