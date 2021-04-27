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

// {a, {b, c}} : a = gcd(p, q) = bp + cq
pair<int, pair<int, int>> ext_gcd(int p, int q) {
  if (q == 0) return {p, {1, 0}};
  auto r = ext_gcd(q, p % q);
  return {r.first, {r.second.second, r.second.first - p / q * r.second.second}};
}

/* 中国剰余定理 */
// a, b, p, q が与えられるので、
// X mod p ≡ q
// X mod a ≡ b
// を満たすX mod Y = gcd(q, b)を求める
// CRT(q, p, b, a) = {r, m} mは周期
pair<int, int> CRT(int a1, int m1, int a2, int m2) {
  auto eg = ext_gcd(m1, m2);
  int d = eg.first;
  if ((a2 - a1) % d) return {0, -1};
  int m = m1 / d * m2;
  int r =
      ((a1 + m1 * ((__int128_t)(a2 - a1) / d * eg.second.first % (m2 / d))) %
           m +
       m) %
      m;
  return {r, m};
}

// https://atcoder.jp/contests/abc193/tasks/abc193_e
signed main() {
  int t;
  cin >> t;
  while (t--) {
    int x, y, p, q;
    cin >> x >> y >> p >> q;

    int ans = inf;
    for (int i = x; i < x + y; i++) {
      for (int j = p; j < p + q; j++) {
        auto res = CRT(i, (x + y) * 2, j, p + q);
        if (res.second != -1) ans = min(ans, res.first);
      }
    }
    if (ans == inf) {
      cout << "infinity" << endl;
    } else {
      cout << ans << endl;
    }
  }

  return 0;
}