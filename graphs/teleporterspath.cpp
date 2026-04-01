#include <bits/stdc++.h>
using namespace std;

int main() {
  int n, m;
  cin >> n >> m;
  // directed graph eulerian tour
  vector<set<int>> adj(n);
  vector<int> degree(n); // outdegree - indegree
  for (int i = 0; i < m; ++i) {
    int a, b;
    cin >> a >> b;
    adj[--a].insert(--b);
    degree[a]++;
    degree[b]--;
  }
  // 0 should have 1 more outgoing, n-1 should have 1 more incoming
  bool good = degree[0] == 1 && degree[n - 1] == -1;
  for (int i = 1; i < n - 1; ++i) {
    // everything else should be eulerian
    good = good && degree[i] == 0;
  }
  // then do the tour
  list<int> order;
  stack<pair<int, list<int>::iterator>> s;
  order.push_back(0);
  s.push({0, order.begin()});
  int used = 0;
  while (!s.empty()) {
    auto [node, myIt] = s.top();
    if (adj[node].empty()) {
      s.pop();
    } else {
      used++;
      int conn = *adj[node].begin();
      adj[node].erase(conn);
      auto nextIt = myIt;
      nextIt++;
      nextIt = order.insert(nextIt, conn);
      s.push({conn, nextIt});
    }
  }
  if (!good || used != m) {
    cout << "IMPOSSIBLE" << endl;
  } else {
    for (int node : order) {
      cout << node + 1 << ' ';
    }
    cout << endl;
  }
}