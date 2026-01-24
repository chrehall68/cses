#include <bits/stdc++.h>
#include <limits>
using namespace std;

int main() {
  int n, k;
  cin >> n >> k;
  // movies[i] = {end, start}
  vector<pair<int, int>> movies(n);
  for (int i = 0; i < n; ++i) {
    int start, end;
    cin >> start >> end;
    movies[i] = {end, start};
  }
  sort(movies.begin(), movies.end());

  multiset<int> freeTimes;
  for (int i = 0; i < k; ++i) {
    freeTimes.insert(numeric_limits<int>::min());
  }
  int watchable = 0;
  for (auto [end, start] : movies) {
    // see if someone is free to take this movie
    // someone's free to take it if someone finished watching their movie at
    // a time <= the movie's start
    auto it = freeTimes.upper_bound(start);
    if (it != freeTimes.begin()) {
      freeTimes.erase(--it);
      watchable++;
      freeTimes.insert(end);
    }
  }
  cout << watchable << endl;
}