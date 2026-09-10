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
  int n;
  string prefix;
  cin >> n;
  cin >> prefix;
  if (n % 2 == 1) {
    cout << 0 << endl;
    return 0;
  }
  // first check validity of prefix. If it's valid, then we have some number
  // of dangling opens
  // then we need to place x=(# of dangling opens) on the rhs
  // and we also need to generate a valid sequence of n-(prefix)-x characters
  // so we just scatter the x among the n-(prefix)-x+1 slots
  // (+1 because could place the brackets after the last)
  // and each of these slots can be reused
  // so its stars and bars
  ll x = 0;
  for (char c : prefix) {
    if (c == '(') {
      x++;
    } else {
      x--;
    }
    if (x < 0) {
      cout << 0 << endl;
      return 0;
    }
  }
  if (n < prefix.size() + x) {
    cout << 0 << endl;
    return 0;
  }
  // valid
  // so now we see that we have a convolution on catalan numbers
  // and that convolution works out to the below
  assert((n - prefix.size() - x) % 2 == 0);
  int remainingPairs = (n - prefix.size() - x) / 2;
  cout << (x + 1) * modinv(remainingPairs + x + 1) % C *
              comb(2 * remainingPairs + x, remainingPairs) % C
       << endl;
}