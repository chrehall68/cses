#include <bits/stdc++.h>
using namespace std;
int main() {
  int n;
  cin >> n;
  vector<vector<int>> mexGrid;
  for (int row = 0; row < n; ++row) {
    vector<int> curRow;
    for (int col = 0; col < n; ++col) {
      vector<int> above;
      for (int aboveRow = row - 1; aboveRow > -1; aboveRow--) {
        above.push_back(mexGrid[aboveRow][col]);
      }
      // and include things in the cur row too
      for (int cp = col - 1; cp > -1; --cp) {
        above.push_back(curRow[cp]);
      }
      sort(above.begin(), above.end());
      // find first excluded
      int mex = 0;
      while (mex < above.size() && above[mex] == mex) {
        mex++;
      }
      // now mex is the actual mex, so store it
      curRow.push_back(mex);
    }
    mexGrid.push_back(curRow);
  }

  // output
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      cout << mexGrid[i][j] << ' ';
    }
    cout << endl;
  }
}