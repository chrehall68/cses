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
  cin >> n;
  if (n % 2 == 1) {
    cout << 0 << endl;
    return 0;
  }
  int brackets = n / 2;
  // so n**2 way is to just dp
  // we know exactly 1 way to place 1 brackets
  // and we know exactly 1 way to place 0 brackets
  // then for every amount of contained brackets, consider placing that amount
  // inside and remaining amount after thus we get ways[i] =
  // sum(ways[inside]*ways[i-1-inside] for inside in 0..=i-1)
  // but that's just the catalan numbers
  cout << comb(2 * brackets, brackets) * modinv(brackets + 1) % C << endl;

  cout << endl;
}