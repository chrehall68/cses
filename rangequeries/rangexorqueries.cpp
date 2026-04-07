#include <bits/stdc++.h>
using namespace std;

int main() {
  int n, q;
  cin >> n >> q;
  vector<int> psum(n + 1);
  for (int i = 0; i < n; ++i) {
    cin >> psum[i + 1];
    psum[i + 1] ^= psum[i];
  }
  for (int i = 0; i < q; ++i) {
    int a, b;
    cin >> a >> b;
    cout << (psum[b] ^ psum[--a]) << '\n';
  }
}