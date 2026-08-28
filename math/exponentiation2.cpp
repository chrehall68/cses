#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll C = 1'000'000'007;

ll exponentiate(ll a, ll b, ll c) {
  ll res = 1;
  ll curPow = a;
  while (b > 0) {
    if (b % 2 == 1) {
      res *= curPow;
      res %= c;
    }
    curPow *= curPow;
    curPow %= c;
    b >>= 1;
  }
  return res;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int n;
  for (cin >> n; n > 0; --n) {
    // fermat's little theorem
    // a ** (p-1) === 1 mod p
    ll a, b, c;
    cin >> a >> b >> c;
    ll pow = exponentiate(b, c, C - 1);
    ll res = exponentiate(a, pow, C);
    cout << res << endl;
  }
}