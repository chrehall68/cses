#include <bits/stdc++.h>
using namespace std;
using ll = long long;
struct HeightStruct {
  // handlers should know to use extraAdder first
  int extraAdder;
  // distinctHeights[height] = count at that height
  map<int, ll> distinctHeights;
  ll totalAmt;
};
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  // if each node stored [numAtDist0, numAtDist1, numAtDist2, ..., numAtDistK]
  // then we could reroot in O(K) time
  // if we're stepping in to child, then at root, we need to:
  // subtract out child's store array from our arry
  // shift our array right by one (since everything's now 1 farther)
  // set our array[0] = 1
  // but k can be big
  // definitely feels like a rerooting problem
  // maybe another approach is like either:
  // - this is the end of a path
  // - a path passes through this node and into another child
  // yeah actually maybe we could do that and do it like small to large merging
  int n, k;
  cin >> n >> k;
  vector<vector<int>> g(n);
  for (int i = 0; i < n - 1; ++i) {
    int a, b;
    cin >> a >> b;
    g[--a].push_back(--b);
    g[b].push_back(a);
  }
  ll total = 0;
  auto dfs = [&](auto &dfs, int i, int parent) -> HeightStruct {
    HeightStruct heights;
    heights.extraAdder = 0;
    heights.totalAmt = 1;
    heights.distinctHeights[0] = 1; // node i exists at height 0
    // process children
    for (int child : g[i]) {
      if (child != parent) {
        HeightStruct other = dfs(dfs, child, i);
        other.extraAdder++;
        // prune other
        while (!other.distinctHeights.empty() &&
               prev(other.distinctHeights.end())->first + other.extraAdder >
                   k) {
          other.distinctHeights.erase(prev(other.distinctHeights.end()));
        }
        // merge other with mine
        if (heights.totalAmt < other.totalAmt) {
          swap(heights, other);
        }
        for (auto [heightUnadded, cnt] : other.distinctHeights) {
          int height = heightUnadded + other.extraAdder;
          int complement = k - height;
          // combine (subtract to undo the effect of extraAdder)
          total +=
              heights.distinctHeights[complement - heights.extraAdder] * cnt;
        }
        // insert only after we've finished accessing heights ^^^
        for (auto [heightUnadded, cnt] : other.distinctHeights) {
          int height = heightUnadded + other.extraAdder;
          heights.distinctHeights[height - heights.extraAdder] += cnt;
        }
        heights.totalAmt += other.totalAmt;
      }
    }
    return heights;
  };
  dfs(dfs, 0, -1);
  cout << total << endl;
}