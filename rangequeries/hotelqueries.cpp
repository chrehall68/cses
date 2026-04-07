#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Segtree {
  vector<vector<ll>> maxes;
  int n;
  Segtree(vector<ll> init) : n(init.size()) {
    maxes.push_back(init);
    while (maxes.back().size() > 1) {
      vector<ll> &b = maxes.back();
      vector<ll> next;
      for (size_t i = 0; i < b.size(); i += 2) {
        if (i + 1 < b.size()) {
          next.push_back(max(b[i], b[i + 1]));
        } else {
          next.push_back(b[i]);
        }
      }
      maxes.push_back(next);
    }
  }
  int firstGeIdx(ll query) {
    if (maxes[maxes.size() - 1][0] < query) {
      return -1;
    }
    int idx = 0;
    for (int level = maxes.size() - 1; level >= 0; --level, idx *= 2) {
      if (maxes[level][idx] < query) {
        idx++;
      }
    }
    return idx / 2;
  }
  void decrement(int idx, ll amt) {
    maxes[0][idx] -= amt;
    idx /= 2;
    for (int level = 1; level < maxes.size(); ++level, idx /= 2) {
      maxes[level][idx] = maxes[level - 1][idx * 2];
      if (idx * 2 + 1 < maxes[level - 1].size()) {
        maxes[level][idx] =
            max(maxes[level][idx], maxes[level - 1][idx * 2 + 1]);
      }
    }
  }
};

int main() {
  // find first index of a hotel with rooms >= query
  // could log**2(n) n this by binary searching for last index such that
  // max in hotels[0..=idx] is >= query
  // but that can be sped up to logn n by just checking left and right
  int n, m;
  cin >> n >> m;
  vector<ll> hotels(n);
  for (int i = 0; i < n; ++i) {
    cin >> hotels[i];
  }
  Segtree s(hotels);
  for (int i = 0; i < m; ++i) {
    int rooms;
    cin >> rooms;
    int idx = s.firstGeIdx(rooms);
    cout << idx + 1 << '\n';
    if (idx != -1) {
      s.decrement(idx, rooms);
    }
  }
}