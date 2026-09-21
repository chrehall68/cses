#include <algorithm>
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  // precompute triangle numbers
  const ll M = 1'000'000'000'000;
  ll curSum = 0;
  vector<ll> triangles;
  for (int i = 1; curSum <= M; curSum += i, i++) {
    triangles.push_back(curSum);
  }
  // greedily assigning largest triangle number doesn't work
  // consider n=12
  // best done by 6+6
  // but assigning biggest gives 10 + 1 + 1
  // well we know that a triangle number is x(x+1)//2
  // and the gaps between triangle numbers are x
  // so that means that if we look at the largest triangle number k
  // that is less than a given number n, then n - k must be around sqrt(n)
  // since n-k <= x, and x ~ sqrt(k) and k ~ n
  // maybe we can look to see whether we take the biggest number or we take
  // the second biggest
  // and then optimally precompute number of triangles needed for numbers <=
  // 10**6 actually we have 10**3 triangles, so for 10**6 that's a bit muchx so
  // according to gauss' theorem, every number can be written as the sum of 3
  // triangle numbers
  // so thus we can just precompute the triangle numbers and check whether one
  // or 2 works
  int t;
  for (cin >> t; t > 0; --t) {
    ll n;
    cin >> n;
    auto it = lower_bound(triangles.begin(), triangles.end(), n);
    if (it != triangles.end() && *it == n) {
      cout << 1 << endl;
    } else {
      // look through all ones
      int r = triangles.size() - 1;
      bool good = false;
      for (size_t i = 1; i < triangles.size() && !good && r >= 0; ++i) {
        while (r >= 0 && triangles[r] + triangles[i] > n) {
          r--;
        }
        good = r >= 0 && triangles[r] + triangles[i] == n;
      }
      if (good) {
        cout << 2 << endl;
      } else {
        cout << 3 << endl;
      }
    }
  }
}