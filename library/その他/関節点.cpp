#include<bits/stdc++.h>
using namespace std;
#define int long long

const int N = 1e5+10;
vector<int> G[N];
bool visited[N];
int prenum[N],parent[N],lowest[N],timer;

void dfs(int cur,int prev){
  prenum[cur] = lowest[cur] = timer;
  timer++;
  visited[cur] = 1;

  for(int i = 0; i < G[cur].size(); i++){
    int next = G[cur][i];
    if(!visited[next]){
      //curからnextへ訪問する直前の処理
      parent[next] = cur;

      dfs(next,cur);
      //nextの探索が終了した直後の処理
      lowest[cur] = min(lowest[cur],lowest[next]);
    }
    else if(next != prev){
      //辺cur->nextがback-edgeの場合の処理
      lowest[cur] = min(lowest[cur],prenum[next]);
    }
  }
}

void art_points(){
  dfs(0,-1);

  set<int > ap;
  int np = 0;
  for(int i = 1; i < N; i++){
    int p = parent[i];
    if(p == 0) np++;
    else if(prenum[p] <= lowest[i]) ap.insert(p);
  }
  if(np > 1) ap.insert(0);
  for(auto p : ap) cout << p << endl;
}

signed main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int V,E; cin >> V >> E;
  for(int i = 0; i < E; i++){
    int s,t; cin >> s >> t;
    G[s].push_back(t);
    G[t].push_back(s);
  }
  art_points();

  return 0;
}
