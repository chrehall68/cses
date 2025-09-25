#include <bits/stdc++.h>
using namespace std;

int main() {
  int t;
  cin >> t;
  for (int i = 0; i < t; ++i) {
    int n, a, b;
    cin >> n >> a >> b;
    int ties = n - a - b;
    if (((a == 0) ^ (b == 0)) || ties < 0) {
      // impossible
      cout << "NO" << endl;
    } else {
      // process all ties first
      cout << "YES" << endl;
      int low = 0;
      vector<int> aCards;
      vector<int> bCards;
      for (; low < ties; ++low) {
        aCards.push_back(low);
        bCards.push_back(low);
      }
      // do a's wins
      for (int aWin = 0; aWin < a; ++aWin) {
        aCards.push_back(low + b + aWin);
        bCards.push_back(low + aWin);
      }
      // do b's wins
      for (int bWin = 0; bWin < b; ++bWin) {
        aCards.push_back(low + bWin);
        bCards.push_back(low + a + bWin);
      }
      // then output stuff
      for (int card : aCards) {
        cout << card + 1 << " ";
      }
      cout << endl;
      for (int card : bCards) {
        cout << card + 1 << " ";
      }
      cout << endl;
    }
  }
}