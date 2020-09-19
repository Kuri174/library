#include<bits/stdc++.h>
using namespace std;
#ifdef LOCAL_DEBUG
  #include "LOCAL_DEBUG.hpp"
#endif
#define int long long
struct edge{ int to, cost; };

//http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1595
signed main(){

  int n; cin >> n;
  vector<vector<edge>> G(n);
  for(int i = 0; i < n-1; i++){
    int a, b; cin >> a >> b;
    a--, b--;
    G[a].push_back({b, 1});
    G[b].push_back({a, 1});
  }

  vector<int> dist(n, 0);
  auto dfs = [&](auto&& dfs, int u, int par)->void{
    for(edge e : G[u]){
      if(e.to == par) continue;
      dfs(dfs, e.to, u);
      dist[u] = max(dist[u], dist[e.to] + e.cost);
    }
  };
  dfs(dfs, 0, -1);

  vector<int> dp(n, 0); //頂点iから最も遠い点までの距離
  auto dfs2 = [&](auto&& dfs2, int u, int par, int d_par)->void{
    vector<pair<int, int>> v;
    v.push_back({0, -1});
    for(edge e : G[u]){
      v.push_back({(e.to == par ? d_par : dist[e.to]) + e.cost, e.to});
    }
    sort(v.rbegin(), v.rend());
    dp[u] = v[0].first;

    for(edge e : G[u]){
      if(e.to == par) continue;
      d_par = (e.to == v[0].second ? v[1].first : v[0].first);
      dfs2(dfs2, e.to, u, d_par);
    }
  };
  dfs2(dfs2, 0, -1, 0);

  for(int i = 0; i < n; i++){
    cout << 2 * (n - 1) - dp[i] << endl;
  }

  return 0;
}
