#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  // if a pair of numbers is coprime, their gcd is 1
  // brute force is for every pair, compute gcd
  // anything divisible by 2 is in the same group -> all pairs w/i that
  // group are bad
  // anything divisible by 3 is in the same group -> all
  // pairs w/i that group are bad
  // anything divisible by x is in the same group, and all pairs w/i that group
  // are bad
  // the problem is, pairs can be in both the 2 group and the 3 group
  // so we want to count the exact number of
  // "how many pairs are both divisible by any of (2..=M)"
  // and we can use PIE for that with mobius inversion / the mobius function

  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  // compute mobius function
  const int M = 1'000'000;
  vector<ll> numFactors(M + 1);
  vector<bool> isPrime(M + 1, true);
  vector<bool> isSquare(M + 1);
  for (int i = 2; i <= M; ++i) {
    if (isPrime[i]) {
      for (int j = i; j <= M; j += i) {
        isPrime[j] = false;
        isSquare[j] = isSquare[j] || (j % (i * i) == 0);
        numFactors[j]++;
      }
    }
  }
  vector<ll> mobius(M + 1);
  for (int i = 2; i <= M; ++i) {
    if (!isSquare[i]) {
      mobius[i] = numFactors[i] % 2 == 1 ? 1 : -1;
    }
  }

  // use mobius function for counting
  ll n;
  cin >> n;
  vector<ll> counts(M + 1);
  for (int i = 0; i < n; ++i) {
    int num;
    cin >> num;
    counts[num]++;
  }
  ll pairsDivisibleByAny = 0;
  for (int factor = 2; factor <= M; ++factor) {
    ll numInGroup = 0;
    for (int j = factor; j <= M; j += factor) {
      numInGroup += counts[j];
    }
    ll pairsInGroup = numInGroup * (numInGroup - 1) / 2;
    pairsDivisibleByAny += pairsInGroup * mobius[factor];
  }
  ll totalPairs = n * (n - 1) / 2;
  ll coprimePairs = totalPairs - pairsDivisibleByAny;
  cout << coprimePairs << endl;
}