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
  string s;
  cin >> s;
  vector<int> counts(26);
  for (char c : s) {
    counts[c - 'a']++;
  }
  ll n = s.size();
  ll prod = 1;
  for (int i = 0; i < 26; ++i) {
    if (counts[i] > 0) {
      prod = prod * comb(n, counts[i]) % C;
      n -= counts[i];
    }
  }
  cout << prod << endl;
}