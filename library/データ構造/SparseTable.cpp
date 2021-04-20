#include <bits/stdc++.h>
using namespace std;
#ifdef _DEBUG
#include "_DEBUG.hpp"
#endif
#define int long long

template <class T>
struct SparseTable {
  vector<vector<T>> dat;
  vector<int> height;

  SparseTable(){};
  SparseTable(vector<T> v) {
    int n = v.size(), h = 0;
    while ((1 << h) < n) h++;
    dat.assign(h, vector<T>(1 << h));
    height.assign(n + 1, 0);
    for (int i = 2; i <= n; i++) height[i] = height[i >> 1] + 1;
    for (int i = 0; i < n; i++) dat[0][i] = v[i];
    for (int i = 1; i < h; i++) {
      for (int j = 0; j < n; j++) {
        dat[i][j] = min(dat[i - 1][j], dat[i - 1][min(j + (1 << (i - 1)), n - 1)]);
      }
    }
  }
  T getval(int a, int b) {
    return min(dat[height[b - a]][a], dat[height[b - a]][b - (1 << height[b - a])]);
  }
};

signed main() { return 0; }
