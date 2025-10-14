#include <bits/stdc++.h>
using namespace std;
int main() {
  int n;
  cin >> n;
  set<int> distinct;
  for (int i = 0; i < n; ++i) {
    int num;
    cin >> num;
    distinct.insert(num);
  }
  cout << distinct.size() << endl;
}