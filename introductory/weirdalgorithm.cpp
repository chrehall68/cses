#include <bits/stdc++.h>
#include <ios>

using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  long n;
  cin >> n;
  while (n > 1) {
    cout << n << " ";
    if (n % 2 == 0) {
      n /= 2;
    } else {
      n *= 3;
      n += 1;
    }
  }
  cout << 1 << endl;
}