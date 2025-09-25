#include <bits/stdc++.h>
#include <ios>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  int n;
  cin >> n;
  n -= 1;
  vector<vector<bool>> prevGrayCode = {{false}, {true}};
  while (n > 0) {
    vector<vector<bool>> curGrayCode;
    // 0s, then 1s
    int newLength = prevGrayCode.size() * 2;
    for (int i = 0; i < newLength; ++i) {
      curGrayCode.push_back({i >= prevGrayCode.size()});
    }
    // then, add prev gray code to the 0s and mirrored gray code to the 1s
    for (int i = 0; i < prevGrayCode.size(); ++i) {
      for (bool b : prevGrayCode[i]) {
        curGrayCode[i].push_back(b);
        curGrayCode[newLength - 1 - i].push_back(b);
      }
    }
    n--;
    prevGrayCode = curGrayCode;
  }
  // output
  for (vector<bool> &v : prevGrayCode) {
    for (bool b : v) {
      if (b) {
        cout << "1";
      } else {
        cout << "0";
      }
    }
    cout << endl;
  }
}