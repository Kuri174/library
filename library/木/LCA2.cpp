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

struct edge{ int to, cost; };
struct LCA{
  vector<int> euler; //オイラー路の訪問順
  vector<int> dist; //根からの距離
  vector<int> left; //初めて頂点iに訪れたk
  vector<int> right; //最後に頂点iに訪れたk
  using P = pair<int, int>;
  SegmentTree<P> seg; //{根からの距離, k}
  vector<vector<edge>> g;

  LCA(vector<vector<edge>> g, int s = 0) : g(g){
    int n = g.size(), k = 0;
    euler.resize(2*n-1); dist.resize(2*n-1); left.resize(n), right.resize(n);
    dfs(s, -1, 0, k);
    vector<P> v;
    for(int i = 0; i < dist.size(); i++){ v.emplace_back(dist[i], i); }
    seg = SegmentTree<P>(v, P(INF, INF), [&](P x, P y){ return min(x, y); });
  }

  //オイラー路
  void dfs(int u, int par, int cost, int &k){
    left[u] = right[u] = k;
    euler[k] = u;
    dist[k++] = cost;
    for(auto e : g[u]){
      if(e.to == par) continue;
      dfs(e.to, u, cost + e.cost, k);
      right[u] = k;
      euler[k] = u;
      dist[k++] = cost;
    }
  }

  //共通祖先
  int getnode(int u, int v){
    if(left[u] > left[v]) swap(u, v);
    return seg.get(left[u], left[v]+1).second;
  }

  //uとvの最短距離
  int getdist(int u, int v){
    return dist[left[u]] + dist[left[v]] - dist[getnode(u, v)] * 2;
  }
};

//https://atcoder.jp/contests/past201912-open/tasks/past201912_k
signed main(){

  int n; cin >> n;
  vector<int> p(n);
  vector<vector<edge>> g(n);
  int s = -1;
  for(int i = 0; i < n; i++){
    cin >> p[i];
    if(p[i] != -1) g[p[i]-1].push_back({i, 1});
    if(p[i] == -1) s = i;
  }
  LCA l(g, s);

  int q; cin >> q;
  for(int i = 0; i < q; i++){
    int a, b; cin >> a >> b;
    a--, b--;
    if(l.left[b] < l.left[a] && l.left[a] < l.right[b]){
      cout << "Yes" << endl;
    }else{
      cout << "No" << endl;
    }
  }

  return 0;
}