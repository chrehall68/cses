#include <algorithm>
#include <limits>
#include <map>
#include <queue>
#include <set>
#include <utility>
#include <vector>

using adjacencyList = std::vector<std::vector<int>>;
using adjacencyMatrix = std::vector<std::vector<long long>>;

std::pair<adjacencyMatrix, std::map<int, int>>
preprocess(adjacencyMatrix &graph) {
  std::map<std::pair<int, int>, long long> edges;
  std::map<int, int> adjusted;
  int extraNeeded = 0;
  for (int u = 0; u < graph.size(); ++u) {
    for (int v = 0; v < graph.size(); ++v) {
      int capacity = graph[u][v];
      if (capacity > 0) {
        std::pair<int, int> directed = {u, v};
        std::pair<int, int> other = {v, u};
        if (edges.find(other) != edges.end()) {
          // this is a case of (a, b) and (b, a)
          // so we need to adjust
          // make a new vertex at (n+extraNeeded)
          int newVertex = graph.size() + extraNeeded;
          edges[{u, newVertex}] = capacity;
          edges[{newVertex, v}] = capacity;
          adjusted[newVertex] = v;
          extraNeeded++;
        } else {
          // no need to adjust
          edges[directed] = capacity;
        }
      }
    }
  }
  // create new graph
  if (extraNeeded == 0) {
    return {graph, adjusted};
  }
  adjacencyMatrix adjustedGraph(
      graph.size() + extraNeeded,
      std::vector<long long>(graph.size() + extraNeeded, 0));
  for (auto it = edges.begin(); it != edges.end(); ++it) {
    auto [edge, capacity] = *it;
    adjustedGraph[edge.first][edge.second] = capacity;
  }
  return {adjustedGraph, adjusted};
}

/**
 * @brief Changes the edgeFlows matrix to correspond to the original graph
 *
 * @param edgeFlows the edge flows. All the added vertices should be at the end.
 * @param adjustments the adjustments.
 * @return adjacencyMatrix the edgeflows for the original graph. mat[from][to] =
 * flow or -1 if no edge exists.
 */
adjacencyMatrix postprocess(adjacencyMatrix &edgeFlows,
                            std::map<int, int> &adjustments) {
  int newSize = edgeFlows.size() - adjustments.size();
  adjacencyMatrix result(newSize, std::vector<long long>(newSize, -1));

  for (int u = 0; u < edgeFlows.size(); ++u) {
    for (int v = 0; v < edgeFlows.size(); ++v) {
      if (edgeFlows[u][v] != -1) {
        // there's an actual flow
        // see what it corresponds to
        if (adjustments.count(u) || adjustments.count(v)) {
          // at least one is an added vertex
          int actualU = u;
          if (adjustments.count(u)) {
            actualU = adjustments[u];
          }
          int actualV = v;
          if (adjustments.count(v)) {
            actualV = adjustments[v];
          }
          result[actualU][actualV] = edgeFlows[u][v];
        } else {
          // none of them is an added vertex
          result[u][v] = edgeFlows[u][v];
        }
      }
    }
  }
  return result;
}

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
  int n, m;
  cin >> n >> m;
  adjacencyMatrix graph(n, vector<long long>(n, 0));
  adjacencyList lst(n);
  for (int i = 0; i < m; ++i) {
    int a, b;
    cin >> a >> b;
    a--;
    b--;
    graph[a][b] = 1;
    graph[b][a] = 1;
    lst[a].push_back(b);
    lst[b].push_back(a);
  }
  // find max flow
  auto [adjustedMatrix, adjustments] = preprocess(graph);
  auto [flow, edgeFlows] = edmondKarp(adjustedMatrix, 0, n - 1);
  auto result = postprocess(edgeFlows, adjustments);
  cout << flow << endl;
  // then do a bfs to find the cut. all edges
  // leaving the cut will be our edge cut
  queue<int> q;
  q.push(0);
  vector<bool> used(n, false);
  used[0] = true;
  while (!q.empty()) {
    int top = q.front();
    q.pop();
    for (int conn : lst[top]) {
      if (result[top][conn] != 1) {
        // this isn't a saturated edge, so follow it
        if (!used[conn]) {
          used[conn] = true;
          q.push(conn);
        }
      }
    }
  }
  // now do one more time to figure out which are the edges leaving this
  // partition
  for (int u = 0; u < n; ++u) {
    if (!used[u]) {
      continue;
    }
    for (int v : lst[u]) {
      if (result[u][v] == 1 && !used[v]) {
        // this is a used edge that leaves the partition
        cout << u + 1 << " " << v + 1 << endl;
      }
    }
  }
}