#include <bits/stdc++.h>
using namespace std;

int main() {
  int n;
  cin >> n;
  vector<pair<int, int>> points;
  for (int i = 0; i < n; ++i) {
    int arrive, depart;
    cin >> arrive >> depart;
    points.push_back({arrive, 1});
    points.push_back({depart, -1});
  }
  sort(points.begin(), points.end());
  int active = 0;
  int best = 0;
  for (int i = 0; i < points.size(); ++i) {
    active += points[i].second;
    best = max(best, active);
  }
  cout << best << endl;
}