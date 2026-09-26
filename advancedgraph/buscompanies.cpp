#include <bits/stdc++.h>
#include <queue>
using namespace std;
using ll = long long;
constexpr const ll M = 1'000'000'000'000'000'000LL;

int main() {
  // so maybe a modified dijkstra's?
  // we can't actually create the full graph because
  // that would be extremely dense
  // but maybe we can say that some bus companies are the cheapest
  // and we also know sum(k) <= 2*10**5
  // so intuitively, we'd want to explore the smallest first
  int n, numBuses;
  cin >> n >> numBuses;
  vector<ll> busCosts(numBuses);
  for (ll &cost : busCosts) {
    cin >> cost;
  }
  vector<vector<int>> busesInCity(n);
  vector<vector<int>> citiesForBus(numBuses);
  for (int bus = 0; bus < numBuses; ++bus) {
    int k;
    for (cin >> k; k > 0; --k) {
      int city;
      cin >> city;
      --city;
      citiesForBus[bus].push_back(city);
      busesInCity[city].push_back(bus);
    }
  }
  // now dijkstra's
  vector<bool> usedBusRoute(numBuses);
  vector<ll> minCosts(n, M);
  priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<>> pq;
  minCosts[0] = 0;
  pq.push({0, 0});
  while (!pq.empty()) {
    auto [cost, city] = pq.top();
    pq.pop();
    if (minCosts[city] < cost) {
      continue; // this is stale
    }
    // this is not stale, so relax any buses
    for (int bus : busesInCity[city]) {
      if (!usedBusRoute[bus]) {
        // this is the first time we're hitting this bus
        // therefore since all bus costs are nonnegative, this is optimal time
        // to take this bus
        usedBusRoute[bus] = true;
        ll nextCost = cost + busCosts[bus];
        for (int connCity : citiesForBus[bus]) {
          if (nextCost < minCosts[connCity]) {
            minCosts[connCity] = nextCost;
            pq.push({nextCost, connCity});
          }
        }
      }
    }
  }
  // output
  for (int city = 0; city < n; ++city) {
    cout << minCosts[city] << ' ';
  }
  cout << endl;
}
