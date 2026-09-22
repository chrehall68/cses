#include <bits/stdc++.h>
using namespace std;

int main() {
  int n, m;
  cin >> n >> m;
  vector<int> outDegree(n);
  vector<vector<int>> predecessors(n);
  for (int i = 0; i < m; ++i) {
    int before, after;
    cin >> before >> after;
    predecessors[--after].push_back(--before);
    outDegree[before]++;
  }
  // now sort of kahn's topsort but like backwards
  vector<int> order; // stores in reverse
  // construct initial
  set<int> available;
  for (int i = 0; i < n; ++i) {
    if (outDegree[i] == 0) {
      available.insert(i);
    }
  }
  // now iterate through, always placing the max
  while (!available.empty()) {
    int toTake = *prev(available.end());
    available.erase(toTake);
    order.push_back(toTake);
    // then relax edges
    for (int predecessor : predecessors[toTake]) {
      outDegree[predecessor]--;
      if (outDegree[predecessor] == 0) {
        available.insert(predecessor);
      }
    }
  }
  reverse(order.begin(), order.end());
  for (int node : order) {
    cout << node + 1 << ' ';
  }
  cout << endl;
}