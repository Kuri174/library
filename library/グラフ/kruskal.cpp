#include<bits/stdc++.h>
using namespace std;
#define int long long

struct edge{ int u,v,cost; };
bool comp(const edge& e1,const edge& e2){
  return e1.cost < e2.cost;
}

vector<edge> es;
int V,E; //頂点数、辺数

struct UF{
  vector<int> par; //親
  vector<int> size; //集合の大きさ

  void init(int n){
    par.resize(n);
    size.resize(n);
    for(int i = 0; i < n; i++){
      par[i] = i;
      size[i] = 1;
    }
  }

  //木の根を求める
  int root(int x){
    if(par[x] == x){
      return x;
    }
    else {
      return par[x] = root(par[x]);
    }
  }

  //xとyの属する集合を併合
  void unite(int x,int y){
    x = root(x);
    y = root(y);
    if(x == y) return;

    if(size[x] < size[y]) swap(x,y);
    par[y] = x;
    size[x] += size[y];
  }
}uf;

int kruskal(){
  sort(es.begin(),es.end(),comp);
  uf.init(V);
  int total = 0;
  for(int i = 0; i < es.size(); i++){
    edge e = es[i];
    if(uf.root(e.u) != uf.root(e.v)){
      total += e.cost;
      uf.unite(e.u,e.v);
    }
  }
  return total;
}

signed main(){

  cin >> V;
  for(int i = 0; i < V; i++){
    for(int j = 0; j < V; j++){
      int cost; cin >> cost;
      es.push_back({i, j, cost});
    }
  }
  cout << kruskal() << endl;

  return 0;
}
