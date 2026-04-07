#include <bits/stdc++.h>
using namespace std;

int main() {
  int n, q;
  cin >> n >> q;
  vector<vector<int>> lifts(n);
  for (int i = 0; i < n; ++i) {
    int num;
    cin >> num;
    lifts[i].push_back(num);
  }
  // then compute 2**k
  const int TIMES = 20;
  for (int k = 1; k <= TIMES; ++k) {
    for (int i = 0; i < n; ++i) {
      if ((1 << k) + i <= n) {
        lifts[i].push_back(
            min(lifts[i][k - 1], lifts[i + (1 << (k - 1))][k - 1]));
      }
    }
  }
  // and then answer queries
  for (int i = 0; i < q; ++i) {
    // can answer in O(log(amt))
    int a, b;
    cin >> a >> b;
    int amt = b - --a;
    int mi = 1'000'000'000;
    for (int time = TIMES - 1; time >= 0; --time) {
      if (amt & (1 << time)) {
        mi = min(mi, lifts[a][time]);
        a += 1 << time;
      }
    }
    cout << mi << '\n';
  }
}