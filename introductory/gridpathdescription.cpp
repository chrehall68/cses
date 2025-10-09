#include <bits/stdc++.h>
#include <vector>

using namespace std;

vector<char> moves(7 * 7);
string matches;
vector<bool> used(7 * 7, false);
// right, down, left, up
vector<pair<int, int>> allPossibs = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
pair<int, int> U = {-1, 0};
pair<int, int> D = {1, 0};
pair<int, int> L = {0, -1};
pair<int, int> R = {0, 1};
int total = 0;
vector<int> stillUnused(4);
pair<int, int> *possib;
vector<vector<int>> bads = {{0, 2}, {1, 3}};

void numMatching(int turn, int r, int c) {
  if (r == 6 && c == 0) {
    total += turn == matches.size();
    return;
  }

  //  handle case where this has 2 places that can't both be reached
  stillUnused.clear();
  for (int i = 0; i < 4; ++i) {
    int rp = r + allPossibs[i].first;
    int cp = c + allPossibs[i].second;
    if ((0 <= rp && rp < 7 && 0 <= cp && cp < 7 && !used[rp * 7 + cp])) {
      stillUnused.push_back(i);
    }
  }
  if (stillUnused == bads[0] || stillUnused == bads[1]) {
    return;
  }

  // if it's the first time
  if (matches[turn] == '?') {
    // can go up/down/left/right
    for (int i = 0; i < allPossibs.size(); ++i) {
      // make sure doesn't go to a used space
      int rp = r + allPossibs[i].first;
      int cp = c + allPossibs[i].second;
      if (0 <= rp && rp < 7 && 0 <= cp && cp < 7 && !used[rp * 7 + cp]) {
        // try it iff it doesn't divide the grid into two unreachable parts
        used[rp * 7 + cp] = true;
        numMatching(turn + 1, rp, cp);
        used[rp * 7 + cp] = false;
      }
    }
  } else {
    if (matches[turn] == 'U') {
      possib = &U;
    } else if (matches[turn] == 'R') {
      possib = &R;
    } else if (matches[turn] == 'D') {
      possib = &D;
    } else if (matches[turn] == 'L') {
      possib = &L;
    }
    int rp = r + possib->first;
    int cp = c + possib->second;
    if (0 <= rp && rp < 7 && 0 <= cp && cp < 7 && !used[rp * 7 + cp]) {
      // try it iff it doesn't divide the grid into two unreachable parts
      used[rp * 7 + cp] = true;
      numMatching(turn + 1, rp, cp);
      used[rp * 7 + cp] = false;
    }
  }

  // after initial reflection,
  // on right | on down
  // left | up
  // right | down
  // up | left
  // down | right
}

int main() {
  cin >> matches;

  used[0] = true;
  // exploit mirrorability of the string
  int firstNonquestionIdx = matches.size();
  int lastNonquestionIdx = 0;
  for (int i = 0; i < matches.size(); ++i) {
    if (matches[i] != '?') {
      firstNonquestionIdx = min(firstNonquestionIdx, i);
      lastNonquestionIdx = i;
    }
  }
  if (firstNonquestionIdx != matches.size()) {
    if (firstNonquestionIdx > (matches.size() - 1 - lastNonquestionIdx)) {
      // worth mirroring
      string other;
      for (int i = matches.size() - 1; i > -1; --i) {
        if (matches[i] != 'L' && matches[i] != 'R') {
          other += matches[i];
        } else if (matches[i] == 'L') {
          other += 'R';
        } else {
          other += 'L';
        }
      }
      matches = other;
    }
  } else {
    cout << 88418 << endl;
    return 0;
  }

  numMatching(0, 0, 0);
  cout << total << endl;
}