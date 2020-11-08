#include <bits/stdc++.h>
#ifdef _DEBUG
#include "_DEBUG.hpp"
#endif
#define int long long
using namespace std;
using P = pair<int, int>;
const int inf = 2e18;
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

template <class T>
void rot90(vector<vector<T>> &cur) {
  int H = cur.size();
  int W = cur[0].size();
  vector<vector<T>> rot(W, vector<T>(H));
  for (int i = 0; i < H; i++) {
    for (int j = 0; j < W; j++) {
      rot[j][H - 1 - i] = cur[i][j];  //右回転
      // rot[W - 1 - j][i] = cur[i][j];  //左回転
    }
  }
  cur = rot;
}

// https://atcoder.jp/contests/abc182/tasks/abc182_e
signed main() {
  int h, w, n, m;
  cin >> h >> w >> n >> m;
  vector<int> a(n), b(n);
  vector<int> c(m), d(m);

  auto t = make_vec<int>(h, w);
  for (int i = 0; i < n; i++) {
    cin >> a[i] >> b[i];
    a[i]--, b[i]--;
    t[a[i]][b[i]] = 1;
  }
  for (int i = 0; i < m; i++) {
    cin >> c[i] >> d[i];
    c[i]--, d[i]--;
    t[c[i]][d[i]] = -1;
  }

  auto dp = make_vec<int>(h, w);
  for (int k = 0; k < 4; k++) {
    for (int i = 0; i < h; i++) {
      int right = 0;
      for (int j = 0; j < w; j++) {
        if (t[i][j] == 1) right = 1;
        if (t[i][j] == -1) right = 0;
        if (right && t[i][j] != -1) dp[i][j] = 1;
      }
    }
    rot90(t);
    rot90(dp);
    swap(h, w);
  }

  int ans = 0;
  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      ans += dp[i][j] == 1;
    }
  }
  cout << ans << endl;

  // for (int i = 0; i < h; i++) {
  //   for (int j = 0; j < w; j++) {
  //     cout << dp[i][j] << " ";
  //   }
  //   cout << endl;
  // }

  return 0;
}