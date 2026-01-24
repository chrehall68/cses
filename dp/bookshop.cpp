#include <bits/stdc++.h>
using namespace std;

int main() {
  int n, x;
  cin >> n >> x;
  vector<int> prices(n);
  vector<int> pages(n);
  for (int i = 0; i < n; ++i) {
    cin >> prices[i];
  }
  for (int i = 0; i < n; ++i) {
    cin >> pages[i];
  }
  vector<int> maxPages(x + 1, 0);
  for (int i = 0; i < n; ++i) {
    for (int j = x; j >= prices[i]; --j) {
      maxPages[j] = max(maxPages[j], maxPages[j - prices[i]] + pages[i]);
    }
    int bestSoFar = 0;
    for (int j = 0; j <= x; ++j) {
      bestSoFar = max(bestSoFar, maxPages[j]);
      maxPages[j] = bestSoFar;
    }
  }

  cout << maxPages[x] << endl;
}