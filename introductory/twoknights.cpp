#include <bits/stdc++.h>
using namespace std;

int main() {
  int n;
  cin >> n;
  for (long long i = 1; i <= n; ++i) {
    long long squares = i * i;
    // 8 things attack
    long long attacking = 8 * squares;
    // for the top two rows
    // we disqualify their two up's
    // and then for the leftmost col, everything after the 2nd row, disqualify
    // its upleft and for the rightmost col, everything after the 2nd row,
    // disqualify its upright
    long long disqualified = min(2LL, i) * i * 2 + max(0LL, i - 2) * 2;
    disqualified *= 4; // use symmetry for other 4 orientations
    long long actualBad = attacking - disqualified;
    cout << squares * (squares - 1) / 2 - actualBad / 2 << endl;
  }
}