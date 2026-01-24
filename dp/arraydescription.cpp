#include <bits/stdc++.h>
#include <numeric>
using namespace std;
using ll = long long;
const ll C = 1e9 + 7;

int main() {
  int n, m;
  cin >> n >> m;
  // waysEndingAt[i-1] = how many arrays end w/ i as the last number
  vector<ll> waysEndingAt(m, 0);
  vector<ll> workingSpace(m, 0);
  int start;
  cin >> start;
  if (start == 0) {
    fill(waysEndingAt.begin(), waysEndingAt.end(), 1);
  } else {
    waysEndingAt[start - 1] = 1;
  }
  for (int i = 1; i < n; ++i) {
    fill(workingSpace.begin(), workingSpace.end(), 0);
    int num;
    cin >> num;
    if (num == 0) {
      for (int dest = 0; dest < m; ++dest) {
        workingSpace[dest] = waysEndingAt[dest];
        if (dest > 0) {
          workingSpace[dest] += waysEndingAt[dest - 1];
        }
        if (dest + 1 < m) {
          workingSpace[dest] += waysEndingAt[dest + 1];
        }
        workingSpace[dest] %= C;
      }
    } else {
      num -= 1;
      workingSpace[num] = waysEndingAt[num];
      if (num > 0) {
        workingSpace[num] += waysEndingAt[num - 1];
      }
      if (num + 1 < m) {
        workingSpace[num] += waysEndingAt[num + 1];
      }
      workingSpace[num] %= C;
    }
    swap(workingSpace, waysEndingAt);
  }
  cout << accumulate(waysEndingAt.begin(), waysEndingAt.end(), 0LL) % C << endl;
}