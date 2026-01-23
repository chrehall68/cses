#include <bits/stdc++.h>
#include <map>
using namespace std;

int main() {
  int n;
  cin >> n;
  // intervals[i] = {start, end, originalIdx}
  vector<tuple<int, int, int>> intervals(n);
  for (int i = 0; i < n; ++i) {
    int start, end;
    cin >> start >> end;
    intervals[i] = {start, end, i};
  }

  // now we just need to monotonic map this
  // we'll sort by start time and maintain things in our monotonic map
  // where things are only in our map if they haven't had anything inside them
  // yet but first, need our output variables
  vector<bool> containsOther(n, false);
  vector<bool> containedByOther(n, false);

  // now do our monotonic map and sorted
  // we want to process the things with the earliest start time
  // to maintain the invariant that the current thing we're processing has start
  // time >= largest start time in our monotonic map in cases of ties we want to
  // process the things with the later end times first
  auto cmp = [](const tuple<int, int, int> &a, const tuple<int, int, int> &b) {
    if (get<0>(a) != get<0>(b)) {
      return get<0>(a) < get<0>(b);
    }
    // case of tie; want to process later end time first
    return get<1>(a) > get<1>(b);
  };
  sort(intervals.begin(), intervals.end(), cmp);
  // maps from end time : original idxs (since more than one thing can end
  // there) minimal monotonic map storing only things that haven't contained
  // anything yet and the last ending thing (if it's still active)
  map<int, vector<int>> currentlyActive;
  for (int i = 0; i < n; ++i) {
    auto [start, end, originalIdx] = intervals[i];
    // maintain invariant that everything in map is currently active
    // by removing all things with end time < start
    while (!currentlyActive.empty() && currentlyActive.begin()->first < start) {
      currentlyActive.erase(currentlyActive.begin());
    }
    // now everything inside is currently active
    // so find the containing interval, if any
    auto containingIt = currentlyActive.lower_bound(end);
    if (containingIt != currentlyActive.end()) {
      // there's stuff containing it
      // so we mark these results and pop from our map
      // lastRemoved = {end time, idx}
      pair<int, int> lastRemoved = {containingIt->first,
                                    containingIt->second[0]};
      containedByOther[originalIdx] = true;
      while (containingIt != currentlyActive.end()) {
        for (int containingIdx : containingIt->second) {
          containsOther[containingIdx] = true;
          lastRemoved = {containingIt->first, containingIdx};
        }
        auto toRemove = containingIt;
        containingIt++;
        currentlyActive.erase(toRemove);
      }
      // reinsert the last one since it might contain more
      currentlyActive[lastRemoved.first].push_back(lastRemoved.second);
    }
    // and of course put this too
    currentlyActive[end].push_back(originalIdx);
  }

  // output
  for (int i = 0; i < n; ++i) {
    cout << (containsOther[i] ? 1 : 0) << " ";
  }
  cout << endl;
  for (int i = 0; i < n; ++i) {
    cout << (containedByOther[i] ? 1 : 0) << " ";
  }
  cout << endl;
}