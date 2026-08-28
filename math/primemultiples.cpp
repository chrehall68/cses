#include <bits/stdc++.h>
using namespace std;
using ll = __int128_t;

int main() {
  // since we only have up to 20 primes, seems like a PIE problem
  long long inputN, inputK;
  cin >> inputN >> inputK;
  vector<long long> inputs(inputK);
  for (auto &num : inputs) {
    cin >> num;
  }
  ll numDivisible = 0;
  for (int i = 1; i < 1 << inputs.size(); ++i) {
    ll prod = 1;
    ll cnt = 0;
    bool good = true;
    for (size_t idx = 0; idx < inputs.size() && good; ++idx) {
      if ((i >> idx) & 1) {
        prod *= inputs[idx];
        good = prod <= inputN;
        cnt++;
      }
    }
    if (!good) {
      continue; // too large to appear
    }
    // appears some amount of times
    ll times = inputN / prod;
    ll sign = cnt % 2 == 1 ? 1 : -1;
    numDivisible += sign * times;
  }
  cout << (long long)numDivisible << endl;
}