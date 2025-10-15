#include <bits/stdc++.h>
using namespace std;

long long modinv(long long val, long long c) {
  if (val <= 1) {
    return val;
  }
  return c - c / val * modinv(c % val, c) % c;
}

int main() {
  map<int, long long> counts;
  long long curMultiplier = 1;
  long long total = 0;
  int n;
  cin >> n;
  long long C = 1'000'000'007;
  for (int i = 0; i < n; ++i) {
    // idea = count how many subsequences end at this position
    // for it to end here, then we can use 0, or 1 of every distinct
    // number we've seen so far
    int num;
    cin >> num;
    long long prevCount = counts[num];
    // so now we get rid of the previous factor
    curMultiplier = curMultiplier * modinv(prevCount + 1, C) % C;
    // and add that to our total
    total += curMultiplier;
    total %= C;
    // and add us to it
    counts[num]++;
    curMultiplier *= counts[num] + 1;
    curMultiplier %= C;
  }
  cout << total << endl;
}