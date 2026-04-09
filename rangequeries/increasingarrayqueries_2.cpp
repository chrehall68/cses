// alternate solution for increasingarrayqueries
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main() {
  // process queries offline
  // we'll process right to left
  // stack will store the maxes as a decreasing stack, and how much it costs
  // to process nums[i..]
  // since cost for nums[a..b] is cost for nums[a..] - nums[b].. as long as
  // the numbers are ascending (which is what our stack guarantees)
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int n, q;
  cin >> n >> q;
  n++;
  vector<ll> nums(n);
  vector<ll> psums(n + 1);
  for (int i = 0; i < n - 1; ++i) {
    cin >> nums[i];
    psums[i + 1] = psums[i] + nums[i];
  }
  nums[n - 1] = 1'000'000'001;
  psums[n] = psums[n - 1] + nums[n - 1];
  vector<tuple<int, int, int>> qs(q);
  for (int i = 0; i < q; ++i) {
    int a, b;
    cin >> a >> b;
    qs[i] = {--a, --b, i};
  }
  sort(qs.begin(), qs.end());

  // decreasing
  vector<pair<int, ll>> sta; // {idx, cost}
  vector<ll> res(q);
  sta.push_back({n - 1, 0});
  for (int i = n - 2; i >= 0; --i) {
    // insert this
    while (nums[sta.back().first] <= nums[i]) {
      assert(sta.size() >= 2);
      sta.pop_back();
    }
    assert(sta.size() >= 1);
    ll myContribution =
        nums[i] * (sta.back().first - i) - (psums[sta.back().first] - psums[i]);
    ll total = sta.back().second + myContribution;
    sta.push_back({i, total});

    // process any queries that start here
    while (!qs.empty() && get<0>(qs.back()) == i) {
      auto [l, r, resIdx] = qs.back();
      qs.pop_back();
      // now find what r falls behind and subtract that amount
      // find last idx such that sta[idx].first > r
      // and then take care of the remainder
      int low = 0;
      int high = sta.size() - 1;
      int best = 0;
      while (low <= high) {
        int mid = (low + high) / 2;
        if (sta[mid].first > r) {
          // works
          best = mid;
          low = mid + 1;
        } else {
          high = mid - 1;
        }
      }
      ll cost = sta.back().second - sta[best].second;
      // then account for the remaining; the stuff to subtract starts at r+1
      assert(best + 1 < sta.size());
      int end = sta[best].first; // exclusive
      assert(end > r);
      ll rep = nums[sta[best + 1].first];
      ll toSubtract = rep * (end - (r + 1)) - (psums[end] - psums[r + 1]);
      cost -= toSubtract;
      res[resIdx] = cost;
    }
  }
  for (ll num : res) {
    cout << num << '\n';
  }
}