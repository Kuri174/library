#include <bits/stdc++.h>
using namespace std;

#ifdef _DEBUG
#include "_DEBUG.hpp"
#endif
#define int long long
const long long inf = 2e18;
const int mod = 1e9 + 7;

template <typename T>
istream &operator>>(istream &is, vector<T> &v) {
  for (T &in : v) is >> in;
  return is;
}

template <class T>
vector<T> make_vec(size_t a) {
  return vector<T>(a);
}

template <class T, class... Ts>
auto make_vec(size_t a, Ts... ts) {
  return vector<decltype(make_vec<T>(ts...))>(a, make_vec<T>(ts...));
}

template <class T, class V>
typename enable_if<is_class<T>::value == 0>::type fill(T &t, const V &v) {
  t = v;
}

template <class T, class V>
typename enable_if<is_class<T>::value != 0>::type fill(T &t, const V &v) {
  for (auto &e : t) fill(e, v);
}

// nCr mod p O(p^2 + log(n))
int Lucas(int n, int r, int p) {
  assert(n >= r);
  vector<vector<int>> dp(p, vector<int>(p));  // dp[n][r] = nCr
  for (int i = 0; i < p; i++) {
    dp[i][0] = 1;
    for (int j = 1; j <= i; j++) {
      dp[i][j] = (dp[i - 1][j - 1] + dp[i - 1][j]) % p;
    }
  }
  int res = 1;
  while (n > 0) {
    res = (res * dp[n % p][r % p]) % p;
    n /= p;
    r /= p;
  }
  return res;
}

// https://atcoder.jp/contests/arc117/tasks/arc117_c
signed main() {
  int n;
  cin >> n;
  string s;
  cin >> s;

  int ans = 0;
  for (int i = 0; i < n; i++) {
    int color = (s[i] == 'B' ? 0 : s[i] == 'W' ? 1 : 2);
    ans = (ans + Lucas(n - 1, i, 3) * color) % 3;
  }
  if (n % 2 == 0) ans = (3 - ans) % 3;
  cout << (ans == 0 ? 'B' : ans == 1 ? 'W' : 'R') << endl;

  return 0;
}