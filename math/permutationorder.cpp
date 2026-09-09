#include <bits/stdc++.h>
#include <vector>
using namespace std;
using ll = unsigned long long;

int main() {
  // 1 2 3 4 5 6
  // 1 2 3 4 6 5
  // 1 2 3 5 4 6
  // 1 2 3 5 6 4
  // 1 2 3 6 4 5
  // 1 2 3 6 5 4
  // 1 2 4 3 5 6
  // 1 2 4 3 6 5
  // 1 2 4 5 3 6
  // 1 2 4 5 6 3
  // 1 2 4 6 3 5
  // 1 2 4 6 5 3
  // 1 2 5 3 4 6
  // 1 2 5 3 6 4
  // 1 2 5 4 3 6
  // 1 2 5 4 6 3
  // 1 2 5 6 3 4
  // 1 2 5 6 4 3
  // 1 2 6 3 4 5
  // 1 2 6 3 5 4
  // 1 2 6 4 3 5
  // 1 2 6 4 5 3
  // 1 2 6 5 3 4
  // 1 2 6 5 4 3
  const int M = 20;
  vector<ll> amts(M);
  amts[0] = 0;
  amts[1] = 1;
  for (ll n = 2; n < M; ++n) {
    amts[n] = n * amts[n - 1];
  }

  int t;
  for (cin >> t; t > 0; --t) {
    int op;
    cin >> op;
    if (op == 1) {
      // generate the permutation
      ll n, k;
      cin >> n >> k;

      // iterate through
      vector<int> digits;
      set<int> remainingDigits;
      for (int i = 1; i <= n; ++i) {
        remainingDigits.insert(i);
      }
      for (int pos = 1; pos <= n; ++pos) {
        int remaining = n - pos;
        auto dig = remainingDigits.begin();
        ll numLess = 0;
        while (dig != remainingDigits.end() && numLess * amts[remaining] < k) {
          numLess++;
          dig++;
        }
        // now dig is one past
        --dig;
        --numLess;
        k -= numLess * amts[remaining];
        digits.push_back(*dig);
        remainingDigits.erase(dig);
      }
      // output
      for (int dig : digits) {
        cout << dig << ' ';
      }
      cout << endl;
    } else {
      int n;
      cin >> n;
      vector<int> digits(n);
      for (int &dig : digits) {
        cin >> dig;
      }
      ll k = 1;
      set<int> remainingDigits;
      for (int i = 1; i <= n; ++i) {
        remainingDigits.insert(i);
      }
      for (int pos = 1; pos <= n; ++pos) {
        int remaining = n - pos;
        int dig = digits[pos - 1];
        // count numLt
        int numLt = 0;
        for (int otherDig : remainingDigits) {
          if (otherDig < dig) {
            numLt++;
          } else {
            break;
          }
        }
        // then increase k
        remainingDigits.erase(dig);
        k += numLt * amts[remaining];
      }
      cout << k << endl;
    }
  }
}