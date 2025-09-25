#include <bits/stdc++.h>
using namespace std;

long long modPow(long long x, long long y, long long c) {
  long long total = 1;
  long long curPow = x;
  while (y > 0) {
    if ((y & 1) == 1) {
      total *= curPow;
      total %= c;
    }
    curPow *= curPow;
    curPow %= c;
    y >>= 1;
  }
  return total;
}

int main() {
  int n;
  cin >> n;
  cout << modPow(2, n, 1000000007) << endl;
}