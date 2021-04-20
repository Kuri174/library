#include <bits/stdc++.h>
using namespace std;
#ifdef _DEBUG
  #include "_DEBUG.hpp"
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
    for(int i = 0; i < dist.size(); i++){ v.emplace_back(dist[i], euler[i]); }
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

template <class M, class OM = M>
struct DelaySegmentTree{
  using FX = function<M(M, M)>;
  using FA = function<M(M, OM)>;
  using FM = function<OM(OM, OM)>;
  using FP = function<M(M, int)>;
  FX fx;
  FA fa;
  FM fm;
  FP fp;
  int n;
  M ex;
  OM em;
  vector<M> data;
  vector<OM> delay;

  DelaySegmentTree(int sz, FX fx, FA fa, FM fm, FP fp, M ex, OM em) 
  : fx(fx), fa(fa), fm(fm), fp(fp), ex(ex), em(em), data(sz*4, ex), delay(sz*4, em){
    n = 1; while(n < sz) n *= 2;
  }

  void build(vector<M> v){
    for(int k = 0; k < v.size(); k++){
      data[k+n-1] = v[k];
    }
    for(int k = n-2; k >= 0; k--){
      data[k] = fx(data[2*k+1], data[2*k+2]);
    }
  }

  void eval(int k, int len){
    if(delay[k] == em) return;
    if(k < n-1){
      delay[2*k+1] = fm(delay[2*k+1], delay[k]);
      delay[2*k+2] = fm(delay[2*k+2], delay[k]);
    }
    data[k] = fa(data[k], fp(delay[k], len));
    delay[k] = em;
  }

  void update(int a, int b, OM x){ update(a, b, x, 0, 0, n); }
  void update(int a, int b, OM x, int k, int l, int r){
    eval(k, r - l);
    if(b <= l || r <= a) return;
    if(a <= l && r <= b){
      delay[k] = fm(delay[k], x);
      eval(k, r - l);
    }else{
      update(a, b, x, 2*k+1, l, (l+r)/2);
      update(a, b, x, 2*k+2, (l+r)/2, r);
      data[k] = fx(data[2*k+1], data[2*k+2]);
    }
  }

  M getval(int a, int b){ return getval(a, b, 0, 0, n); }
  M getval(int a, int b, int k, int l, int r){
    eval(k, r - l);
    if(b <= l || r <= a) return ex;
    if(a <= l && r <= b) return data[k];
    M vl = getval(a, b, 2*k+1, l, (l+r)/2);
    M vr = getval(a, b, 2*k+2, (l+r)/2, r);
    return fx(vl, vr);
  }

  void print(int n){
    cout << "[";
    for(int i = 0; i < n; i++){
      cout << getval(i, i+1) << ", ";
    }
    cout << "]" << endl;
  }
};


//http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2871&lang=jp
signed main(){

  int n, q; cin >> n >> q;
  vector<vector<edge>> g(n);
  for(int i = 1; i < n; i++){
    int p; cin >> p;
    p--;
    g[p].push_back({i, 1});
  }
  vector<char> c(n);
  for(int i = 0; i < n; i++){
    cin >> c[i];
  }

  LCA l(g);
  int k = 0;
  vector<int> v(n*2-1, 0);
  auto dfs = [&](auto&& dfs, int u, int par)->void{
    v[k++] = (c[u] == 'G' ? 1 : -1);
    for(edge e : g[u]){
      if(e.to == par) continue;
      dfs(dfs, e.to, u);
      k++;
    }
  };
  dfs(dfs, 0, -1);
  
  auto fx = [](int a, int b){ return a + b; };
  auto fa = [](int a, int b){ return a * b; };
  auto fm = [](int a, int b){ return a * b; };
  auto fp = [](int a, int b){ return a; };
  DelaySegmentTree<int> seg(v.size(), fx, fa, fm, fp, 0, 1);
  seg.build(v);

  for(int i = 0; i < q; i++){
   int v; cin >> v;
   v--;
   seg.update(l.left[v], l.right[v]+1, -1);
   cout << (seg.getval(0, 2*n) > 0 ? "broccoli" : "cauliflower") << endl;
   //seg.print(n*2);
 }

  return 0;
}