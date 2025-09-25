#include <bits/stdc++.h>
#include <vector>
using namespace std;

int ways(vector<vector<bool>> &board, int row, vector<bool> &usedCols,
         vector<bool> &slashDiagonals, vector<bool> &backslashDiagonals) {
  if (row >= board.size()) {
    return 1;
  }
  // place in any of the columns
  int total = 0;
  for (int col = 0; col < 8; ++col) {
    int slashDiagonal = row + col;
    int backslashDiagonal = 7 - row + col;
    if (board[row][col] && !usedCols[col] && !slashDiagonals[slashDiagonal] &&
        !backslashDiagonals[backslashDiagonal]) {
      // mark it as used
      usedCols[col] = true;
      slashDiagonals[slashDiagonal] = true;
      backslashDiagonals[backslashDiagonal] = true;
      // recurse
      total +=
          ways(board, row + 1, usedCols, slashDiagonals, backslashDiagonals);
      // unmark it as used
      usedCols[col] = false;
      slashDiagonals[slashDiagonal] = false;
      backslashDiagonals[backslashDiagonal] = false;
    }
  }
  return total;
}

int main() {
  vector<vector<bool>> board;
  for (int i = 0; i < 8; ++i) {
    string s;
    cin >> s;
    vector<bool> row;
    for (char c : s) {
      row.push_back(c == '.');
    }
    board.push_back(row);
  }
  vector<bool> usedCols(8, false);
  vector<bool> slashDiagonals(8 + 8 - 1, false);
  vector<bool> backslashDiagonals(8 + 8 - 1, false);
  cout << ways(board, 0, usedCols, slashDiagonals, backslashDiagonals) << endl;
}