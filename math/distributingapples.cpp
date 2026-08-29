#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll C = 1'000'000'007;

vector<ll> factorials = {1, 1};
ll factorial(size_t n) {
  while (factorials.size() <= n) {
    factorials.push_back(factorials.back() * factorials.size() % C);
  }
  return factorials[n];
}
ll modinv(ll v) {
  if (v <= 1) {
    return v;
  }
  return C - C / v * modinv(C % v) % C;
}
ll comb(ll n, ll k) {
  ll numerator = factorial(n);
  ll denominator = factorial(n - k) * factorial(k) % C;
  return numerator * modinv(denominator) % C;
}
int main() {
  // this is multinomial coefficient
  // ie Pr(n, r1, r2, ..., rk)
  ll n, m;
  cin >> n >> m;
  // m bins, n items
  // distribute n items into m bins
  // just C(n+m-1, m)
  cout << comb(n + m - 1, m) << endl;
}