#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll C = 1'000'000'007;
ll modinv(ll v) {
  if (v <= 1) {
    return v;
  }
  return C - C / v * modinv(C % v) % C;
}
int main() {
  // so if we have n
  // divisor -> contribution to sum
  // 1 -> n *1
  // 2 -> floor(n/2) *2
  // 3 -> floor(n/3) *3
  // 4 -> floor(n/4) *4
  // ...
  // i -> floor(n/i) *i
  // so there's some numbers for which floor(n/i) == 1
  // some numbers for which floor(n/i) == 2
  // some numbers for which floor(n/i) == x
  // and it turns out that there are only o(2 sqrt(n)) distinct
  // values of floor(n/i)
  // after all, for numbers 1..=sqrt(n), those could all give distinct values
  // but then for every divisor sqrt(n)+1..=n, those all must have their
  // floored division value < sqrt(n) (and there's only sqrt(n) possible numbers
  // there)
  // so maybe we can process these groups together if we can find the
  // min/max value of i for which the floor divs are equal, then this is
  // possible

  ll n;
  cin >> n;
  // handle the sqrt(n) numbers leading up
  ll sum = 0;
  ll divisor = 1;
  while (divisor * divisor <= n) {
    ll floored = n / divisor;
    sum = (sum + floored * divisor % C) % C;
    ++divisor;
  }
  ll psum = (divisor - 1) * divisor % C * modinv(2) % C;
  ll floored = n / divisor;
  while (floored >= 1) {
    // now we need the last number such that n / i == floored
    // and we know that cur is the first number such that n/i == floored
    // floor(n / i) == some value
    // how many such i?
    // maybe is it easier "what's the first number such that" floor(n/i) == x
    // hmm seems like it's actually easier to find
    // "what's the last number such that floor(n/i) == x"
    // since it seems like that's just (n // x)
    ll lastDivisor = n / floored % C;
    // we now need the sum from (prevNumber, lastDivisor]
    ll curPsum = lastDivisor * (lastDivisor + 1) % C * modinv(2) % C;
    ll dif = ((curPsum - psum) % C + C) % C;
    sum = (sum + dif * floored % C) % C;

    // advance
    --floored;
    psum = curPsum;
  }
  cout << sum << endl;
}