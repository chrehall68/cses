#include <bits/stdc++.h>
using namespace std;

void hanoi(vector<pair<int, int>> &result, vector<int> &positions, int num,
           int goal) {
  // move everything below it first
  int myPosition = positions[num];
  int otherPosition = 1 + 2 + 3 - myPosition - goal;
  for (int otherNum = num - 1; otherNum > 0; --otherNum) {
    // move this number to something that isn't
    // my position or my goal position
    hanoi(result, positions, otherNum, otherPosition);
  }
  // then move me
  result.push_back({myPosition, goal});
  positions[num] = goal;
}

int main() {
  int n;
  cin >> n;
  vector<pair<int, int>> result;
  vector<int> positions(n + 1, 1);
  // move everything to 3
  for (int num = n; num > 0; --num) {
    hanoi(result, positions, num, 3);
  }

  // now output stuff
  cout << result.size() << endl;
  for (auto [from, to] : result) {
    cout << from << " " << to << endl;
  }
}