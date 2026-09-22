#include <bits/stdc++.h>
using namespace std;

int main() {
  // use the algorithm we learned in graph theory
  // use the smallest node that we haven't used yet
  // that doesn't appear in sequence[i..]
  int n;
  cin >> n;
  vector<int> sequence(n - 2);
  vector<int> counts(n + 1);
  for (int &num : sequence) {
    cin >> num;
    counts[num]++;
  }
  set<int> available;
  for (int i = 1; i <= n; ++i) {
    if (counts[i] == 0) {
      available.insert(i);
    }
  }
  // then iterate through
  for (int to : sequence) {
    assert(!available.empty());
    int from = *available.begin();
    available.erase(from);
    // and now check to see whether edgeTo is available
    if (--counts[to] == 0) {
      available.insert(to);
    }

    cout << to << ' ' << from << '\n';
  }
  assert(available.size() == 2);
  int a = *available.begin();
  int b = *prev(available.end());
  cout << a << ' ' << b << endl;
}