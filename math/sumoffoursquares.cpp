#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  // precompute, up to 10**7, whether a number is the sum of 2 squares
  const int M = 10'000'000;
  vector<optional<pair<int, int>>> isSumOf2(M + 1);
  for (int a = 0; a * a <= M; ++a) {
    for (int b = 0; b * b + a * a <= M; ++b) {
      isSumOf2[a * a + b * b] = {a, b};
    }
  }

  int t;
  for (cin >> t; t > 0; --t) {
    int n;
    cin >> n;
    optional<tuple<int, int, int, int>> res;
    for (int a = 0; a <= n && res == nullopt; ++a) {
      int rem = n - a;
      if (isSumOf2[a] != nullopt && isSumOf2[rem] != nullopt) {
        res = {isSumOf2[a]->first, isSumOf2[a]->second, isSumOf2[rem]->first,
               isSumOf2[rem]->second};
      }
    }
    auto [a, b, c, d] = *res;
    cout << a << ' ' << b << ' ' << c << ' ' << d << endl;
  }
}