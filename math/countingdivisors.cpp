#include <bits/stdc++.h>
using namespace std;
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  const int M = 1'000'000;
  vector<int> counts(M + 1);
  for (int i = 1; i <= M; ++i) {
    for (int j = i; j <= M; j += i) {
      counts[j]++;
    }
  }
  int n;
  for (cin >> n; n > 0; --n) {
    int x;
    cin >> x;
    cout << counts[x] << endl;
  }
}