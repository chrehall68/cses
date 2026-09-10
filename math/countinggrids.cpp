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
  // this seems like another burnside's lemma problem
  // since we have 4 symmetries:
  // - don't rotate -> fixes everything
  // - rotate 90* once
  // - rotate 90* twice
  // - rotate 90* three times
  ll n;
  cin >> n;
  // don't rotate
  ll total = binpow(2, n * n);
  // rotate 90* and 270*
  if (n % 2 == 0) {
    total += 2 * binpow(2, n / 2 * n / 2);
  } else {
    total += 2 * binpow(2, n / 2 * ((n + 1) / 2) + 1);
  }
  total %= C;
  // rotate 180*
  if (n % 2 == 0) {
    total += binpow(2, n * n / 2);
  } else {
    total += binpow(2, n * (n / 2) + (n + 1) / 2);
  }
  total %= C;
  //   cout << total << endl;
  cout << total * modinv(4) % C << endl;
}