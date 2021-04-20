#include <bits/stdc++.h>
using namespace std;
#ifdef _DEBUG
#include "_DEBUG.hpp"
#endif
#define int long long
const int INF = 1LL << 60;

int table[200][200];

signed main() {
  int H, W;
  cin >> H >> W;
  for (int i = 0; i < H; i++) {
    for (int j = 0; j < W; j++) {
      cin >> table[i][j];
    }
  }

  static int c[200][200];
  for (int i = 0; i < H; i++) {
    for (int j = 0; j < W; j++) {
      c[i][j] += ((i + j) % 2 == 0 ? table[i][j] : -table[i][j]);
    }
  }
  for (int i = 0; i < H; i++) {
    for (int j = 0; j < W; j++) {
      if (j - 1 >= 0) c[i][j] += c[i][j - 1];
    }
  }
  for (int i = 0; i < W; i++) {
    for (int j = 0; j < H; j++) {
      if (j - 1 >= 0) c[j][i] += c[j - 1][i];
    }
  }

  int ans = 0;
  for (int i = 0; i < H; i++) {
    for (int j = 0; j < W; j++) {
      for (int k = i; k < H; k++) {
        for (int l = j; l < W; l++) {
          int res = c[k][l];
          if (j - 1 >= 0) res -= c[k][j - 1];
          if (i - 1 >= 0) res -= c[i - 1][l];
          if (j - 1 >= 0 && i - 1 >= 0) res += c[i - 1][j - 1];
          if (res == 0) ans = max(ans, (k - i + 1) * (l - j + 1));
        }
      }
    }
  }
  cout << ans << endl;

  return 0;
}
