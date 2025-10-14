#include <bits/stdc++.h>
#include <queue>
using namespace std;

int main() {
  int x, n;
  cin >> x >> n;

  // (cost, location)
  priority_queue<pair<int, pair<int, int>>> pq;
  set<pair<int, int>> intervals; // (start, end) inclusive
  intervals.insert({0, x});
  pq.push({x + 1, {0, x}});
  for (int i = 0; i < n; ++i) {
    int p;
    cin >> p;
    // now divide whatever is closest to p
    pair<int, int> tmpInt = {p,
                             x + 1}; // always greater than the actual interval
    auto it = intervals.lower_bound(tmpInt);
    it--;
    pair<int, int> splitInterval = *it;
    // now we just need to split
    intervals.erase(it);
    // split somewhere in the middle
    pair<int, int> lhs = {splitInterval.first, p};
    pair<int, int> rhs = {p, splitInterval.second};
    intervals.insert(lhs);
    intervals.insert(rhs);
    pq.push({lhs.second - lhs.first, lhs});
    pq.push({rhs.second - rhs.first, rhs});
    // now output
    while (intervals.find(pq.top().second) == intervals.end()) {
      pq.pop();
    }
    cout << pq.top().first << " ";
  }
  cout << endl;
}