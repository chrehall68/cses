#include <bits/stdc++.h>
using namespace std;

int findRep(vector<int> &reps, int a) {
  if (reps[a] != a) {
    reps[a] = findRep(reps, reps[a]);
  }
  return reps[a];
};
void maybeUnion(vector<int> &reps, vector<bool> &isRoot, vector<int> &sizes,
                int a, int b) {
  int ra = findRep(reps, a);
  int rb = findRep(reps, b);
  if (ra != rb) {
    // union by size
    int smaller, larger;
    if (sizes[ra] < sizes[rb]) {
      smaller = ra;
      larger = rb;
    } else {
      smaller = rb;
      larger = ra;
    }
    // then update smaller's rep
    isRoot[smaller] = false;
    reps[smaller] = larger;
    sizes[larger] += sizes[smaller];
  }
}
int main() {
  int n, m;
  cin >> n >> m;
  // so this is dsu
  // since things form components
  // and we just need to
  vector<int> reps(n + 1);
  vector<bool> isRoot(n + 1, true);
  vector<int> sizes(n + 1, 1);
  for (int i = 0; i <= n; ++i) {
    reps[i] = i;
  }
  for (int i = 0; i < m; ++i) {
    // union
    int a, b;
    cin >> a >> b;
    maybeUnion(reps, isRoot, sizes, a, b);
  }
  // then just connect anything that needs to be connected
  vector<pair<int, int>> toConnect;
  int prev = -1;
  for (int i = 1; i <= n; ++i) {
    if (isRoot[i]) {
      if (prev != -1) {
        toConnect.push_back({prev, i});
      }
      prev = i;
    }
  }
  cout << toConnect.size() << endl;
  for (auto [a, b] : toConnect) {
    cout << a << " " << b << endl;
  }
}