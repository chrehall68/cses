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
int main() {
  // so we would intuitively just do
  // number_of_colors ** number_of_pearls
  // but that overcounts since we want it to
  // be rotation-independent
  // for every unique arrangement, there are number_of_pearls
  // possible ways to rotate it
  // so just divide by number_of_pearls at the end?
  // when every number is different, then it does get counted #pearls times
  // if every pearl is the same -> just #colors of these
  // if there are multiple?
  //
  ll pearls, colors;
  cin >> pearls >> colors;
  ll total = 0;
  // burnside's lemma
  // try all shifts (each shift is a symmetry in our symmetry group)
  for (ll shift = 0; shift < pearls; ++shift) {
    total += binpow(colors, gcd(shift, pearls));
    total %= C;
  }
  total *= modinv(pearls); // we have `pearls` symmetries in our symmetry group
  total %= C;
  cout << total << endl;
}