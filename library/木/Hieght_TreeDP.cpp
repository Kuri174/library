#include<bits/stdc++.h>
using namespace std;
#ifdef _DEBUG
  #include "_DEBUG.hpp"
#endif
#define int long long

struct edge{ int to,cost; };
const int N = 2e5+10;
vector<vector<edge>> G(N);
vector<int> d(N,0),dp(N);

void dfs1(int u,int pre){
  for(auto e : G[u]){
    if(e.to == pre) continue;
    dfs1(e.to,u);
    d[u] = max(d[u],d[e.to] + e.cost);
  }
}

int dfs2(int u,int pre,int d_par){
  vector< pair<int,int> > v;
  v.push_back({0,-1});
  for(auto e : G[u]){
    if(e.to == pre) v.push_back({d_par + e.cost,e.to});
    else v.push_back({e.cost + d[e.to],e.to});
  }
  sort(v.rbegin(),v.rend());

  int res = v[0].first;
  for(auto e : G[u]){
    if(e.to == pre) continue;
    bool child = (v[0].second == e.to); //e.toがuの部分木かどうか
    dfs2(e.to,u,v[child].first);
  }
  return dp[u] = res;
}

signed main(){

  int n; cin >> n;
  for(int i = 0; i < n-1; i++){
    int s,t,w; cin >> s >> t >> w;
    G[s].push_back({t,w});
    G[t].push_back({s,w});
  }

  dfs1(0,-1);
  dfs2(0,-1,0);
  int ans = 0;
  for(int i = 0; i < n; i++){
    ans = max(ans,dp[i]);
  }
  cout << ans << endl;

  return 0;
}
