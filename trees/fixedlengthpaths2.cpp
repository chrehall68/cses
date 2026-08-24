#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// dynamic segtree
// for calculating sums of ranges
// the whole idea behind a dynamic segtree is just that if we know that
// most positions won't be accessed, there's no point in creating nodes
// for those positions, and we can instead allocate nodes dynamically
class DynamicSegtree {
  using NodePtr = int;
  static constexpr const NodePtr EMPTY = -1;
  struct Node;
  vector<Node> elements;
  vector<NodePtr> leaves;
  struct Node {
    int left, right; // inclusive left, exclusive right
    ll sum;
    NodePtr l, r;
  };
  NodePtr createNode(int left, int right) {
    NodePtr ident = elements.size();
    elements.push_back(Node{left, right, 0, EMPTY, EMPTY});
    if (left == right - 1) {
      leaves.push_back(ident);
    }
    return ident;
  }
  // [left, right)
  ll sumInRange(NodePtr ptr, int left, int right) const {
    if (ptr == EMPTY) {
      return 0;
    }
    Node node = elements[ptr];
    if (left <= node.left && node.right <= right) {
      return node.sum;
    } else if (right <= node.left || node.right <= left) {
      return 0;
    } else {
      // query children
      return sumInRange(node.l, left, right) + sumInRange(node.r, left, right);
    }
  }
  void increment(NodePtr ptr, int num, ll amt) {
    assert(ptr != EMPTY && ptr < elements.size());
    Node node = elements[ptr];
    if (node.left == node.right - 1 && node.left == num) {
      node.sum += amt;
    } else if (node.left > num || node.right <= num) {
    } else {
      // in one of children
      int mid = (node.right + node.left) / 2;
      assert(mid - node.left >= 1);
      assert(node.right - mid >= 1);
      if (node.l == EMPTY) {
        node.l = createNode(node.left, mid);
      }
      if (node.r == EMPTY) {
        node.r = createNode(mid, node.right);
      }
      increment(node.l, num, amt);
      increment(node.r, num, amt);
      node.sum = elements[node.l].sum + elements[node.r].sum;
    }
    // restore
    elements[ptr] = node;
  }

public:
  // minL, maxR inclusive
  DynamicSegtree(int minL = -300'000, int maxR = 300'000) {
    createNode(minL, maxR + 1);
  }
  // left, right inclusive
  ll sumInRange(int left, int right) const {
    return sumInRange(0, left, right + 1);
  }
  void increment(int num, ll amt) { increment(0, num, amt); }
  // warning not constant time
  vector<pair<int, ll>> getLeaves() const {
    vector<pair<int, ll>> res;
    for (NodePtr leaf : leaves) {
      res.push_back({elements[leaf].left, elements[leaf].sum});
    }
    return res;
  }
};
struct HeightStruct {
  // handlers should know to use extraAdder first
  int extraAdder;
  // stores counts at specific heights
  DynamicSegtree stree;
  ll totalAmt;
};
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  // if each node stored [numAtDist0, numAtDist1, numAtDist2, ..., numAtDistK]
  // then we could reroot in O(K) time
  // if we're stepping in to child, then at root, we need to:
  // subtract out child's store array from our arry
  // shift our array right by one (since everything's now 1 farther)
  // set our array[0] = 1
  // but k can be big
  // definitely feels like a rerooting problem
  // maybe another approach is like either:
  // - this is the end of a path
  // - a path passes through this node and into another child
  // yeah actually maybe we could do that and do it like small to large merging
  int n, k1, k2;
  cin >> n >> k1 >> k2;
  vector<vector<int>> g(n);
  for (int i = 0; i < n - 1; ++i) {
    int a, b;
    cin >> a >> b;
    g[--a].push_back(--b);
    g[b].push_back(a);
  }
  ll total = 0;
  auto dfs = [&](auto &dfs, int i, int parent) -> HeightStruct {
    HeightStruct heights;
    heights.extraAdder = 0;
    heights.totalAmt = 1;
    heights.stree.increment(0, 1);
    // process children
    for (int child : g[i]) {
      if (child != parent) {
        HeightStruct other = dfs(dfs, child, i);
        other.extraAdder++;
        // merge other with mine
        if (heights.totalAmt < other.totalAmt) {
          swap(heights, other);
        }
        vector<pair<int, ll>> otherLeaves = other.stree.getLeaves();
        for (auto [heightUnadded, cnt] : otherLeaves) {
          int height = heightUnadded + other.extraAdder;
          int complementMin = k1 - height;
          int complementMax = k2 - height;
          // combine (subtract to undo the effect of extraAdder)
          ll amtInRange =
              heights.stree.sumInRange(complementMin - heights.extraAdder,
                                       complementMax - heights.extraAdder);
          total += amtInRange * cnt;
        }
        // insert only after we've finished accessing heights ^^^
        for (auto [heightUnadded, cnt] : otherLeaves) {
          int height = heightUnadded + other.extraAdder;
          heights.stree.increment(height - heights.extraAdder, cnt);
        }
        heights.totalAmt += other.totalAmt;
      }
    }
    return heights;
  };
  dfs(dfs, 0, -1);
  cout << total << endl;
}