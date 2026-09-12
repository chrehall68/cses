#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int t;
  for (cin >> t; t > 0; --t) {
    ll n;
    cin >> n;

    // fix largest number
    // and then the rest will be pretty small
    ll a = sqrt(n);
    optional<tuple<ll, ll, ll, ll>> res;
    while (res == nullopt) {
      // should eventually find something
      ll remaining = n - a * a;
      // we factor remaining in sqrt(remaining)**2 = O(remaining)
      // normally, we'll find `a` pretty fast
      // however, in the worst case, the maximum number chosen must be >=
      // sqrt(n/4) = sqrt(n)/2
      // thus we could check up to sqrt(n)/2 items and
      // each of these iterations requires O(n) work since when a = sqrt(n)/2,
      // n- (sqrt(n)/2)**2 = n- n/4 = 3n/4 = O(n)
      // thus in total, this takes O(n**3/2)
      // which, for n=10**7, is too slow
      for (ll b = sqrt(remaining); b >= 0 && res == nullopt; --b) {
        for (ll c = sqrt(remaining - b * b); c >= 0 && res == nullopt; --c) {
          ll d = sqrt(remaining - b * b - c * c);
          if (d * d + b * b + c * c == remaining) {
            res = {a, b, c, d};
          }
        }
      }
      a--;
    }
    auto [aa, b, c, d] = *res;
    cout << aa << ' ' << b << ' ' << c << ' ' << d << endl;
  }
}