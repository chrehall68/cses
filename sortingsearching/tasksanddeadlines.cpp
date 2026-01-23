#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  int n;
  cin >> n;
  // we have sum(d-f)
  // which is just sum(d) - sum(f)
  // when we see that, we realize we want to minimize all the finishing times
  // so we want to do shortest jobs first
  ll result = 0;
  ll curTime = 0;
  vector<int> durations(n);
  for (int i = 0; i < n; ++i) {
    int duration, deadline;
    cin >> duration >> deadline;
    result += deadline;
    durations[i] = duration;
  }
  sort(durations.begin(), durations.end());
  for (int duration : durations) {
    curTime += duration;
    result -= curTime;
  }
  cout << result << endl;
}