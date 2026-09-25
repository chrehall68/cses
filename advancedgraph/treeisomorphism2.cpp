#include <bits/stdc++.h>
using namespace std;
using ll = long long;

using modInt = pair<ll, ll>;
constexpr const modInt modIntOfInt(const int num) { return {num, num}; }
constexpr const modInt MODS = {1'000'000'007, 998'244'353};
constexpr const modInt BASE = modIntOfInt(100'002);
modInt &operator+=(modInt &a, const modInt &b) {
  get<0>(a) += get<0>(b);
  get<0>(a) %= get<0>(MODS);
  get<1>(a) += get<1>(b);
  get<1>(a) %= get<1>(MODS);
  return a;
}
modInt &operator*=(modInt &a, const modInt &b) {
  get<0>(a) *= get<0>(b);
  get<0>(a) %= get<0>(MODS);
  get<1>(a) *= get<1>(b);
  get<1>(a) %= get<1>(MODS);
  return a;
}

int dfs(const vector<vector<int>> &tree, map<modInt, int> &ids,
        vector<int> &nodeIds, int i, int parent) {
  vector<int> children;
  for (int conn : tree[i]) {
    if (conn != parent) {
      children.push_back(dfs(tree, ids, nodeIds, conn, i));
    }
  }
  sort(children.begin(), children.end());
  // calculate hash
  modInt h = modIntOfInt(0);
  for (int nodeId : children) {
    h *= BASE;
    h += modIntOfInt(nodeId);
  }

  auto [it, _success] = ids.insert({h, ids.size()});
  nodeIds[i] = it->second;
  return nodeIds[i];
}
bool reroot(const vector<vector<int>> &tree, const map<modInt, int> &ids,
            const vector<int> &nodeIds, const int &goalId, int node, int parent,
            int rerootedParentNodeId) {
  // rerootedParentNodeId = nodeId of parent
  // if the tree was rooted at i (meaning parent was a child of i)
  vector<pair<int, int>> childrenIds; // {id, conn}
  for (int conn : tree[node]) {
    if (conn != parent) {
      childrenIds.push_back({nodeIds[conn], conn});
    } else {
      childrenIds.push_back({rerootedParentNodeId, parent});
    }
  }
  sort(childrenIds.begin(), childrenIds.end());
  // calculate suffix hash
  modInt mult = modIntOfInt(1);
  vector<modInt> suffixHash(childrenIds.size() + 1);
  vector<modInt> basePow(childrenIds.size() + 1);
  basePow[childrenIds.size()] = modIntOfInt(1);
  for (int i = childrenIds.size() - 1; i >= 0; --i) {
    auto [id, _] = childrenIds[i];
    modInt myHash = modIntOfInt(id);
    myHash *= mult;
    myHash += suffixHash[i + 1];
    suffixHash[i] = myHash;
    // advance
    mult *= BASE;
    basePow[i] = mult;
  }

  // see if this is a match
  if (ids.count(suffixHash[0]) && ids.at(suffixHash[0]) == goalId) {
    return true;
  }

  // otherwise, ask children
  modInt prefixHash = modIntOfInt(0);
  bool possible = false;
  for (size_t i = 0; i < childrenIds.size(); ++i) {
    // reroot to child
    auto [id, conn] = childrenIds[i];
    if (conn != parent) {
      modInt rerootedHash = prefixHash;
      rerootedHash *= basePow[i + 1];
      rerootedHash += suffixHash[i + 1];
      if (ids.count(rerootedHash)) {
        // worth continuing
        int rerootedId = ids.at(rerootedHash);
        possible = possible ||
                   reroot(tree, ids, nodeIds, goalId, conn, node, rerootedId);
      }
    }
    // update prefix hash
    prefixHash *= BASE;
    prefixHash += modIntOfInt(id);
  }

  return possible;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  // for the previous version of the problem,
  // we knew that the tree was rooted at node 1
  // now we don't know
  // but we know that we can at least root the first tree at root 1
  // and then just see if we can draw the second tree to look like that
  // so maybe we can reroot and if any of the rerooted versions of the second
  // tree match, then the trees are isomorphic
  int t;
  for (cin >> t; t > 0; --t) {
    int n;
    cin >> n;
    vector<vector<int>> t1(n), t2(n);
    for (int i = 0; i < n - 1; ++i) {
      int a, b;
      cin >> a >> b;
      t1[--a].push_back(--b);
      t1[b].push_back(a);
    }
    for (int i = 0; i < n - 1; ++i) {
      int a, b;
      cin >> a >> b;
      t2[--a].push_back(--b);
      t2[b].push_back(a);
    }
    // we're given that node 1 is the root
    // so dfs'ing works
    map<modInt, int> ids;
    ids[modIntOfInt(-1)] = 0; // just to make 0 never happen
    vector<int> nodeIds(n);
    int t1Id = dfs(t1, ids, nodeIds, 0, -1);
    // populate nodeIds with tree 2's ids
    dfs(t2, ids, nodeIds, 0, -1);
    if (reroot(t2, ids, nodeIds, t1Id, 0, -1, -1)) {
      cout << "YES" << endl;
    } else {
      cout << "NO" << endl;
    }
  }
}