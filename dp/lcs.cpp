#include <bits/stdc++.h>
using namespace std;

int main() {
  int n, m;
  cin >> n >> m;
  vector<int> a(n);
  vector<int> b(m);
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }
  for (int i = 0; i < m; ++i) {
    cin >> b[i];
  }
  // just like edit distance
  // take both if match, otherwise skip left or skip right

  vector<vector<int>> dp(a.size() + 1, vector<int>(b.size() + 1, 0));
  for (int i = a.size() - 1; i >= 0; --i) {
    for (int j = b.size() - 1; j >= 0; --j) {
      int best = dp[i + 1][j];
      best = max(best, dp[i][j + 1]); // go to j+1
      int inc = a[i] == b[j];
      best = max(best, dp[i + 1][j + 1] + inc); // i+1, j+1
      dp[i][j] = best;
    }
  }

  cout << dp[0][0] << endl;
  // and reconstruct
  int i = 0, j = 0;
  while (i != a.size() && j != b.size()) {
    if (a[i] == b[j]) {
      cout << a[i] << " ";
      i++;
      j++;
    }
    // otherwise, go left or right depending on which is better
    else if (dp[i + 1][j] > dp[i][j + 1]) {
      i++;
    } else {
      j++;
    }
  }
  cout << endl;
}