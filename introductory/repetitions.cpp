#include <bits/stdc++.h>
using namespace std;

int main() {
  string s;
  cin >> s;
  int longest = 1;
  int curCount = 1;
  for (int i = 1; i < s.size(); ++i) {
    if (s[i] == s[i - 1]) {
      curCount++;
    } else {
      curCount = 1;
    }
    longest = max(longest, curCount);
  }
  cout << longest << endl;
}