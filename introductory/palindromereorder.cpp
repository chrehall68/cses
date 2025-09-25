#include <bits/stdc++.h>
#include <pthread.h>
using namespace std;

int main() {
  vector<int> charCounts(26);
  string s;
  cin >> s;
  for (char c : s) {
    charCounts[c - 'A'] += 1;
  }

  // now there should be either
  // - one number w/ odd count
  // - 0 numbers w/ odd count
  vector<int> theOdds;
  for (int i = 0; i < 26; ++i) {
    if (charCounts[i] % 2 == 1) {
      theOdds.push_back(i);
    }
  }
  if (theOdds.size() >= 2) {
    cout << "NO SOLUTION" << endl;
  } else {
    // create palindrome by placing everything non odd
    string result;
    for (int i = 0; i < 26; ++i) {
      if (charCounts[i] % 2 == 0) {
        for (int j = 0; j < charCounts[i] / 2; ++j) {
          result += 'A' + i;
        }
      }
    }
    // then add the odd
    for (int odd : theOdds) {
      for (int cnt = 0; cnt < charCounts[odd]; ++cnt) {
        result += 'A' + odd;
      }
    }
    // then add the rest
    for (int i = 25; i >= 0; --i) {
      if (charCounts[i] % 2 == 0) {
        for (int j = 0; j < charCounts[i] / 2; ++j) {
          result += 'A' + i;
        }
      }
    }
    cout << result << endl;
  }
}