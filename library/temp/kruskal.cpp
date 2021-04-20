#include <bits/stdc++.h>
using namespace std;
#ifdef _DEBUG
#include "_DEBUG.hpp"
#endif
#define int long long

struct UnionFind {
  vector<int> par;   //親
  vector<int> size;  //集合の大きさ

  UnionFind(int n) {
    par.resize(n);
    size.resize(n, 1);
    for (int i = 0; i < n; i++) {
      par[i] = i;
    }
  }

  //木の根を求める
  int root(int x) {
    if (par[x] == x) {
      return x;
    } else {
      return par[x] = root(par[x]);
    }
  }

  // xとyの属する集合を併合
  void unite(int x, int y) {
    x = root(x), y = root(y);
    if (x == y) return;
    if (size[x] < size[y]) swap(x, y);
    par[y] = x;
    size[x] += size[y];
  }

  bool same(int x, int y) { return root(x) == root(y); }
};

struct edge {
  int from, to, cost;
};

// https://atcoder.jp/contests/joisc2010/submissions/12444341
signed main() {
  int n, m, k;
  cin >> n >> m >> k;
  vector<edge> g(m);
  for (int i = 0; i < m; i++) {
    int u, v, c;
    cin >> u >> v >> c;
    u--, v--;
    g[i] = edge{u, v, c};
  }

  sort(g.begin(), g.end(), [](edge x, edge y) { return x.cost < y.cost; });
  UnionFind uf(n);
  int ans = 0, cnt = 0;
  for (int i = 0; i < m; i++) {
    if (n - cnt <= k) break;
    int u = g[i].from, v = g[i].to, c = g[i].cost;
    if (uf.same(u, v)) continue;
    ans += c;
    uf.unite(u, v);
    cnt++;
  }
  cout << ans << endl;

  return 0;
}