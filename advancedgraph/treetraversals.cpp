#include <bits/stdc++.h>
using namespace std;

struct Node {
  int num;
  Node *left, *right;
  Node(int val) : num(val), left(nullptr), right(nullptr) {}
  ~Node() {
    if (left != nullptr) {
      delete left;
      left = nullptr;
    }
    if (right != nullptr) {
      delete right;
      right = nullptr;
    }
  }
};

int main() {
  int n;
  cin >> n;
  vector<int> preOrder(n), inOrder(n);
  for (int &num : preOrder) {
    cin >> num;
  }
  for (int &num : inOrder) {
    cin >> num;
  }

  vector<int> inOrderIdxOf(n + 1);
  for (int i = 0; i < n; ++i) {
    inOrderIdxOf[inOrder[i]] = i;
  }

  int preOrderIdx = 0;
  // preOrderLeft, preOrderRight inclusive
  auto rec = [&](auto &rec, int inOrderLeft, int inOrderRight) -> Node * {
    int val = preOrder[preOrderIdx];
    Node *res = new Node(val);

    int inOrderIdx = inOrderIdxOf[val];
    if (inOrderIdx != inOrderLeft) {
      // there's stuff on the left
      ++preOrderIdx;
      res->left = rec(rec, inOrderLeft, inOrderIdx - 1);
    }
    if (inOrderIdx != inOrderRight) {
      // there's stuff on the right
      ++preOrderIdx;
      res->right = rec(rec, inOrderIdx + 1, inOrderRight);
    }

    return res;
  };
  Node *tree = rec(rec, 0, n - 1);
  // now just walk the tree
  auto walk = [&](auto &walk, Node *node) -> void {
    if (node->left != nullptr) {
      walk(walk, node->left);
    }
    if (node->right != nullptr) {
      walk(walk, node->right);
    }
    cout << node->num << ' ';
  };
  walk(walk, tree);
  cout << endl;
}