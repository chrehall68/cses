#include <bits/stdc++.h>
using namespace std;

const int M = 1'000'000'000;
int main() {
  // so just bfs from every anime shop
  int n, m, k;
  cin >> n >> m >> k;
  vector<int> curLevel(k);
  for (int &animeShop : curLevel) {
    cin >> animeShop;
  }
  vector<vector<int>> edges(n + 1);
  for (int i = 0; i < m; ++i) {
    int a, b;
    cin >> a >> b;
    edges[a].push_back(b);
    edges[b].push_back(a);
  }
  // now just do the bfs
  vector<int> parents(n + 1, -1);
  vector<int> distances(n + 1, M);
  vector<int> specialDistances(n + 1, M);
  vector<bool> isAnimeShop(n + 1);
  for (int animeShop : curLevel) {
    parents[animeShop] = animeShop;
    distances[animeShop] = 0;
    isAnimeShop[animeShop] = true;
  }
  vector<int> nextLevel;
  while (!curLevel.empty()) {
    for (int node : curLevel) {
      for (int conn : edges[node]) {
        if (parents[conn] != parents[node]) {
          specialDistances[parents[node]] =
              min(specialDistances[parents[node]],
                  distances[node] + distances[conn] + 1);
          if (distances[conn] > distances[node] + 1) {
            distances[conn] = distances[node] + 1;
            parents[conn] = parents[node];
            nextLevel.push_back(conn);
          }
        }
      }
    }
    curLevel.clear();
    swap(curLevel, nextLevel);
  }
  // then output
  for (int i = 1; i <= n; ++i) {
    int dist = distances[i];
    if (isAnimeShop[i]) {
      dist = specialDistances[i];
    }

    if (dist == M) {
      cout << -1 << ' ';
    } else {
      cout << dist << ' ';
    }
  }
  cout << endl;
}