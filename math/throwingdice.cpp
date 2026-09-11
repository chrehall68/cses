#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const ll C = 1'000'000'007;
using Mat = vector<vector<ll>>;

// matrix multiplication / exponentiation
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
  // count number of ways to distribute n identical objects into any number of
  // identical bins
  // first idea is that if we fix the amount of objects, then this can become
  // sum(number of ways to distribute n identical objects into k identical
  // nonempty bins for k in 1..=n)
  // we do have the restriction that each number must be between 1 and 6 though
  // maybe that can help us?
  // maybe we can think of generating functions?
  // like we have (x + x**2 + x**3 + x**4 + x**5 + x**6)
  // for a single die
  // and then we want the coefficient of x**n
  // and we can use any power of this expression
  // hmmm but that seems to double count since it treats the dice as distinct
  // maybe we think about how many 6's, how many 5's, how many 4's, ... how many
  // 1's but it feels like that would require a dp like for every x in 0..=n,
  // how many ways are there to make x where the highest number placeable is i
  // (for every i in 1..=6) maybe we're overcomplicating this maybe we can
  // actually consider each dice distinct because if we can, then we can solve
  // it as a recurrence relation where f0 and less = 0 f1 = 1 fx = f(x-1) +
  // f(x-2) + f(x-3) + ... + f(x-6)
  Mat initial = {{0, 0, 0, 0, 0, 1}}; // exactly 1 way to make sum of 0
  const Mat transition = {{0, 1, 0, 0, 0, 0}, {0, 0, 1, 0, 0, 0},
                          {0, 0, 0, 1, 0, 0}, {0, 0, 0, 0, 1, 0},
                          {0, 0, 0, 0, 0, 1}, {1, 1, 1, 1, 1, 1}};
  ll n;
  cin >> n; // since last term in initial is f(0), no need to subtract
  Mat curPow = transition;
  Mat result = identity(transition.size());
  while (n > 0) {
    if (n & 1) {
      result = matmul(result, curPow);
    }
    curPow = matmul(curPow, curPow);
    n >>= 1;
  }
  Mat lastTerms = matmul(initial, result);
  cout << lastTerms[0].back() << endl;
}