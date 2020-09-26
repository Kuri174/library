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

struct range_edge_graph {
  int n;
  struct edge {
    int to;
    long long weight;
  };
  vector<vector<edge>> g;

  range_edge_graph(int n_) : n(n_) {
    g.resize(n << 2);
    for (int i = 1; i < n; ++i) {
      int c1 = i << 1 | 0, c2 = i << 1 | 1;
      g[i].push_back({c1, 0});
      g[i].push_back({c2, 0});
      g[c1 + 2 * n].push_back({i + 2 * n, 0});
      g[c2 + 2 * n].push_back({i + 2 * n, 0});
    }
    for (int i = n; i < 2 * n; ++i) g[i].push_back({i + 2 * n, 0});
  }

  // from [l1, r1) to [l2, r2)
  void add_edge(int l1, int r1, int l2, int r2, long long w) {
    int id = g.size();
    l1 += n, r1 += n;
    while (l1 < r1) {
      if (l1 & 1) g[l1 + 2 * n].push_back({id, 0}), l1++;
      if (r1 & 1) --r1, g[r1 + 2 * n].push_back({id, 0});
      l1 >>= 1, r1 >>= 1;
    }
    vector<edge> node;
    l2 += n, r2 += n;
    while (l2 < r2) {
      if (l2 & 1) node.push_back({l2++, w});
      if (r2 & 1) node.push_back({--r2, w});
      l2 >>= 1, r2 >>= 1;
    }
    g.push_back(node);
  }

  vector<long long> dijkstra(int s) {
    s += n;
    vector<long long> dist(g.size(), numeric_limits<long long>::max());
    dist[s] = 0;
    using P = pair<long long, long long>;
    priority_queue<P, vector<P>, greater<P>> que;
    que.emplace(0, s);
    while (!que.empty()) {
      P p = que.top();
      que.pop();
      int v = p.second;
      if (dist[v] < p.first) continue;
      for (edge &e : g[v]) {
        if (dist[e.to] > dist[v] + e.weight) {
          dist[e.to] = dist[v] + e.weight;
          que.emplace(dist[e.to], e.to);
        }
      }
    }
    vector<long long> res(dist.begin() + n, dist.begin() + 2 * n);
    return res;
  }
};

//参考 : https://lorent-kyopro.hatenablog.com/entry/2020/07/24/170656
// https://onlinejudge.u-aizu.ac.jp/beta/room.html#ACPC2020Day2/problems/G
signed main() {
  int n;
  cin >> n;
  vector<int> x(n), y(n);
  map<int, int> mpx, mpy;
  for (int i = 0; i < n; i++) {
    cin >> x[i] >> y[i];
    mpx[x[i]] = 1;
    mpy[y[i]] = 1;
  }

  int idx = 0;
  for (auto &p : mpx) p.second = idx++;
  for (auto &p : mpy) p.second = idx++;

  vector<int> Min(idx, inf), Max(idx, -inf);
  range_edge_graph g(idx);
  for (int i = 0; i < n; i++) {
    int nx = mpx[x[i]], ny = mpy[y[i]];
    g.add_edge(nx, nx + 1, ny, ny + 1, 0);
    g.add_edge(ny, ny + 1, nx, nx + 1, 0);
    Min[nx] = min(Min[nx], ny);
    Max[nx] = max(Max[nx], ny);
    Min[ny] = min(Min[ny], nx);
    Max[ny] = max(Max[ny], nx);
  }

  for (int i = 0; i < idx; i++) {
    g.add_edge(i, i + 1, Min[i], Max[i] + 1, 1);
    g.add_edge(Min[i], Max[i] + 1, i, i + 1, 1);
  }

  auto dp = g.dijkstra(mpx[x[0]]);
  int ans = dp[mpx[x[n - 1]]];
  if (ans > inf) ans = -1;
  cout << ans << endl;

  return 0;
}