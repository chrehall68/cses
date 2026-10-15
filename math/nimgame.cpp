#include <bits/stdc++.h>
using namespace std;

int main(){
  int t;
  for(cin >> t; t > 0; --t){
    int n;
    int xo = 0;
    for (cin >> n; n > 0; --n){
      int num;
      cin >> num;
      xo ^= num;
    }
    if (xo != 0){
      cout << "first" << endl;
    } else {
      cout << "second" << endl;
    }
  }
}
