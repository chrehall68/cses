#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll C = 1'000'000'007;

int main() {
  int n;
  for (cin >> n; n > 0; --n) {
    ll a, b;
    cin >> a >> b;
    ll res = 1;
    ll curPow = a;
    while (b > 0) {
      if (b % 2 == 1) {
        res *= curPow;
        res %= C;
      }
      curPow *= curPow;
      curPow %= C;
      b >>= 1;
    }
    cout << res << endl;
  }
}