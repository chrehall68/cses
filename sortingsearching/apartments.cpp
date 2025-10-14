#include <bits/stdc++.h>
using namespace std;

int main() {
  int n, m, k;
  cin >> n >> m >> k;
  vector<int> desired(n);
  vector<int> apartments(m);
  for (int i = 0; i < n; ++i) {
    cin >> desired[i];
  }
  for (int i = 0; i < m; ++i) {
    cin >> apartments[i];
  }

  sort(apartments.begin(), apartments.end());
  sort(desired.begin(), desired.end());
  int apartmentsIdx = 0;
  int usedApartments = 0;
  for (int person : desired) {
    // move forward
    while (apartmentsIdx < apartments.size() &&
           apartments[apartmentsIdx] + k < person) {
      apartmentsIdx++;
    }
    // check
    if (apartmentsIdx < apartments.size() &&
        apartments[apartmentsIdx] - k <= person &&
        apartments[apartmentsIdx] + k >= person) {
      // good
      apartmentsIdx++;
      ++usedApartments;
    }
  }
  cout << usedApartments << endl;
}