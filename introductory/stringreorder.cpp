#include <algorithm>
#include <bits/stdc++.h>
#include <functional>
#include <queue>
using namespace std;

int main() {
  string s;
  cin >> s;
  vector<int> counts(26, 0);
  int maxCount = 0;
  for (char c : s) {
    counts[c - 'A'] += 1;
    maxCount = max(maxCount, counts[c - 'A']);
  }

  int others = s.size() - maxCount;
  if (maxCount > others + 1) {
    cout << -1 << endl;
    return 0;
  }
  // good
  // so just scatter
  string result;
  for (int remaining = s.size(); remaining > 0; --remaining) {
    // find max and second max amounts
    int m = max_element(counts.begin(), counts.end()) - counts.begin();

    // now figure out best thing to put here
    for (int j = 0; j < 26; ++j) {
      if ((result.empty() || result.back() != 'A' + j) && counts[j] > 0 &&
          (j == m || !(counts[m] > remaining - counts[m]))) {
        // good
        result += 'A' + j;
        counts[j] -= 1;
        break;
      }
    }
  }
  cout << result;
}