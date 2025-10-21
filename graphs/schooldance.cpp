#include <algorithm>
#include <limits>
#include <map>
#include <queue>
#include <set>
#include <utility>
#include <vector>

using adjacencyList = std::vector<std::vector<int>>;
using adjacencyMatrix = std::vector<std::vector<long long>>;

std::vector<std::pair<int, int>>
edmondKarpGetPath(adjacencyList &residualGraph,
                  adjacencyMatrix &residualCapacity, int source, int sink) {
  // just find the shortest path w/ a bfs
  std::vector<int> parents(residualGraph.size(), -1);
  std::vector<bool> used(residualGraph.size(), false);
  std::queue<int> q;
  q.push(source);
  used[source] = true;
  while (!q.empty() && parents[sink] == -1) {
    int top = q.front();
    q.pop();

    // now add neighbors
    for (int conn : residualGraph[top]) {
      if (!used[conn] && residualCapacity[top][conn] > 0) {
        used[conn] = true;
        parents[conn] = top;
        q.push(conn);
      }
    }
  }
  // check if valid
  if (parents[sink] == -1) {
    return {};
  }
  // it is, so reconstruct
  std::vector<std::pair<int, int>> path;
  int cur = sink;
  while (cur != source) {
    int parent = parents[cur];
    path.push_back({parent, cur});
    cur = parent;
  }
  return path;
}

/**
 * @brief Calculates maximum flow for the graph
 *
 * @param graph a directed graph in adjacency matrix format, where
 * each entry is {to, capacity}. If there is an edge from a to b,
 * there SHOULD NOT be an edge from b to a.
 * @param source the number for the source vertex
 * @param sink the number for the sink vertex
 * @return std::pair<long long, adjacencyMatrix> a pair
 * of (max flow, per edge flow). per edge flow is a matrix of [from][to] = flow
 * or -1
 */
std::pair<long long, adjacencyMatrix> edmondKarp(adjacencyMatrix &graph,
                                                 int source, int sink) {
  // start by collecting the edge set
  // and mapping out how much is flowing along them
  // -1 means no edge exists
  adjacencyMatrix edgeFlows(graph.size(),
                            std::vector<long long>(graph.size(), -1));
  // for residual graph
  adjacencyList residualGraph(graph.size());
  adjacencyMatrix residualCapacity(graph.size(),
                                   std::vector<long long>(graph.size(), 0));
  for (int u = 0; u < graph.size(); ++u) {
    for (int v = 0; v < graph.size(); ++v) {
      if (graph[u][v] > 0) {
        edgeFlows[u][v] = 0;
        residualGraph[u].push_back(v);
        residualGraph[v].push_back(u);
        residualCapacity[u][v] = graph[u][v];
      }
    }
  }
  // do the main loop
  std::vector<std::pair<int, int>> path =
      edmondKarpGetPath(residualGraph, residualCapacity, source, sink);
  long long flow = 0;
  while (!path.empty()) {
    // calculate path's capacity
    long long capacity = std::numeric_limits<long long>::max();
    for (std::pair<int, int> &edge : path) {
      capacity = std::min(capacity, residualCapacity[edge.first][edge.second]);
    }
    // now augment flow by that
    flow += capacity;
    for (std::pair<int, int> &edge : path) {
      if (edgeFlows[edge.first][edge.second] >= 0) {
        // this edge is in the original graph
        // so mark that more flow is going through it
        edgeFlows[edge.first][edge.second] += capacity;
        // and also in our residual graph, we can have less going through
        // but can have more going back
        residualCapacity[edge.first][edge.second] -= capacity;
        residualCapacity[edge.second][edge.first] += capacity;
      } else {
        // this edge isn't in the original graph
        // so we're really taking flow away from something
        edgeFlows[edge.second][edge.first] -= capacity;
        // but now we can actually have more going through
        // and less going back
        residualCapacity[edge.second][edge.first] += capacity;
        residualCapacity[edge.first][edge.second] -= capacity;
      }
    }
    // and get new path
    path = edmondKarpGetPath(residualGraph, residualCapacity, source, sink);
  }
  return {flow, edgeFlows};
}

#include <iostream>
using namespace std;
int main() {
  int n, m, k;
  cin >> n >> m >> k;
  // n boys, m girls, k pairs
  // boys are first n
  // girls are next m
  int total = 2 + n + m;
  int source = n + m;
  int sink = n + m + 1;
  adjacencyMatrix graph(total, vector<long long>(total, 0));
  for (int i = 0; i < k; ++i) {
    int boy, girl;
    cin >> boy >> girl;
    boy--;
    girl = girl - 1 + n;
    graph[boy][girl] = 1;
    graph[source][boy] = 1;
    graph[girl][sink] = 1;
  }
  auto [flow, edgeFlows] = edmondKarp(graph, source, sink);
  cout << flow << endl;
  // then we just go through the things
  for (int u = 0; u < n; ++u) {
    for (int v = n; v < n + m; ++v) {
      if (edgeFlows[u][v] == 1) {
        cout << u + 1 << " " << v - n + 1 << endl;
      }
    }
  }
}