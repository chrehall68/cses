#include <bits/stdc++.h>
using namespace std;
int main() {
  int n, x;
  cin >> n >> x;
  map<int, int> indices;
  for (int i = 0; i < n; ++i) {
    int num;
    cin >> num;
    if (indices.count(x - num)) {
      cout << 1 + indices[x - num] << " " << 1 + i << endl;
      return 0;
    }
    indices[num] = i;
  }
  cout << "IMPOSSIBLE" << endl;
}