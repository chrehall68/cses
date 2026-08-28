#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll C = 1'000'000'007;
ll binpow(ll x, ll y) {
  ll res = 1;
  ll curPow = x % C;
  while (y > 0) {
    if (y & 1) {
      res *= curPow;
      res %= C;
    }
    curPow *= curPow;
    curPow %= C;
    y >>= 1;
  }
  return res;
}
ll modinv(ll v) {
  if (v <= 1) {
    return v;
  }
  return C - C / v * modinv(C % v) % C;
}
// sum of all elements in a geometric series up to p**n
ll geometric(ll p, ll n) {
  ll numerator = (1 - binpow(p, n + 1) + C) % C;
  ll denominator = (1 - p + C) % C;
  return numerator * modinv(denominator) % C;
}
int main() {
  // finding the number of divisors is easy
  // if you have a number p1**x1 p2**x2 p3**x3 ...
  // you can choose to use 0..=x1 of p1, 0..=x2 of p2, etc
  // and each of these choices is independent and results in a different number
  // so just product(x_i + 1)

  // if we had exactly one factor, we could use geometric series sum
  // since we have 1 + p + p**2 + p**3 + ... + p**x
  // then maybe we can build off of that?
  // suppose we have the sum of the divisors for some number x
  // and we now add another new factor p**y
  // then our new sum of divisors is
  // sum*1 + sum*p + sum*p**2 + sum*p**3 + ...
  // = sum (1 + p * p**2 + p**3 + ... + p**y)

  // what about for the product?
  // if we had exactly one prime factor, we have the factors
  // 1, p, p**2, p**3, ..., p**x
  // which gives us a product of p** (0+1+2+3+...+x)
  // = p**(x*(x+1)/2)
  // then suppose we have the product of the divisors for some number x
  // and we add a new factor p**y
  // then our new divisors are
  // (old divisors), (old divisors)*p, (old divisors)*p**2, ...
  // and thus our new product is
  // prod * prod*(p**num_divisors) * prod*((p**2)**num_divisors)
  // * ... * prod*((p**y)**num_divisors)
  // = prod**(y+1) * p**((0+1+2+...+y)*num_divisors)
  // = prod**(y+1) * p**( y*(y+1)/2 * num_divisors )

  ll n;
  ll distinct = 1;
  // do this instead of converting from mod C to mod C-1
  // since the operation is pretty simple
  ll distinctModCM1 = 1;
  ll sum = 1;
  ll prod = 1;
  for (cin >> n; n > 0; --n) {
    ll p, cnt;
    cin >> p >> cnt;
    // mod C-1 since a**(p-1) = 1 mod p
    ll pPow = cnt * (cnt + 1) / 2 % (C - 1) * distinctModCM1 % (C - 1);
    prod = binpow(prod, cnt + 1) * binpow(p, pPow) % C;
    distinctModCM1 = distinctModCM1 * (cnt + 1) % (C - 1);
    distinct = distinct * (cnt + 1) % C;
    sum = sum * geometric(p, cnt) % C;
  }
  cout << distinct << endl;
  cout << sum << endl;
  cout << prod << endl;
}
