#include <bits/stdc++.h>
#include <string>

using namespace std;

long long numOnLeft(long long n) {
  long long pow10 = 10;
  long long total = 0;
  int length = 1;
  while (pow10 < n) {
    total += (pow10 / 10 * 9) * length;
    pow10 *= 10;
    length++;
  }
  // now we are greater
  // so reduce pow and then subtract to see how many extra we have
  pow10 /= 10;
  total += (n - pow10) * length;
  return total;
}

int main() {
  int q;
  cin >> q;

  for (int i = 0; i < q; ++i) {
    long long k;
    cin >> k;

    // find first number such that the length of that number +
    // the length of everything before is > than k

    long long pow10 = 10;
    int length = 1;
    while (k - (pow10 / 10 * 9) * length > 0) {
      k -= (pow10 / 10 * 9) * length;
      pow10 *= 10;
      length++;
    }
    // now we are greater
    // so reduce pow and then subtract to see how many extra we have
    pow10 /= 10;
    long long number = (k - 1) / length + pow10;
    string s = to_string(number);
    // cout << number << " which is actually " << s[(k - 1) % length] << endl;
    cout << s[(k - 1) % length] << endl;
  }
}