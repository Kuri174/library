#include <bits/stdc++.h>
using namespace std;
#ifdef LOCAL_DEBUG
  #include "LOCAL_DEBUG.hpp"
#endif
#define int long long
const int INF = 1LL << 60;

template <class T>
struct SegmentTree{
  using F = function<T(T, T)>;
  F f;
  T inf;
  int n;
  vector<T> node;

  SegmentTree(){}
  SegmentTree(vector<T> v, T inf, F f) : inf(inf), f(f){
    n = 1; while(n < v.size()) n *= 2;
    node.resize(2*n-1, inf);
    for(int i = 0; i < v.size(); i++) node[i+n-1] = v[i];
    for(int i = n-2; i >= 0; i--) node[i] = f(node[2*i+1], node[2*i+2]);
  }

  void update(int k, T val){
    k += n-1;
    node[k] = val;
    while(k > 0){
      k = (k-1) / 2;
      node[k] = f(node[2*k+1], node[2*k+2]);
    }
  }

  void add(int k, T val){
    k += n-1;
    node[k] += val;
    while(k > 0){
      k = (k-1) / 2;
      node[k] = f(node[2*k+1], node[2*k+2]);
    }
  }

  //区間[a, b)の値を返す
  T operator[](int x) { return get(x, x + 1); }
  T get(int a, int b){ return get(a, b, 0, 0, n); }
  T get(int a, int b, int k, int l, int r){
    if(r <= a || b <= l) return inf;
    if(a <= l && r <= b) return node[k];
    T vl = get(a, b, 2*k+1, l, (l+r)/2);
    T vr = get(a, b, 2*k+2, (l+r)/2, r);
    return f(vl, vr);
  }

  void print(int n){
    for(int i = 0; i < n; i++){
      cout << get(i, i+1) << " ";
    }
    cout << endl;
  }
};

SegmentTree<int> dp;
vector<int> es;

struct edge{ int to, cost, id; };
struct LCA{
  vector<int> vs; //dfsでの訪問順
  vector<int> dist; //根からの距離
  vector<int> id; //各頂点がvsに初めて登場するindex
  using P = pair<int,int>;
  SegmentTree<P> seg; //根からの距離が一番近いindex
  vector<vector<edge>> G;

  LCA(vector<vector<edge>> G) : G(G){
    int n = G.size(), k = 0;
    vs.resize(2*n-1); dist.resize(2*n-1); id.resize(n);
    dfs(0, -1, 0, k);
    vector<P> v;
    for(int i = 0; i < dist.size(); i++){ v.push_back(P(dist[i], i)); }
    seg = SegmentTree<P>(v, P(INF, INF),[&](P x, P y){ return min(x, y); });
  }

  //オイラー路
  void dfs(int u, int pre, int cost, int &k){
    id[u] = k;
    vs[k] = u;
    dist[k++] = cost;
    for(auto e : G[u]){
      if(e.to == pre) continue;
      dp.update(k, e.cost);
      es[e.id * 2] = k;
      dfs(e.to, u, cost + e.cost, k);
      vs[k] = u;
      es[e.id * 2 + 1] = k;
      dp.update(k, -e.cost);
      dist[k++] = cost;
      // es[e.id * 2 + 1] = k;
      // dp.update(k, -e.cost);
    }
  }

  //共通祖先
  int getnode(int u, int v){
    if(id[u] > id[v]) swap(u, v);
    return seg.get(id[u], id[v]+1).second;
  }

  //uとvの最短距離
  int getdist(int u, int v){
    return dist[id[u]] + dist[id[v]] - dist[getnode(u, v)] * 2;
  }
};

signed main(){

  int n, q, s; cin >> n >> q >> s;
  s--;
  vector<vector<edge>> g(n);
  for(int i = 0; i < n-1; i++){
    int u, v, w; cin >> u >> v >> w;
    u--, v--;
    g[u].push_back({v, w, i});
    g[v].push_back({u, w, i});
  }
  dp = SegmentTree<int>(vector<int>(n*2, 0), 0, [&](int x, int y){ return (x + y); });
  es.resize(n*2);
  LCA l(g);
  for(int i = 0; i < q; i++){
    int query, x, t; cin >> query;
    if(query == 0){
      cin >> x;
      x--;
      int p = l.getnode(s, x);
      int ans = dp.get(0, l.id[s]+1) + dp.get(0, l.id[x]+1) - dp.get(0, l.id[p]+1) * 2;
      cout << ans << endl;
      s = x;
    }else{
      cin >> x >> t;
      x--;
      dp.update(es[x * 2], t);
      dp.update(es[x * 2 + 1], -t);
    }
  }
  dp.print(n*2);

  return 0;
}
