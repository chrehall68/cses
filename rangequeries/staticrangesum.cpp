#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main() {
  int n, q;
  cin >> n >> q;
  vector<ll> psums(n + 1);
  for (int i = 0; i < n; ++i) {
    cin >> psums[i + 1];
    psums[i + 1] += psums[i];
  }
  for (int i = 0; i < q; ++i) {
    int a, b;
    cin >> a >> b;
    cout << psums[b] - psums[a - 1] << '\n';
  }
}