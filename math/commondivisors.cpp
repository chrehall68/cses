#include <bits/stdc++.h>
using namespace std;
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  const int M = 1'000'000;
  vector<int> counts(M);
  int n;
  for (cin >> n; n > 0; --n) {
    int x;
    cin >> x;
    counts[x]++;
  }
  int best = 1;
  for (int gcd = 1; gcd <= M; ++gcd) {
    int sum = 0;
    for (int j = gcd; j <= M; j += gcd) {
      sum += counts[j];
    }
    if (sum > 1) {
      best = gcd;
    }
  }
  cout << best << endl;
}