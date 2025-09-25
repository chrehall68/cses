#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

long long c(int n, int r) {
  int upper = max(r, n - r);
  int lower = min(r, n - r);
  long long numerator = 1;
  while (n > upper) {
    numerator *= n;
    n--;
  }
  long long denom = 1;
  while (lower > 0) {
    denom *= lower;
    lower--;
  }
  return numerator / denom;
}

long long pr(int n, vector<int> &r) {
  int remaining = n;
  long long total = 1;
  for (int ri : r) {
    total *= c(remaining, ri);
    remaining -= ri;
  }
  return total;
}

int main() {
  string s;
  cin >> s;
  sort(s.begin(), s.end());

  vector<int> counts(26, 0);
  for (char c : s) {
    counts[c - 'a'] += 1;
  }
  cout << pr(s.size(), counts) << endl;

  cout << s << endl;

  while (next_permutation(s.begin(), s.end())) {
    cout << s << endl;
  }
}