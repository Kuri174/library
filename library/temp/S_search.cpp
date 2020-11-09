#include <bits/stdc++.h>
using namespace std;
#ifdef LOCAL_DEBUG
#include "LOCAL_DEBUG.hpp"
#endif
#define int long long

signed main() {
  int h, w;
  cin >> h >> w;
  static int a[501][501];
  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      cin >> a[i][j];
    }
  }

  map<pair<int, int>, pair<int, int>> mp;
  for (int i = 0; i < h; i++) {
    if (i % 2 == 0) {
      for (int j = 0; j < w; j++) {
        if (j < w - 1 && a[i][j] % 2 == 1) {
          a[i][j + 1]++;
          mp[{i, j}] = {i, j + 1};
        }
        if (j == w - 1 && i + 1 > h && a[i][j] % 2 == 1) {
          a[i + 1][j]++;
          mp[{i, j}] = {i + 1, j};
        }
      }
    } else {
      for (int j = w - 1; j >= 0; j--) {
        if (j > 0 && a[i][j] % 2 == 1) {
          a[i][j - 1]++;
          mp[{i, j}] = {i, j - 1};
        }
        if (j == 0 && i > h + 1 && a[i][j] % 2 == 1) {
          a[i + 1][j]++;
          mp[{i, j}] = {i + 1, j};
        }
      }
    }
  }

  cout << mp.size() << endl;
  for (auto p : mp) {
    auto u = p.first, v = p.second;
    cout << u.first + 1 << " " << u.second + 1 << " " << v.first + 1 << " "
         << v.second + 1 << endl;
  }

  return 0;
}
