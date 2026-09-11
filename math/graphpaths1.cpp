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
  // if we knew the number of ways to get from node 1 to every other node using
  // exactly x steps then we could use that to count the number of ways to get
  // from node 1 to every other node using exactly x+1 steps by just following
  // all directed edges
  int n, m, k;
  cin >> n >> m >> k;
  Mat transition(n, vector<ll>(n));
  for (int i = 0; i < m; ++i) {
    int a, b;
    cin >> a >> b;
    transition[--a][--b]++;
  }
  Mat initial(1, vector<ll>(n));
  initial[0][0] = 1; // exactly 1 way to get from node 1 to node 1 using 0 steps
  Mat result = identity(n);
  Mat curPow = transition;
  while (k > 0) {
    if (k & 1) {
      result = matmul(result, curPow);
    }
    curPow = matmul(curPow, curPow);
    k >>= 1;
  }
  Mat lastTerms = matmul(initial, result);
  cout << lastTerms[0].back() << endl;
}