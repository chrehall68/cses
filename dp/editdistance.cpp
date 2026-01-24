#include <bits/stdc++.h>
#include <limits>
#include <vector>
using namespace std;

int main() {
  string a, b;
  cin >> a >> b;

  // add one character, remove, or replace
  // so if we're at indices i,j
  // we can go to index i+1,j (remove i or add a character on j side), i,j+1
  // (remove j or add character on i side) i+1,j+1 (replace i or j) let's use b
  // as j and a as i
  vector<int> prevLevel(b.size() + 1);
  for (int j = 0; j <= b.size(); ++j) {
    int remainingChars = b.size() - j;
    // have to just remove them (or add on other side)
    prevLevel[j] = remainingChars;
  }
  vector<int> curLevel(b.size() + 1);
  for (int i = a.size() - 1; i >= 0; --i) {
    for (int j = b.size(); j >= 0; --j) {
      int best = prevLevel[j] + 1; // go to index i+1
      if (j + 1 <= b.size()) {
        best = min(best, curLevel[j + 1] + 1); // go to j+1
        int inc = a[i] != b[j];
        best = min(best, prevLevel[j + 1] + inc); // i+1, j+1
      }
      curLevel[j] = best;
    }
    swap(prevLevel, curLevel);
  }

  cout << prevLevel[0] << endl;
}