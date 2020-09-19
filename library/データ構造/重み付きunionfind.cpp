#include<bits/stdc++.h>
using namespace std;
#define int long long
const int INF = 1LL << 31;

struct UF{
  vector<int> par;
  vector<int> depth;
  vector<int> diff;

  void init(int n){
    depth.resize(n,0);
    diff.resize(n,0);
    par.resize(n);
    for(int i = 0; i < n; i++){
      par[i] = i;
    }
  }

  //木の根を求める
  int find(int x){
    if(par[x] == x){
      return x;
    }
    else {
      int r = find(par[x]);
      diff[x] += diff[par[x]];
      return par[x] = r;
    }
  }

  int weight(int x){
    find(x); //経路圧縮
    return diff[x];
  }

  //xとyの属する集合を併合
  void unite(int x,int y,int w){
    w += weight(x) - weight(y);
    x = find(x);
    y = find(y);
    if(x == y) return;

    if(depth[x] < depth[y]) swap(x,y), w = -w;
    if(depth[x] == depth[y]) depth[x]++;
    par[y] = x;
    diff[y] = w;
  }
}uf;

signed main(){

  int n,q; cin >> n >> q;
  uf.init(n);
  vector<int> v;
  for(int i = 0; i < q; i++){
    int k,x,y,z; cin >> k;
    if(k){
      cin >> x >> y;
      if(uf.find(x) != uf.find(y)) v.push_back(INF);
      else v.push_back(uf.weight(y) - uf.weight(x));
    }
    else {
      cin >> x >> y >> z;
      uf.unite(x,y,z);
    }
  }

  for(auto p : v){
    if(p == INF) cout << '?' << endl;
    else cout << p << endl;
  }

  return 0;
}
