#include <bits/stdc++.h>
using namespace std;
using ll = __int128;

ll numProduceable(ll time, vector<long long> &productionTimes) {
  ll total = 0;
  for (ll prodTime : productionTimes) {
    ll amt = time / prodTime;
    total += amt;
  }
  return total;
}
int main() {
  long long n, t;
  cin >> n >> t;
  vector<long long> productionTimes(n);
  for (int i = 0; i < n; ++i) {

    cin >> productionTimes[i];
  }

  // now just bsearch
  ll low = 1;
  ll high = (ll)1e18;
  ll best = 0;
  while (low <= high) {
    ll mid = low + (high - low) / 2;
    if (numProduceable(mid, productionTimes) >= (ll)t) {
      // works, try lower time
      high = mid - 1;
      best = mid;
    } else {
      // doesn't work, try higher time
      low = mid + 1;
    }
  }
  cout << (long long)best << endl;
}