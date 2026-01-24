#include <bits/stdc++.h>
#include <ios>
#include <limits>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int n;
  cin >> n;
  vector<string> grid(n);
  for (int i = 0; i < n; ++i) {
    cin >> grid[i];
  }

  // so we determine rankings of all length-x strings
  // and use those rankings to determine rankings of length-x+1 strings
  // we start at the last one
  vector<vector<int>> rankings(n + 1,
                               vector<int>(n + 1, numeric_limits<int>::max()));
  vector<pair<pair<char, int>, pair<int, int>>> curLevel, workingSpace;
  vector<int> counts(max(n, 26));
  rankings[n - 1][n - 1] = 0;
  for (int x = 1; x < 2 * n - 1; ++x) {
    // go diagonal
    int r, c;
    if (x < n) {
      r = n - 1 - x;
      c = n - 1;
    } else {
      c = n - 1 - (x - n);
      r = 0;
    }
    // extract the rankings
    while (r < n && c >= 0) {
      char key = grid[r][c];
      // prev comes from right or down, depending on which is ranked less
      int prev = min(rankings[r + 1][c], rankings[r][c + 1]);
      curLevel.push_back({{key, prev}, {r, c}});
      // advance
      r++;
      c--;
    }
    // then fill in those rankings
    // instead of sort, we'll counting sort
    // first counting sort by the rankings
    fill(counts.begin(), counts.end(), 0);
    workingSpace.clear();
    workingSpace.resize(curLevel.size());
    for (auto [key, _] : curLevel) {
      counts[key.second]++;
    }
    for (int i = 1; i < n; ++i) {
      counts[i] += counts[i - 1];
    }
    // then fill in
    for (int i = curLevel.size() - 1; i >= 0; --i) {
      int prev = curLevel[i].first.second;
      int location = --counts[prev];
      workingSpace[location] = curLevel[i];
    }
    // now counting sort by the letters
    fill(counts.begin(), counts.end(), 0);
    swap(workingSpace, curLevel);
    for (auto &[key, _] : curLevel) {
      counts[key.first - 'A']++;
    }
    for (int i = 1; i < 26; ++i) {
      counts[i] += counts[i - 1];
    }
    // then fill in
    for (int i = curLevel.size() - 1; i >= 0; --i) {
      int key = curLevel[i].first.first;
      int location = --counts[key - 'A'];
      workingSpace[location] = curLevel[i];
    }
    swap(workingSpace, curLevel);
    pair<char, int> prevKey = {'\0', -1};
    int rankNo = -1;
    for (auto &[key, location] : curLevel) {
      rankNo += key != prevKey;
      rankings[location.first][location.second] = rankNo;
      prevKey = key;
    }
    curLevel.clear();
  }
  // now we just go from the start and go to whichever has a lower ranking
  int r = 0, c = 0;
  while (r < n && c < n) {
    // can go right or down
    cout << grid[r][c];
    bool goRight =
        c + 1 < n && (r + 1 >= n || (rankings[r][c + 1] < rankings[r + 1][c]));
    c += goRight;
    r += !goRight;
  }
  cout << endl;
}