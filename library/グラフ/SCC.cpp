#include<bits/stdc++.h>
using namespace std;
#ifdef LOCAL_DEBUG
  #include "LOCAL_DEBUG.hpp"
#endif
#define int long long

struct SCC{
  vector< vector<int> > G; //グラフの隣接リスト
  vector< vector<int> > rG; //辺の向きを逆にしたグラフ
  vector<int> vs; //帰りがけ順の並び
  vector<bool> visited; //既に調べたか
  vector<int> cmp; //トポロジカル順序 値が等しければ強連結成分

  void init(int _V){
    int V = _V;
    G.resize(V);
    rG.resize(V);
    visited.resize(V);
    cmp.resize(V);
  }

  void dfs(int v){
    visited[v] = true;
    for(int i = 0; i < G[v].size(); i++){
      if(!visited[G[v][i]]) dfs(G[v][i]);
    }
    vs.push_back(v);
  }

  void rdfs(int v,int k){
    visited[v] = true;
    cmp[v] = k;
    for(int i = 0; i < rG[v].size(); i++){
      if(!visited[rG[v][i]]) rdfs(rG[v][i],k);
    }
  }

  int scc(int V){
    fill(visited.begin(),visited.begin()+V,false);
    for(int v = 0; v < V; v++){
      if(!visited[v]) dfs(v);
    }

    fill(visited.begin(),visited.begin()+V,false);
    int k = 0;
    for(int i = vs.size()-1; i >= 0; i--){
      if(!visited[vs[i]]) rdfs(vs[i],k++);
    }
    return k;
  }

}scc;

signed main(){

  //強連結成分分解
  int V,E; cin >> V >> E;
  scc.init(V);
  for(int i = 0; i < E; i++){
    int s,t; cin >> s >> t;
    scc.G[s].push_back(t);
    scc.rG[t].push_back(s);
  }
  scc.scc(V);

  int Q; cin >> Q;
  for(int i = 0; i < Q; i++){
    int u,v; cin >> u >> v;
    if(scc.cmp[u] == scc.cmp[v]) cout << 1 << endl;
    else cout << 0 << endl;
  }

  return 0;
}
