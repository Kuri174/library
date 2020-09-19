#include<bits/stdc++.h>
using namespace std;
#ifdef LOCAL_DEBUG
  #include "LOCAL_DEBUG.hpp"
#endif
#define int long long

//https://atcoder.jp/contests/past201912-open/submissions/9780743
signed main(){

  int N; cin >> N;
  vector<int> P(N);
  vector<vector<int>> G(N);
  int s = -1;
  for(int i = 0; i < N; i++){
    cin >> P[i];
    if(P[i] == -1){
      s = i;
    }else{
      P[i]--;
      G[P[i]].push_back(i);
    }
  }

  vector<int> depth(N, 0);
  function< void(int,int,int) > dfs =
  [&](int u, int pre, int d){
    depth[u] = d;
    for(int v : G[u]){
      if(v == pre) continue;
      dfs(v, u, d+1);
    }
  };
  dfs(s, -1, 0);

  vector<vector<int>> dp(40, vector<int> (N, -1));
  for(int i = 0; i < N; i++){
    dp[0][i] = P[i];
  }
  for(int i = 0; i < 30; i++){
    for(int j = 0; j < N; j++){
      if(dp[i][j] == -1) continue;
      dp[i+1][j] = dp[i][dp[i][j]];
    }
  }

  int Q; cin >> Q;
  for(int i = 0; i < Q; i++){
    int a, b; cin >> a >> b;
    a--, b--;
    int d = depth[a] - depth[b];
    if(d < 0){
      cout << "No" << endl;
      continue;
    }
    for(int j = 30; j >= 0; j--){
      if(d >> j & 1){
        a = dp[j][a];
      }
    }
    cout << (a == b ? "Yes" : "No") << endl;
  }

  return 0;

}

// #include<bits/stdc++.h>
// using namespace std;
// #define int long long
//
// vector< vector<int> > G;
//
// struct LCA{
//   const int MAX_LOG_V = 40;
//   vector< vector<int> > parent; //[k][v]親を2^k回辿って到達する頂点v(根=-1)
//   vector<int> depth; //根から深さ
//
//   void dfs(int v,int p,int d){
//     parent[0][v] = p;
//     depth[v] = d;
//     for(int i = 0;i < G[v].size();i++){
//       if(G[v][i] != p){
//           dfs(G[v][i],v,d+1);
//       }
//     }
//   }
//
//   void init(int V){
//     parent.resize(MAX_LOG_V,vector<int> (V));
//     depth.resize(V,0);
//     //parent[0][v],depth[v]の初期化
//     dfs(0,-1,0);
//     //parent[k][v]の初期化
//     for(int k = 0; k+1 < MAX_LOG_V; k++){
//       for(int v = 0; v < V; v++){
//         if(parent[k][v] == -1) parent[k+1][v] = -1;
//         else parent[k+1][v] = parent[k][parent[k][v]];
//       }
//     }
//   }
//
//   int lca(int u,int v){
//     //uとvの深さが同じになるまで親を辿る
//     if(depth[u] > depth[v]) swap(u,v);
//     for(int k = 0; k < MAX_LOG_V; k++){
//       if((depth[v]-depth[u]) >> k & 1){
//         v = parent[k][v];
//       }
//     }
//     if(u == v) return u;
//
//     //2分探索
//     for(int k = MAX_LOG_V-1; k >= 0; k--){
//       if(parent[k][u] != parent[k][v]){
//         u = parent[k][u];
//         v = parent[k][v];
//       }
//     }
//     return parent[0][u];
//   }
//
// }lca;
//
//
// signed main(){
//   cin.tie(0);
//   ios::sync_with_stdio(false);
//
//   int n; cin >> n;
//   G.resize(n);
//   for(int i = 0; i < n-1; i++){
//     int x,y; cin >> x >> y;
//     x--,y--;
//     G[x].push_back(y);
//     G[y].push_back(x);
//   }
//   lca.init(n);
//
//   int Q; cin >> Q;
//   for(int i = 0; i < Q; i++){
//     int a,b; cin >> a >> b;
//     a--,b--;
//     cout << lca.depth[a]+lca.depth[b]-2*lca.depth[lca.lca(a,b)]+1 << endl;
//   }
//
//   return 0;
// }
