// #define _GLIBCXX_DEBUG
// currently too slow
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct NodeInfo {
  int startTime, endTime;
  ll value;

  bool operator<(const NodeInfo &o) const {
    // given that they're generated from eulerian tour,
    // no start times are the same.
    return startTime < o.startTime;
  }
  bool operator==(const NodeInfo &o) const { return startTime == o.startTime; }
};
// inner segtree is just a regular range maximum segtree
// with point updates
class InnerSegtree {
  struct InnerInfo {
    // these are finish times
    int mi;
    int ma;
    // this is the maximum value in this segment
    ll val;
  };
  vector<InnerInfo> levels;
  vector<pair<size_t, size_t>> levelInfo; // {size, start}
  size_t n;

public:
  InnerSegtree(vector<NodeInfo> &nodes) : n(nodes.size()) {
    // the nodes should already be sorted by finish time
    int prevFinishTime = -1;
    for (NodeInfo &info : nodes) {
      assert(info.endTime > prevFinishTime);
      prevFinishTime = info.endTime;
      levels.push_back({info.endTime, info.endTime, info.value});
    }
    levelInfo.push_back({n, 0});
    while (levelInfo.back().first > 1) {
      auto [size, start] = levelInfo.back();
      size_t ops = 0;
      size_t myStart = levels.size();
      for (size_t i = 0; i < size; i += 2) {
        if (i + 1 < size) {
          levels.push_back(
              {levels[start + i].mi, levels[start + i + 1].ma,
               max(levels[start + i].val, levels[start + i + 1].val)});
        } else {
          levels.push_back(levels[start + i]);
        }
        ops++;
      }
      levelInfo.push_back({ops, myStart});
    }
  }
  // point update
  void update(size_t idx, ll newValue) {
    levels[idx].val = newValue;
    idx /= 2;
    size_t prevStart = 0;
    size_t curStart;
    for (size_t level = 1; level < levelInfo.size();
         prevStart = curStart, ++level, idx /= 2) {
      curStart = levelInfo[level].second;

      if (idx * 2 + 1 < levelInfo[level - 1].first) {
        levels[curStart + idx].val = max(levels[prevStart + idx * 2].val,
                                         levels[prevStart + idx * 2 + 1].val);
      } else {
        levels[curStart + idx] = levels[prevStart + idx * 2];
      }
    }
  }
  // range max
  ll maxHelper(int finishTimeGe, size_t level, size_t levelIdx) {
    if (levelIdx >= levelInfo[level].first) {
      return 0;
    }
    InnerInfo info = levels[levelInfo[level].second + levelIdx];
    if (info.mi >= finishTimeGe) {
      // just use this
      return info.val;
    } else if (info.ma < finishTimeGe) {
      return 0;
    } else {
      return max(maxHelper(finishTimeGe, level - 1, levelIdx * 2),
                 maxHelper(finishTimeGe, level - 1, levelIdx * 2 + 1));
    }
  }
  ll rangeMax(int finishTimeGe) {
    return maxHelper(finishTimeGe, levelInfo.size() - 1, 0);
  }
};
// outer segtree, responsible for merging
class OuterSegtree {
  struct Info {
    // these are start times
    int mi, ma;
    // this is the segtree representing this segment
    InnerSegtree stree;
    // and we need to associate nodeinfos with what index
    // they ended up at
    map<NodeInfo, size_t> toIdx;
  };
  vector<Info> levels;
  vector<pair<size_t, size_t>> levelInfo; // {size, start}
  vector<int> startTimes;
  size_t n;

public:
  OuterSegtree(vector<NodeInfo> &nodes) : n(nodes.size()) {
    // nodes should've been generated from an eulerian tour
    // therefore should already be sorted by start time
    vector<Info> firstLevel;
    vector<vector<NodeInfo>> nodesByChunk(n);
    for (size_t i = 0; i < nodes.size(); ++i) {
      const NodeInfo &info = nodes[i];
      startTimes.push_back(info.startTime);
      nodesByChunk[i].push_back(info);
      levels.push_back({info.startTime,
                        info.startTime,
                        InnerSegtree(nodesByChunk[i]),
                        {{info, 0}}});
    }
    levelInfo.push_back({n, 0});
    const auto comp = [](const NodeInfo &a, const NodeInfo &b) {
      return a.endTime < b.endTime;
    };
    while (levelInfo.back().first > 1) {
      auto [size, start] = levelInfo.back();
      vector<vector<NodeInfo>> nextNodesByChunk;
      size_t myStart = levels.size();
      size_t ops = 0;
      for (size_t i = 0; i < size; i += 2) {
        if (i + 1 < size) {
          // need to merge two things to have them
          // sorted by end time
          auto &chunk1 = nodesByChunk[i];
          auto &chunk2 = nodesByChunk[i + 1];
          vector<NodeInfo> merged(chunk1.size() + chunk2.size());
          std::merge(chunk1.begin(), chunk1.end(), chunk2.begin(), chunk2.end(),
                     merged.begin(), comp);
          map<NodeInfo, size_t> toIdx;
          for (size_t innerIdx = 0; innerIdx < merged.size(); ++innerIdx) {
            toIdx[merged[innerIdx]] = innerIdx;
          }
          levels.push_back({levels[start + i].mi, levels[start + i + 1].ma,
                            InnerSegtree(merged), toIdx});
          nextNodesByChunk.push_back(merged);
        } else {
          levels.push_back(levels[start + i]);
          nextNodesByChunk.push_back(nodesByChunk[i]);
        }
        ops++;
      }
      nodesByChunk = std::move(nextNodesByChunk);
      levelInfo.push_back({ops, myStart});
    }
  }
  void update(const NodeInfo &info) {
    // assumes info is populated with the new value
    auto it = lower_bound(startTimes.begin(), startTimes.end(), info.startTime);
    assert(it != startTimes.end() && *it == info.startTime);
    size_t idx = it - startTimes.begin();
    // update up from there
    for (size_t level = 0; level < levelInfo.size(); ++level, idx /= 2) {
      size_t start = levelInfo[level].second;
      levels[start + idx].stree.update(levels[start + idx].toIdx[info],
                                       info.value);
    }
  }
  ll queryHelper(const NodeInfo &child, const NodeInfo &ancestor, size_t level,
                 size_t levelIdx) {
    if (levelIdx >= levelInfo[level].first) {
      return 0;
    }
    auto &info = levels[levelInfo[level].second + levelIdx];
    if (ancestor.startTime <= info.mi && info.ma <= child.startTime) {
      return info.stree.rangeMax(child.endTime);
    } else if (child.startTime < info.mi || info.ma < ancestor.startTime) {
      return 0;
    } else {
      return max(queryHelper(child, ancestor, level - 1, levelIdx * 2),
                 queryHelper(child, ancestor, level - 1, levelIdx * 2 + 1));
    }
  }
  ll query(const NodeInfo &child, const NodeInfo &ancestor) {
    assert(ancestor.startTime <= child.startTime &&
           child.endTime <= ancestor.endTime);
    return queryHelper(child, ancestor, levelInfo.size() - 1, 0);
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  // we can find the path from node a to node b
  // by using binary lifting
  // but how to find the maximum value on that path?
  // if we didn't have to deal with changes, we would just have
  // our lifts store the maximum in the range [start, 2**lift'th parent]
  // but we need to handle changes

  // in an eulerian tour, a node x is my ancestor
  // if x's first occurrence appears before my first occurrence
  // and x's last occurrence appears after my last occurrence

  // thus, to get the max of all the nodes between node x and its ancestor y
  // you first have all nodes sorted by first occurrence
  // then we have a continuous range [first_occurrence_y, first_occurrence_x]
  // to make up that range, we have at most logN nodes. Inside each node,
  // we have all elements sorted by end time. Then, we query for the max
  // value in the continuous range [last_occurrence_x, last_occurrence_y]
  // and we know that because of how a eulerian tour works, last_occurence_y
  // will be the largest value out of all these values.
  // thus log**2 N time per query
  // and to update a node, you'll update all parents of the node in the outer
  // segtree and inside each of the inner segtrees, update
  // sortedPosition[nodeFinishTime]

  // maybe that's good enough?
  int n, q;
  cin >> n >> q;
  vector<ll> values(n);
  for (ll &num : values) {
    cin >> num;
  }
  vector<vector<int>> g(n);
  for (int i = 0; i < n - 1; ++i) {
    int a, b;
    cin >> a >> b;
    g[--a].push_back(--b);
    g[b].push_back(a);
  }

  constexpr const int MAX_K = 20;
  vector<int> depths(n);
  vector<array<int, MAX_K>> lifts(n);
  vector<NodeInfo> infos(n);
  for (auto &arr : lifts) {
    fill(arr.begin(), arr.end(), -1);
  }
  int time = 0;
  auto dfs = [&](auto &&dfs, int i, int parent) -> void {
    infos[i].startTime = time++;
    infos[i].value = values[i];
    for (int conn : g[i]) {
      if (conn != parent) {
        depths[conn] = depths[i] + 1;
        lifts[conn][0] = i;
        dfs(dfs, conn, i);
      }
    }
    infos[i].endTime = time++;
  };
  dfs(dfs, 0, -1);
  // now finish building lifts
  for (size_t k = 0; k < MAX_K; ++k) {
    for (int i = 0; i < n; ++i) {
      if (lifts[i][k] != -1 && lifts[lifts[i][k]][k] != -1) {
        lifts[i][k + 1] = lifts[lifts[i][k]][k];
      }
    }
  }
  // now build segtree
  auto sortedCopy = infos;
  sort(sortedCopy.begin(), sortedCopy.end());
  OuterSegtree stree(sortedCopy);

  // and handle queries
  for (; q > 0; --q) {
    int qType;
    cin >> qType;
    if (qType == 1) {
      int node;
      ll newValue;
      cin >> node >> newValue;
      infos[--node].value = newValue;
      stree.update(infos[node]);
    } else {
      // find lca using binary lifts
      // then handle both sides independently
      int a, b;
      cin >> a >> b;
      int lower = --a, higher = --b;
      if (depths[b] > depths[a]) {
        lower = b;
        higher = a;
      }
      // lift lower
      for (int k = MAX_K - 1; k >= 0; --k) {
        if (depths[lower] - (1 << k) >= depths[higher]) {
          lower = lifts[lower][k];
        }
      }
      int lca = lower;
      if (lower != higher) {
        // move both up
        for (int k = MAX_K - 1; k >= 0; --k) {
          if (lifts[lower][k] != -1 && lifts[lower][k] != lifts[higher][k]) {
            lower = lifts[lower][k];
            higher = lifts[higher][k];
          }
        }
        assert(lower != higher);
        assert(lifts[lower][0] != -1);
        assert(lifts[lower][0] == lifts[higher][0]);
        lca = lifts[lower][0];
      }

      // now that we have the lca, go from a to lca and b to lca
      ll ma = max(stree.query(infos[a], infos[lca]),
                  stree.query(infos[b], infos[lca]));
      cout << ma << ' ';
    }
  }
  cout << endl;
}