#include <bits/stdc++.h>
#include <string>
using namespace std;
using ll = long long;

ll numLt(ll limit) {
  string s = to_string(limit);
  if (limit < 10) {
    return limit + 1;
  }
  // ways[digitIdx][digit][tight]
  vector<vector<array<ll, 2>>> ways(s.size(), vector<array<ll, 2>>(10, {0, 0}));
  // initialize
  for (int digit = 0; digit < 10; ++digit) {
    ways[s.size() - 1][digit][false] = 1; // not tight
    // for tight, we can only go up to the limit
    int limit = s[s.size() - 1] - '0';
    ways[s.size() - 1][digit][true] = digit <= limit;
  }
  // maintenance
  for (int digitIdx = s.size() - 2; digitIdx >= 0; --digitIdx) {
    for (int tight = 0; tight < 2; ++tight) {
      int limit = tight ? s[digitIdx] - '0' : 9;
      for (int digit = 0; digit <= limit; ++digit) {
        bool nextTight = tight && digit == limit;
        for (int otherDigit = 0; otherDigit < 10; ++otherDigit) {
          if (otherDigit != digit) {
            ways[digitIdx][digit][tight] +=
                ways[digitIdx + 1][otherDigit][nextTight];
          }
        }
      }
    }
  }
  // then now we can start it at any position
  ll result = 1;
  for (int startPosition = 0; startPosition < s.size(); ++startPosition) {
    for (int digit = 1; digit < 10; ++digit) {
      result += ways[startPosition][digit][startPosition == 0];
    }
  }
  return result;
}

int main() {
  ll a, b;
  cin >> a >> b;
  ll first = numLt(a - 1);
  ll second = numLt(b);
  cout << second - first << endl;
}