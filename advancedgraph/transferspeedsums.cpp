#pragma GCC optimize("O3", "unroll-loops")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

using namespace std;
using ll = long long;

pair<ll, ll> &operator+=(pair<ll, ll> &a, const pair<ll, ll> &b) {
  a.first += b.first;
  a.second += b.second;
  return a;
}

// __gnu_pbds is a very fast implementation of a tree
// and allows us to store custom metadata in each tree node and
// define methods that can be called
template <class Node_CItr, class Node_Itr, class Cmp_Fn, class _Alloc>
class custom_node_update
    : public tree_order_statistics_node_update<Node_CItr, Node_Itr, Cmp_Fn,
                                               _Alloc> {
public:
  // {count, weightedSum}
  typedef pair<ll, ll> metadata_type;

  // note: just using int and ll raw since that's what this
  // will be specialized as
  ll extract_value(Node_CItr it) { return (*it)->second; }
  int extract_key(Node_CItr it) { return (*it)->first; }

  // value for just this {key, cnt} pair
  metadata_type justMe(Node_CItr it) {
    ll cnt = extract_value(it);
    return {cnt, cnt * extract_key(it)};
  }

  // update metadata from left and right
  void operator()(Node_Itr it, Node_CItr end_it) {
    // account for itself
    metadata_type x = justMe(it);

    if (it.get_l_child() != end_it) // add a sum in left child:
      x += it.get_l_child().get_metadata();
    if (it.get_r_child() != end_it) // add a sum in right child:
      x += it.get_r_child().get_metadata();

    const_cast<metadata_type &>(it.get_metadata()) = x;
  }

  // remnant from inheriting from tree_order_statistics_node_update
  int64_t order_of_key(int key) const {
    throw invalid_argument("Don't call this anymore");
  }

  // {countGe, weightedSumLt}
  metadata_type query(int ge) {
    metadata_type accum = {0, 0};
    query(node_begin(), ge, accum);
    return accum;
  }

  virtual Node_CItr node_begin() const = 0; // pointer to the root
  virtual Node_CItr node_end() const = 0;   // one past the last node

private:
  void query(Node_CItr it, int ge, metadata_type &accum) {
    if (it == node_end()) {
      return;
    }

    // we know that a red black tree is a valid bst
    // so we only need to descend the tree once
    // and this method is written tail recursively to better allow this
    if (Cmp_Fn()((*it)->first, ge)) {
      // if current number < ge, then all left child, and this
      // need to get added to the weighted sum
      // and then we recurse on the right
      accum.second += justMe(it).second;
      Node_CItr l_it = it.get_l_child();
      if (l_it != node_end()) {
        accum.second += l_it.get_metadata().second;
      }
      query(it.get_r_child(), ge, accum);
    } else {
      // current number >= ge, so this and all right child
      // need to be added to count
      accum.first += justMe(it).first;
      Node_CItr r_it = it.get_r_child();
      if (r_it != node_end()) {
        accum.first += r_it.get_metadata().first;
      }
      query(it.get_l_child(), ge, accum);
    }
  }
};
using tree_ptr = __gnu_pbds::tree<int, ll, less<>, __gnu_pbds::rb_tree_tag,
                                  custom_node_update>;
using CustomTree = shared_ptr<tree_ptr>;

struct Info {
  CustomTree stree;
  int size;
  Info() : stree(make_shared<tree_ptr>()), size(0) {}

  void insert(int num, ll cnt) {
    ll prevCnt = 0;
    auto it = stree->find(num);
    if (it != stree->end()) {
      prevCnt = it->second;
      stree->erase(it);
    }

    stree->insert({num, prevCnt + cnt});
    size += cnt;
  }
  void clampTo(int ma) {
    while (!stree->empty() && prev(stree->end())->first > ma) {
      auto it = prev(stree->end());
      auto [num, cnt] = *it;
      // erase previous
      size -= cnt;
      stree->erase(it);
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
    myInfo.insert(1'000'001, 1);
    for (auto [conn, speed] : g[i]) {
      if (conn != parent) {
        Info childInfo = dfs(dfs, conn, i);
        childInfo.clampTo(speed);
        // then small to large merge
        if (myInfo.size < childInfo.size) {
          swap(myInfo, childInfo);
        }
        // so now childInfo is the smaller one, insert that
        for (auto [num, cnt] : *childInfo.stree) {
          auto [countOfGe, weightedSumOfLt] = myInfo.stree->query(num);
          // num is the limiting factor for these
          total += countOfGe * cnt * num;
          // limiting factor is encoded in weighted sum
          total += weightedSumOfLt * cnt;
        }
        // and then actually do the merge
        for (auto [num, cnt] : *childInfo.stree) {
          myInfo.insert(num, cnt);
        }
      }
    }

    return myInfo;
  };
  dfs(dfs, 1, 0);

  cout << total << endl;
}