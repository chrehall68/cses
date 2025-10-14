#include <bits/stdc++.h>
#include <ios>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int n, m;
  cin >> n >> m;
  vector<int> nums(n);
  map<int, int> indices;
  for (int i = 0; i < n; ++i) {
    int num;
    cin >> num;
    nums[i] = num;
    indices[num] = i;
  }
  // do initial count
  int required = 0;
  int lastSeen = n;
  for (auto it = indices.begin(); it != indices.end(); ++it) {
    if (it->second < lastSeen) {
      required++;
    }
    lastSeen = it->second;
  }
  // do modifications
  for (int i = 0; i < m; ++i) {
    int a, b;
    cin >> a >> b;

    // move
    if (b < a) {
      swap(a, b);
    }
    a--;
    b--;
    // so now b needs to move back and a needs to move forward
    // we'll move a first
    int aNum = nums[a], bNum = nums[b];
    if (aNum > 1 && indices[aNum - 1] > a && indices[aNum - 1] < b) {
      required--; // moved to after the thing right before it
    }
    if (aNum < n && indices[aNum + 1] > a && indices[aNum + 1] < b) {
      required++; // moved to after the thing right after it
    }
    indices[aNum] = b;
    nums[b] = aNum;
    // repeat for b
    if (bNum > 1 && indices[bNum - 1] > a && indices[bNum - 1] < b) {
      required++; // moved to before the thing right before it
    }
    if (bNum < n && indices[bNum + 1] > a && indices[bNum + 1] < b) {
      required--; // moved to before the thing right after it
    }
    indices[bNum] = a;
    nums[a] = bNum;
    // and adjust in case aNum and bNum are right next to each other
    if (aNum == bNum - 1) {
      // a just moved past it
      required++;
    }
    if (bNum == aNum - 1) {
      // b just moved before it
      required--;
    }
    cout << required << endl;
  }
}