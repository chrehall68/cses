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
  // count the number of derangements
  // a b c d e
  // if put b at first, then either:
  // a takes b's spot, and then we solve # of derangements with n-2 items
  // a doesn't take b's spot, and then we solve # of derangements with n-1 items
  //   since we can think of it like a must not go to b's spot
  int n;
  cin >> n;
  vector<ll> derangements(n + 1);
  derangements[0] = 0;
  derangements[1] = 0;
  derangements[2] = 1;
  for (int curN = 3; curN <= n; ++curN) {
    derangements[curN] = ((ll)(curN - 1)) *
                         (derangements[curN - 2] + derangements[curN - 1]) % C;
  }
  cout << derangements[n] << endl;
}