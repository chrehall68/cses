#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
// could do it w/ coordinate compression too
using ordered_set = tree<pair<int, int>, null_type, less<>, rb_tree_tag,
                         tree_order_statistics_node_update>;
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int n, q;
  cin >> n >> q;
  vector<int> nums(n);
  ordered_set s;
  for (int i = 0; i < n; ++i) {
    cin >> nums[i];
    s.insert({nums[i], i});
  }
  for (int i = 0; i < q; ++i) {
    char op;
    int a, b;
    cin >> op >> a >> b;
    if (op == '?') {
      cout << s.order_of_key({b, n}) - s.order_of_key({a, -1}) << '\n';
    } else {
      s.erase({nums[--a], a});
      nums[a] = b;
      s.insert({nums[a], a});
    }
  }
}