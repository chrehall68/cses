#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  // standard LCA with binary lifts problem
  int n, q;
  cin >> n >> q;
  vector<vector<int>> outgoing(n + 1);
  vector<vector<int>> lifts(n + 1); // 1-indexed
  for (int i = 2; i <= n; ++i) {
    int par;
    cin >> par;
    lifts[i].push_back(par);
    outgoing[par].push_back(i);
  }
  vector<int> depths(n + 1);
  queue<int> qu;
  qu.push(1);
  while (qu.size() > 0) {
    int employee = qu.front();
    qu.pop();
    for (int subordinate : outgoing[employee]) {
      qu.push(subordinate);
      depths[subordinate] = depths[employee] + 1;
    }
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
    int a, b;
    cin >> a >> b;
    int lower = a, higher = b;
    if (depths[b] > depths[a]) {
      lower = b;
      higher = a;
    }
    // raise lower
    for (int kp = k; kp >= 0; --kp) {
      if (depths[lower] - (1 << kp) >= depths[higher]) {
        lower = lifts[lower][kp];
      }
    }
    if (lower == higher) {
      cout << lower << endl;
    } else {
      for (int kp = k; kp >= 0; --kp) {
        if (kp < lifts[lower].size() && lifts[lower][kp] != lifts[higher][kp]) {
          lower = lifts[lower][kp];
          higher = lifts[higher][kp];
        }
      }
      assert(lower != higher);
      assert(lifts[lower][0] == lifts[higher][0]);
      cout << lifts[lower][0] << endl;
    }
  }
}