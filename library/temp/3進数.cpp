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

int enc(string s) {
  int res = 0;
  for (int i = 0; i < s.size(); i++) {
    res = res * 3 + (s[i] - '1');
  }
  return res;
}

// https://onlinejudge.u-aizu.ac.jp/services/room.html#HUPC2020Day3/problems/M
signed main() {
  int q, m;
  cin >> q >> m;
  vector<string> s(q);
  cin >> s;

  vector<bool> dp(pow(3, m), false);

  auto dfs = [&](auto &&dfs, string s) -> void {
    if (dp[enc(s)]) return;
    dp[enc(s)] = true;
    for (int i = 0; i < m; i++) {
      if (s[i] == '1') continue;
      s[i]--;
      dfs(dfs, s);
      s[i]++;
    }
  };

  for (int i = 0; i < q; i++) {
    if (dp[enc(s[i])]) {
      cout << "1";
    } else {
      cout << "0";
      for (int j = 0; j < m; j++) {
        if (s[i][j] == '1') continue;
        s[i][j]--;
        dfs(dfs, s[i]);
        s[i][j]++;
      }
    }
  }
  cout << endl;

  return 0;
}