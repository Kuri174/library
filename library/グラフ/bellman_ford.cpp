#include<bits/stdc++.h>
using namespace std;
#define int long long

#ifdef _DEBUG
  #include "_DEBUG.hpp"
#endif

struct edge{ int to,cost; };
vector<int> RG[3000],can_use(3000,0);

int bellmanford(vector<edge> G[],int n,int s){
  const int INF = 1LL << 60;
  vector<int> dist(n,INF); //sからの最短距離
  dist[s] = 0;
  for(int i = 0; i < n; i++){
    for(int u = 0; u < n; u++){
      if(!can_use[u]) continue; //関係ないところでの負の経路の検出を防ぐ
      for(auto e : G[u]){
        if(dist[u] != INF && dist[e.to] > dist[u] + e.cost){
          dist[e.to] = dist[u] + e.cost;
          //n回目にも更新があるなら負の閉路が存在
          if(i == n-1){
            cout << "inf" << endl;
            return 0;
          }
        }
      }
    }
  }
  cout << -dist[n-1] << endl;
  return 0;
}

//https://atcoder.jp/contests/abc061/submissions/me
signed main(){

  int n,m; cin >> n >> m;
  vector< edge > G[n];
  for(int i = 0; i < m; i++){
    int a,b,c; cin >> a >> b >> c;
    a--,b--;
    G[a].push_back({b,-c});
    RG[b].push_back(a);
  }

  function< void(int,int) > dfs =
  [&](int u,int pre){
    if(can_use[u]) return;
    can_use[u] = 1;
    for(int v : RG[u]){
      if(v == pre) continue;
      dfs(v,u);
    }
  };
  dfs(n-1,-9);

  bellmanford(G,n,0);

  return 0;
}
