#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using lll = __int128_t;

ll binpow(ll x, ll y, const ll C) {
  lll res = 1;
  lll curPow = x % C;
  while (y > 0) {
    if (y & 1) {
      res *= curPow;
      res %= C;
    }
    curPow *= curPow;
    curPow %= C;
    y >>= 1;
  }

  return (ll)res;
}
// fermat's theorem states that
// p is prime -> for all bases a, a**(p-1) === 1 mod p
// and miller rabin extends this by saying that
// p is prime AND p is not 2 -> 2 | p-1
// thus p-1 = 2**x d where d is odd
// thus a**(2**x d) -1 === 0 mod p
// thus (a**(2**(x-1) d)+1)(a**(2**(x-1) d) -1) === 0 mod p
// and we can keep breaking up the -1 side until we get
// (a**(2**(x-1) d)+1)(a**(2**(x-2) d)+1)(a**(2**(x-3) d)+1)...
// ... (a**d +1)(a**d -1)
// so now for this to be congruent to 0, at least one of these factors
// must be equal to 0
// if NONE of them are equal to 0, then p is not prime
// if there is one equal to 0, tells us nothing
// p = 2**x * d + 1
bool isComposite(ll p, ll d, ll x, ll base) {
  // start by checking a**d, then a** 2d, then a**4d, etc
  lll cur = binpow(base, d, p); // need lll's since do multiplication
  if (cur == 1 || cur == p - 1) {
    // product is 0 since this makes either term a**d -1 === 0
    // or term a**d +1 === 0
    return false;
  }
  for (ll curX = 1; curX <= x; ++curX) {
    cur = cur * cur % p;
    // now check 2**curX d
    if (cur == p - 1) {
      return false;
    }
  }
  // none of them are 0, so we know it's definitely composite
  return true;
}
bool isPrimeMillerRabin(ll p, size_t iters = 10) {
  // factor p-1 into 2**x, d
  if (p <= 1) {
    return false;
  }
  if (p == 2) {
    return true;
  }
  ll d = p - 1;
  ll x = 0;
  while (d % 2 == 0) {
    d >>= 1;
    x++;
  }
  // now sample randomly
  bool composite = false;
  for (size_t iter = 1; iter <= iters && !composite; ++iter) {
    ll base = 2 + rand() % (p - 2); // don't check 0 or 1
    composite = isComposite(p, d, x, base);
  }
  return !composite;
}

int main() {
  int t;
  for (cin >> t; t > 0; --t) {
    ll num;
    cin >> num;
    for (num++; !isPrimeMillerRabin(num); ++num)
      ;
    cout << num << endl;
  }
}