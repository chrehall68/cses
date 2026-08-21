#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  // standard binary lifts problem
  int n, q;
  cin >> n >> q;
  vector<vector<int>> lifts(n + 1); // 1-indexed
  for (int i = 2; i <= n; ++i) {
    int par;
    cin >> par;
    lifts[i].push_back(par);
  }

  // build lifts
  int k;
  for (k = 0; (1 << k) <= n; ++k) {
    for (int i = 1; i <= n; ++i) {
      if (k < lifts[i].size()) {
        int par = lifts[i][k];
        if (k < lifts[par].size()) {
          lifts[i].push_back(lifts[par][k]);
        }
      }
    }
  }

  // handle queries
  for (; q > 0; --q) {
    int employee, desired;
    cin >> employee >> desired;
    int cur = employee;
    for (int kp = k; kp >= 0; --kp) {
      if (1 << kp <= desired) {
        // need to make this hop
        if (kp < lifts[cur].size()) {
          cur = lifts[cur][kp];
          desired -= 1 << kp;
        } else {
          break;
        }
      }
    }
    if (desired == 0) {
      cout << cur << endl;
    } else {
      cout << -1 << endl;
    }
  }
}