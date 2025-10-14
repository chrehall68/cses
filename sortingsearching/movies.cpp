#include <bits/stdc++.h>
using namespace std;

int main() {
  int n;
  cin >> n;
  vector<pair<int, int>> movies; // (end, start)
  for (int i = 0; i < n; ++i) {
    int start, end;
    cin >> start >> end;
    movies.push_back({end, start});
  }
  sort(movies.begin(), movies.end());
  int lastEnd = movies[0].second - 1;
  int used = 0;
  for (int i = 0; i < n; ++i) {
    if (movies[i].second >= lastEnd) {
      lastEnd = movies[i].first;
      ++used;
    }
  }
  cout << used << endl;
}