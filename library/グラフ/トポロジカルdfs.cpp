#include<bits/stdc++.h>
using namespace std;
#define int long long

const int N = 2e5+10;
vector<vector<int>> G(N);
bool visited[N];
vector<int> out; //トポロジカル順序

void dfs(int u){
  visited[u] = true;
  for(int v : G[u]){
    if(!visited[v]) dfs(v);
  }
  out.push_back(u);
}
void tsort(int n){
  for(int i = 1; i <= n; i++){
    if(!visited[i]) dfs(i);
  }
  reverse(out.begin(),out.end());
}

//https://atcoder.jp/contests/nikkei2019-qual/tasks/nikkei2019_qual_d
signed main(){

  int n,m; cin >> n >> m;
  for(int i = 0; i < n-1+m; i++){
    int a,b; cin >> a >> b;
    G[a].push_back(b);
  }
  tsort(n);

  vector<int> dp(n+1,0); //根からの距離
  vector<int> ans(n+1,0);
  for(int i = 0; i < n; i++){
    for(int v : G[out[i]]){
      if(dp[v] < dp[out[i]]+1){
        dp[v] = dp[out[i]]+1;
        ans[v] = out[i];
      }
    }
  }

  for(int i = 1; i <= n; i++){
    cout << ans[i] << endl;
  }

  return 0;
}
