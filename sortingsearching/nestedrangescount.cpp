#include <bits/stdc++.h>
#include <cassert>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <vector>
using namespace __gnu_pbds;
using namespace std;
typedef tree<int, null_type, std::less_equal<>, rb_tree_tag,
             tree_order_statistics_node_update>
    ordered_set;

int main() {
  // so we need to be able to something similar to the nested ranges check
  // for counting how many things contain this, we just need to count how many
  // currently active things have an end time >= its end time
  // for counting how many things this contains, we can look at when it expires
  // and count how many of the already expired things have a start time
  // >= its start time
  int n;
  cin >> n;
  // intervals[i] = (start, end)
  vector<pair<int, int>> intervals(n);
  vector<int> indices(n);
  for (int i = 0; i < n; ++i) {
    int start, end;
    cin >> start >> end;
    intervals[i] = {start, end};
    indices[i] = i;
  }
  // sentinel that starts after everything else
  // just to get our while loop to finish propagating stuff
  intervals.push_back({(int)1e9 + 1, (int)1e9 + 2});
  indices.push_back(n);

  // sort by start time, breaking ties by latest end time
  auto cmp = [&intervals](const int a, const int b) {
    auto [startA, endA] = intervals[a];
    auto [startB, endB] = intervals[b];
    if (startA != startB) {
      return startA < startB;
    }
    return endA > endB;
  };
  sort(indices.begin(), indices.end(), cmp);
  // output vars
  vector<int> numContaining(n, 0);
  vector<int> numContainedBy(n, 0);
  // curActive maps endTime : originalIdx's of intervals w/ that end time
  // ordered by start time in decreasing order
  map<int, vector<int>> curActive;
  ordered_set curActiveEnds;
  ordered_set expiredStarts;
  for (int originalIdx : indices) {
    auto [start, end] = intervals[originalIdx];
    // maintain the invariant that everything inside is currently active
    // by removing things with end time < start
    while (!curActive.empty() && curActive.begin()->first < start) {
      // also, now that we know their end time < start, we know that we should
      // have the final values for numContaining
      int expiredTime = curActive.begin()->first;
      vector<int> &expiredIndices = curActive.begin()->second;
      for (int j = expiredIndices.size() - 1; j >= 0; --j) {
        // we know how many are here
        int expiredOriginalIdx = expiredIndices[j];
        assert(*curActiveEnds.begin() == expiredTime);
        int expiredStart = intervals[expiredOriginalIdx].first;
        numContaining[expiredOriginalIdx] =
            expiredStarts.size() - expiredStarts.order_of_key(expiredStart);
        curActiveEnds.erase(curActiveEnds.begin());
        expiredStarts.insert(expiredStart);
      }
      curActive.erase(curActive.begin());
    }
    // now that it's been trimmed, find how many contain it
    numContainedBy[originalIdx] =
        curActiveEnds.size() - curActiveEnds.order_of_key(end);
    // and insert us
    curActive[end].push_back(originalIdx);
    curActiveEnds.insert(end);
  }

  // output
  for (int i = 0; i < n; ++i) {
    cout << numContaining[i] << " ";
  }
  cout << endl;
  for (int i = 0; i < n; ++i) {
    cout << numContainedBy[i] << " ";
  }
  cout << endl;
}