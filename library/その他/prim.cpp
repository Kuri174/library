#include<bits/stdc++.h>
using namespace std;
#define int long long

const int INF = 1 << 60;
const int N = 2e5;

vector< vector<int> > G[N]; //辺e=(u,v)のコスト
int mincost[N]; //集合Xからの最小コスト
bool used[N]; //頂点iがXに含まれているか
int V; //頂点数

int prim(){
  fill(mincost,mincost+V,INF);
  mincost[0] = 0;
  int res = 0;

  while(1){
    int v = -1;
    for(int u = 0; u < V; u++){
      if(!used[u] && (v == -1 || mincost[u] < mincost[v])) v = u;
    }
    if(v == -1) break;

    used[v] = true;
    res += mincost[v];
    for(int u = 0; u < V; u++){
      mincost[u] = min(mincost[u],G[v][u]);
    }
  }
  return mincost;
}

signed main(){
  cin.tie(0);
  ios::sync_with_stdio(false);



  return 0;
}
