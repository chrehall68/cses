#include <bits/stdc++.h>
using namespace std;
using ld = long double;

int main() {
  // n is small enough that we just simulate
  size_t n, a, b;
  cin >> n >> a >> b;
  vector<ld> prev(6 * n + 1), cur(6 * n + 1);
  prev[0] = 1;
  ld mult = 1 / (ld)6;
  for (size_t i = 1; i <= n; ++i) {
    for (size_t pVal = 0; pVal < cur.size(); ++pVal) {
      for (size_t roll = 1; roll <= 6 && roll + pVal < cur.size(); ++roll) {
        cur[pVal + roll] += mult * prev[pVal];
      }
    }
    swap(prev, cur);
    fill(cur.begin(), cur.end(), 0);
  }
  ld value = accumulate(prev.begin() + a, prev.begin() + b + 1, (ld)0);
  cout << fixed << setprecision(6) << value << endl;
}