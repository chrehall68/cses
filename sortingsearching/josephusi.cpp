#include <bits/stdc++.h>
using namespace std;

int main() {
  int n;
  cin >> n;
  list<int> people;
  for (int i = 1; i <= n; ++i) {
    people.push_back(i);
  }
  auto it = people.begin();
  while (!people.empty()) {
    if (it == --people.end()) {
      it = people.begin();
    } else {
      it++;
    }
    cout << *it << " ";
    auto toErase = it;
    if (it == --people.end()) {
      it = people.begin();
    } else {
      it++;
    }
    people.erase(toErase);
  }
  cout << endl;
}