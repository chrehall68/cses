#include <bits/stdc++.h>
#include <limits>
using namespace std;

int main() {
  int n;
  cin >> n;
  long bestSum = numeric_limits<int>::min();
  long curSum = 0;
  for (int i = 0; i < n; ++i) {
    int num;
    cin >> num;
    curSum += num;
    bestSum = max(bestSum, curSum);
    if (curSum < 0) {
      curSum = 0;
    }
  }
  cout << bestSum << endl;
}