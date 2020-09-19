#include<bits/stdc++.h>
using namespace std;
#ifdef LOCAL_DEBUG
  #include "LOCAL_DEBUG.hpp"
#endif
#define int long long

vector<int> tsort(vector<vector<int>> G){

  int n = G.size();
  vector<int> sorted,indeg(n,0); //入次数
  for(int u = 0; u < n; u++){
    for(int v : G[u]){
      indeg[v]++;
    }
  }

  priority_queue<int,vector<int>,greater<int>> q; //最小値
  for(int u = 0; u < n; u++){
    if(indeg[u] == 0) q.push(u);
  }
  while(!q.empty()){
    int u = q.top(); q.pop();
    for(int v : G[u]){
      indeg[v]--;
      if(indeg[v] == 0) q.push(v);
    }
    sorted.push_back(u);
  }
  return sorted;
}

signed main(){

  int n,m; cin >> n >> m;
  vector<vector<int>> G(n);
  for(int i = 0; i < n-1+m; i++){
    int a,b; cin >> a >> b;
    a--,b--;
    G[a].push_back(b);
  }

  auto v = tsort(G);
  vector<int> dp(n,-1),pre(n,-1); //根からの距離,先祖
  for(int i = 0; i < n; i++){
    for(int j : G[v[i]]){
      if(dp[j] < dp[v[i]]+1)
      dp[j] = dp[v[i]]+1;
      pre[j] = v[i];
    }
  }

  for(int i = 0; i < n; i++){
    cout << pre[i]+1 << endl;
  }

  return 0;
}
