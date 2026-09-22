#include <bits/stdc++.h>
using namespace std;
using ld = long double;

int main() {
  // n children, candies 1..=k
  // find expected max
  // we can say
  // E[X] = 1*P(1 is max) + 2*P(2 is max)
  // + ... + k*P(k is max)
  // so to get P(i is max), we can easily compute
  // P(max <= i)
  // and then use differences to get P(max == i)
  int n, k;
  cin >> n >> k;
  cout << fixed << setprecision(6);
  ld prevPMaxLe = 0;
  ld ex = 0;
  for (int maxNum = 1; maxNum <= k; ++maxNum) {
    ld pMaxLe = pow(maxNum / (ld)k, n);
    ld pMaxEq = pMaxLe - prevPMaxLe;
    ex += pMaxEq * maxNum;
    prevPMaxLe = pMaxLe;
  }
  // handles cases where we were ever so slightly off from
  // 1/2 of 1e-6
  cout << ex + 1e-18 << endl;
}