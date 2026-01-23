#include <bits/stdc++.h>
#include <queue>
using namespace std;

int main() {
  int n;
  cin >> n;
  // customers[i] = {arrive, depart, originalIdx}
  vector<tuple<int, int, int>> customers(n);
  for (int i = 0; i < n; ++i) {
    int arrive, depart;
    cin >> arrive >> depart;
    customers[i] = {arrive, depart, i};
  }
  sort(customers.begin(), customers.end());

  int numRooms = 0;
  vector<int> roomNos(n);
  vector<int> availableRooms;
  // min pq of {departure time, roomNo}
  priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
  for (auto [arrive, depart, originalIdx] : customers) {
    while (!pq.empty() && pq.top().first < arrive) {
      // then a room becomes available
      availableRooms.push_back(pq.top().second);
      pq.pop();
    }
    // need a new room if nothing is available
    if (availableRooms.empty()) {
      availableRooms.push_back(++numRooms);
    }
    // then just take an arbitrary available room
    roomNos[originalIdx] = availableRooms.back();
    pq.push({depart, availableRooms.back()});
    availableRooms.pop_back();
  }
  // output
  cout << numRooms << endl;
  for (int i = 0; i < n; ++i) {
    cout << roomNos[i] << " ";
  }
  cout << endl;
}