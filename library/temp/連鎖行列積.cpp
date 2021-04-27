#include <bits/stdc++.h>
using namespace std;
#ifdef _DEBUG
#include "_DEBUG.hpp"
#endif
#define int long long
const int INF = 1LL << 60;

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

int calc(int x, int y) {
  string sx = to_string(x), sy = to_string(y);
  reverse(sx.begin(), sx.end());
  reverse(sy.begin(), sy.end());
  int res = 0, nx = sx.size(), ny = sy.size(), c = 0, kuri = 0;
  for (int i = 0; i < max(nx, ny); i++) {
    int tx = (nx - 1 < i ? 0 : (int)(sx[i] - '0'));
    int ty = (ny - 1 < i ? 0 : (int)(sy[i] - '0'));
    c += tx + ty;
    res += tx * ty + kuri;
    if (c >= 10)
      kuri = 1;
    else
      kuri = 0;

    c = kuri;
  }
  return res + kuri;
}

// https://onlinejudge.u-aizu.ac.jp/problems/2660
signed main() {
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }

  vector<int> imos(n + 1, 0);
  for (int i = 0; i < n; i++) {
    imos[i + 1] = imos[i] + a[i];
  }

  auto dp = make_vec<int>(n, n);
  fill(dp, INF);
  for (int i = 0; i < n; i++) dp[i][i] = 0;
  for (int l = 1; l <= n; l++) {
    for (int i = 0; i <= n - l; i++) {
      int j = i + l - 1;
      for (int k = i; k < j; k++) {
        int x = imos[k + 1] - imos[i];
        int y = imos[j + 1] - imos[k + 1];
        dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j] + calc(x, y));
      }
    }
  }
  cout << dp[0][n - 1] << endl;

  return 0;
}