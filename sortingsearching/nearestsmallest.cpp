#include <bits/stdc++.h>
using namespace std;

int main() {
  int n;
  cin >> n;
  vector<int> nums(n);
  for (int i = 0; i < n; ++i) {
    cin >> nums[i];
  }
  stack<int> s; // monotonically increasing stack
  vector<int> firstSmaller(n, 0);
  for (int i = n - 1; i >= 0; --i) {
    while (!s.empty() && nums[s.top()] > nums[i]) {
      // this is first smaller
      firstSmaller[s.top()] = i + 1;
      s.pop();
    }
    // push this
    s.push(i);
  }
  for (int i = 0; i < n; ++i) {
    cout << firstSmaller[i] << " ";
  }
  cout << endl;
}