#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll C = 1e9 + 7;
int main() {
  int t;
  cin >> t;
  map<int, vector<int>> queryIdxs;
  for (int i = 0; i < t; ++i) {
    int query;
    cin >> query;
    queryIdxs[query].push_back(i);
  }
  vector<ll> results(t);
  int last = (--queryIdxs.end())->first;
  // inspired by https://codeforces.com/blog/entry/98085
  // type a towers store the ones that end in a width-2 block
  // type b towers store the ones that end in 2 width-1 blocks
  ll a = 1;
  ll b = 1;
  for (int i = 1; i <= last; ++i) {
    for (int queryIdx : queryIdxs[i]) {
      results[queryIdx] = (a + b) % C;
    }
    // then advance
    // could extend the width 2 blocks, or add a 1x2 block on top of the b's or
    // the a's
    ll newA = a * 2 + b;
    // could extend one, extend the other, extend both, extend none (add 2 1x1
    // blocks)
    ll newB = a + 4 * b;
    a = newA % C;
    b = newB % C;
  }
  for (int i = 0; i < t; ++i) {
    cout << results[i] << endl;
  }
}