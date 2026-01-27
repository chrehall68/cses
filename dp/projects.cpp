#include <bits/stdc++.h>
#include <queue>
#include <vector>
using namespace std;
using ll = long long;

int main() {
  // standard line scan
  int n;
  cin >> n;
  vector<tuple<int, int, ll>> projects(n);
  for (int i = 0; i < n; ++i) {
    int start, end;
    ll reward;
    cin >> start >> end >> reward;
    projects[i] = {start, end, reward};
  }

  // sort by start time
  sort(projects.begin(), projects.end());
  // min heap of end time, cumulative reward
  priority_queue<pair<int, ll>, vector<pair<int, ll>>, greater<>> pq;
  ll bestCumulative = 0;
  ll result = 0;
  for (auto [start, end, reward] : projects) {
    // update best cumulative
    while (!pq.empty() && start > pq.top().first) {
      bestCumulative = max(bestCumulative, pq.top().second);
      pq.pop();
    }
    // insert into pq
    result = max(result, bestCumulative + reward);
    pq.push({end, bestCumulative + reward});
  }
  cout << result << endl;
}