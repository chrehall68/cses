#pragma GCC optimize("O3", "unroll-loops")
#include <bits/stdc++.h>
// currently too slow

using namespace std;
using ll = long long;

// dynamic segtree
// aka sparse segtree
class DynamicSegtree {
  using NodePtr = int;
  const static NodePtr NULLPTR = -1;
  struct Node {
    int left, right; // inclusive
    NodePtr l, r;
    ll count;
    ll weightedSum; // count(1)*1 + count(2)*2 + ...

    Node(int left, int right)
        : left(left), right(right), l(NULLPTR), r(NULLPTR), count(0),
          weightedSum(0) {}
  };

  vector<Node> nodes;
  NodePtr insertNode(Node n) {
    nodes.push_back(n);
    return nodes.size() - 1;
  }

  Node ensureChildren(NodePtr p) {
    Node node = nodes[p];
    if (node.l == NULLPTR) {
      assert(node.r == NULLPTR);
      int cnt = node.right - node.left + 1;
      int halfAmt = cnt / 2;
      nodes[p].l = insertNode(Node(node.left, node.left + halfAmt - 1));
      nodes[p].r = insertNode(Node(node.left + halfAmt, node.right));
    }
    return nodes[p];
  }

  // returns {count, weightedSum}
  pair<ll, ll> query(NodePtr p, int queryL, int queryR) {
    Node node = nodes[p];
    if (queryL <= node.left && node.right <= queryR) {
      return {node.count, node.weightedSum};
    } else if (node.right < queryL || queryR < node.left) {
      return {0, 0};
    }
    node = ensureChildren(p);
    auto [c1, w1] = query(node.l, queryL, queryR);
    auto [c2, w2] = query(node.r, queryL, queryR);
    return {c1 + c2, w1 + w2};
  }

  void increment(NodePtr p, int num, ll cnt) {
    Node node = nodes[p];
    if (node.left == num && node.right == num) {
      // made it to a leaf
      nodes[p].count += cnt;
      nodes[p].weightedSum += cnt * num;
    } else if (node.left > num || node.right < num) {
      return; // out of range
    } else {
      // in one of children
      node = ensureChildren(p);
      increment(node.l, num, cnt);
      increment(node.r, num, cnt);
      // and pull updates to my values
      nodes[p].count = nodes[node.l].count + nodes[node.r].count;
      nodes[p].weightedSum =
          nodes[node.l].weightedSum + nodes[node.r].weightedSum;
    }
  }

  NodePtr root;

public:
  DynamicSegtree(int left, int right) { root = insertNode(Node(left, right)); }

  void increment(int num, ll cnt) { increment(root, num, cnt); }
  pair<ll, ll> query(int left, int right) { return query(root, left, right); }
};

const int RANGE_MAX = 1'000'002;
const int RANGE_MIN = 0;
struct Info {
  DynamicSegtree stree;
  map<int, ll> cnts;
  int size;
  Info() : stree(RANGE_MIN, RANGE_MAX), size(0) {}

  void insert(int num, ll cnt) {
    cnts[num] += cnt;
    stree.increment(num, cnt);
    size += cnt;
  }
  void clampTo(int ma) {
    while (!cnts.empty() && prev(cnts.end())->first > ma) {
      auto it = prev(cnts.end());
      auto [num, cnt] = *it;
      // erase previous
      insert(num, -cnt);
      cnts.erase(it);
      // and insert ma
      insert(ma, cnt);
    }
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int n;
  cin >> n;
  vector<vector<pair<int, ll>>> g(n + 1);
  for (int i = 0; i < n - 1; ++i) {
    int a, b, speed;
    cin >> a >> b >> speed;
    g[a].push_back({b, speed});
    g[b].push_back({a, speed});
  }
  // now do a dfs
  ll total = 0;
  auto dfs = [&](auto &dfs, int i, int parent) -> Info {
    Info myInfo;
    myInfo.insert(RANGE_MAX - 1, 1);
    for (auto [conn, speed] : g[i]) {
      if (conn != parent) {
        Info childInfo = dfs(dfs, conn, i);
        childInfo.clampTo(speed);
        // then small to large merge
        if (myInfo.size < childInfo.size) {
          swap(myInfo, childInfo);
        }
        // so now childInfo is the smaller one, insert that
        for (auto [num, cnt] : childInfo.cnts) {
          auto [countOfGe, _w] = myInfo.stree.query(num, RANGE_MAX);
          auto [_c, weightedSumOfLt] = myInfo.stree.query(RANGE_MIN, num - 1);
          // num is the limiting factor for these
          total += countOfGe * cnt * num;
          // limiting factor is encoded in weighted sum
          total += weightedSumOfLt * cnt;
        }
        // and then actually do the merge
        for (auto [num, cnt] : childInfo.cnts) {
          myInfo.insert(num, cnt);
        }
      }
    }

    return myInfo;
  };
  dfs(dfs, 1, 0);

  cout << total << endl;
}