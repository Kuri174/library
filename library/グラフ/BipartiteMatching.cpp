#include<bits/stdc++.h>
using namespace std;
#ifdef _DEBUG
  #include "_DEBUG.hpp"
#endif
#define int long long

struct BipartiteMatching {
  vector< vector< int > > graph;
  vector< int > match, alive, used;
  int timestamp;

  BipartiteMatching(int n) : graph(n), alive(n, 1), used(n, 0), match(n, -1), timestamp(0) {}

  void add_edge(int u, int v) {
    graph[u].push_back(v);
    graph[v].push_back(u);
  }

  bool dfs(int idx) {
    used[idx] = timestamp;
    for(auto &to : graph[idx]) {
      int to_match = match[to];
      if(alive[to] == 0) continue;
      if(to_match == -1 || (used[to_match] != timestamp && dfs(to_match))) {
        match[idx] = to;
        match[to] = idx;
        return true;
      }
    }
    return false;
  }

  int bipartite_matching() {
    int ret = 0;
    for(int i = 0; i < graph.size(); i++) {
      if(alive[i] == 0) continue;
      if(match[i] == -1) {
        ++timestamp;
        ret += dfs(i);
      }
    }
    return ret;
  }

  void output() {
    for(int i = 0; i < graph.size(); i++) {
      if(i < match[i]) {
        cout << i << "-" << match[i] << endl;
      }
    }
  }
};

//https://atcoder.jp/contests/soundhound2018/tasks/soundhound2018_c
signed main(){

  int H, W; cin >> H >> W;
  vector<string> C(H);
  for(int i = 0; i < H; i++){
    cin >> C[i];
  }

  BipartiteMatching bm(H * W);
  int cnt = 0;
  for(int i = 0; i < H; i++){
    for(int j = 0; j < W; j++){
      if(j + 1 < W){
        if(C[i][j] == '.' && C[i][j+1] == '.'){
          bm.add_edge(i * W + j, i * W + j + 1);
        }
      }
      if(i + 1 < H){
        if(C[i][j] == '.' && C[i+1][j] == '.'){
          bm.add_edge(i * W + j, i * W + j + W);
        }
      }
      if(C[i][j] == '.') cnt++;
    }
  }
  int ans = cnt - bm.bipartite_matching();
  cout << ans << endl;

  return 0;
}
