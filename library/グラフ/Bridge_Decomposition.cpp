#include<bits/stdc++.h>
using namespace std;
#ifdef _DEBUG
  #include "_DEBUG.hpp"
#endif
#define int long long

struct edge{ int to,cost; };
struct Bridge_Decomposition{
  vector<vector<edge>> G,Tree,NewTree; //グラフ, グラフ->木(後退辺を消す), 木->色をまとめた木
  vector<int> dp,depth,cmp; //葉から根までの累積和, 木の深さ, 色(同じ色で強連結)
  vector<pair<int,int>> bridge; //橋
  int color = 1;

  Bridge_Decomposition(vector<vector<edge>> G):G(G){
    int n = G.size();
    Tree.resize(n); NewTree.resize(n);
    dp.resize(n,0); depth.resize(n,-1); cmp.resize(n,0);
    dfs(0,-1,0); //木の構築
    dfs2(0,-1); //累積和
    dfs3(0,-1); //色塗り
    dfs4(0,-1); //同じ色をまとめた木にする, 橋の列挙, //関節点の列挙
  }

  void dfs(int u,int pre,int d){
    depth[u] = d;
    for(edge e : G[u]){
      if(e.to == pre) continue;
      if(depth[e.to] == -1){
        dfs(e.to,u,d+1);
        Tree[u].push_back(e);
        Tree[e.to].push_back({u,e.cost});
      }else {
        if(depth[e.to] < depth[u]){
          dp[u]++;
          dp[e.to]--;
        }
      }
    }
    return;
  }

  void dfs2(int u,int pre){
    for(edge e : Tree[u]){
      if(e.to == pre) continue;
      dfs2(e.to,u);
      dp[u] += dp[e.to];
    }
    return;
  }

  void dfs3(int u,int pre){
    for(edge e : Tree[u]){
      if(e.to == pre) continue;
      if(dp[e.to] == 0){
        cmp[e.to] = color++;
      }else {
        cmp[e.to] = cmp[u];
      }
      dfs3(e.to,u);
    }
    return;
  }

  void dfs4(int u,int pre){
    for(edge e : Tree[u]){
      if(e.to == pre) continue;
      int x = cmp[u], y = cmp[e.to];
      if(x != y){
        NewTree[x].push_back({y,e.cost});
        NewTree[y].push_back({x,e.cost});
        bridge.push_back(minmax(u,e.to));
      }
      dfs4(e.to,u);
    }
    return;
  }
};

signed main(){

  int n,m; cin >> n >> m;
  vector<vector<edge>> G(n);
  for(int i = 0; i < m; i++){
    int x,y; cin >> x >> y;
    G[x].push_back({y,1});
    G[y].push_back({x,1});
  }

  Bridge_Decomposition bd(G);
  sort(bd.bridge.begin(),bd.bridge.end());
  for(auto p : bd.bridge){
    cout << p.first << " " << p.second << endl;
  }

  return 0;
}
