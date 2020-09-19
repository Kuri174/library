#include<bits/stdc++.h>
using namespace std;
#define int long long

struct MaxFlow{
  struct edge{ int to,cap,rev; }; //{行先,容量,逆辺}
  vector< vector<edge> > G; //隣接リスト
  vector<bool> visited; //dfsで既に調べたかのフラグ

  void init(int n){
    G.resize(n);
    visited.resize(n);
  }

  void add_edge(int from,int to,int cap){
    G[from].push_back({to,cap,(int)G[to].size()});
    G[to].push_back({from,0,(int)G[from].size()-1});
  }

  //増加パスを探す
  int dfs(int v,int t,int f){
    if(v == t) return f;
    visited[v] = true;
    for(auto &e : G[v]){
      if(!visited[e.to] && e.cap > 0){
        int d = dfs(e.to,t,min(f,e.cap));
        if(d > 0){
          e.cap -= d;
          G[e.to][e.rev].cap += d;
          return d;
        }
      }
    }
    return 0;
  }

  //sからtへの最大流を求める
  int maxflow(int s,int t){
    int flow = 0;
    for(;;){
      fill(visited.begin(),visited.end(),false);
      int f = dfs(s,t,1LL<<60);
      if(f == 0) return flow;
      flow += f;
    }
  }

}flow;

signed main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int V,E; cin >> V >> E;
  flow.init(V+1);
  for(int i = 0; i < E; i++){
    int u,v,c; cin >> u >> v >> c;
    flow.add_edge(u,v,c);
  }
  cout << flow.maxflow(0,V-1) << endl;

  return 0;
}
