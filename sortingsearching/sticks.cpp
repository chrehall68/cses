#include <bits/stdc++.h>
#include <limits>
using namespace std;

int main() {
  long n;
  cin >> n;
  vector<int> sticks(n);
  for (int i = 0; i < n; ++i) {
    cin >> sticks[i];
  }
  sort(sticks.begin(), sticks.end());
  long long sumAfter = 0;
  long long sumBefore = 0;
  for (int i = n - 1; i >= 0; --i) {
    sumAfter += sticks[i];
  }
  // so now it costs some amount to move everything lt and some to move
  // everything gt
  long long bestCost = numeric_limits<long long>::max();
  for (long i = 0; i < n; ++i) {
    sumAfter -= sticks[i];
    long long curCost =
        i * sticks[i] - sumBefore + sumAfter - (n - i - 1) * sticks[i];
    sumBefore += sticks[i];
    bestCost = min(bestCost, curCost);
  }
  cout << bestCost << endl;
}