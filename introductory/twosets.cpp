#include <bits/stdc++.h>

using namespace std;

int main() {
  long long n;
  cin >> n;
  long long total = (n + 1) * n / 2;
  if (total % 2 == 1) {
    cout << "NO" << endl;
  } else {
    cout << "YES" << endl;
    vector<bool> used(n + 1);
    long long remaining = total / 2;
    long long nextUnused = n;
    int firstCount = 0;
    while (remaining > 0) {
      long long toSubtract = min(nextUnused, remaining);
      if (toSubtract == nextUnused) {
        used[nextUnused--] = true;
      } else {
        used[remaining] = true;
      }
      remaining -= toSubtract;
      firstCount++;
    }
    cout << firstCount << endl;
    for (int i = 1; i <= n; ++i) {
      if (used[i]) {
        cout << i << " ";
      }
    }
    cout << endl;

    // print second one too
    cout << n - firstCount << endl;
    for (int i = 1; i <= n; ++i) {
      if (!used[i]) {
        cout << i << " ";
      }
    }
    cout << endl;
  }
}