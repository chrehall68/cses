#include <bits/stdc++.h>
using namespace std;

int main() {
  long long n;
  cin >> n;
  // if there's a 2 and a 5, then extra zero
  // 2 12 22 32 42 52 62 72 82 92 102
  // we need to factorize each number to figure out how many times
  // 5's appear in the factors
  // and how many times 2's appear
  // luckily, we know that if a 5 appears, there is always
  // a matching 2
  // so just count 5's
  // then instead of factoring, use division
  long long fiveCount = 0;
  n /= 5;
  while (n > 0) {
    fiveCount += n;
    n /= 5;
  }
  cout << fiveCount << endl;
}