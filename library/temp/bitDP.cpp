#include <bits/stdc++.h>
using namespace std;
#ifdef _DEBUG
  #include "_DEBUG.hpp"
#endif
#define int long long
const int INF = 1LL << 60;

template<class T> vector<T> make_vec(size_t a) { return vector<T>(a); }
template<class T, class... Ts> auto make_vec(size_t a, Ts... ts) {
  return vector<decltype(make_vec<T>(ts...))>(a, make_vec<T>(ts...));
}
template<class T, class V>
typename enable_if<is_class<T>::value == 0>::type fill(T &t, const V &v) {
    t = v;
}
template<class T, class V>
typename enable_if<is_class<T>::value != 0>::type fill(T &t, const V &v) {
    for (auto &e : t) fill(e, v);
}
// auto v = make_vec<int>(h, w);
// fill(v, 0);

struct edge{ int to, cost; };
vector<int> dikstra(vector<vector<edge>> G, int s){
  using P = pair<int, int>;
  priority_queue<P,vector<P>,greater<P>> q;
  vector<int> d(G.size(), 1LL << 60); //sからの最短距離
  d[s] = 0;
  q.push({0,s}); //{最短距離,頂点}

  while(!q.empty()){
    auto p = q.top(); q.pop();
    int v = p.second;
    if(d[v] < p.first) continue;
    for(auto e : G[v]){
      if(d[e.to] > d[v] + e.cost){
        d[e.to] = d[v] + e.cost;
        q.push(P(d[e.to], e.to));
      }
    }
  }
  return d;
}

signed main(){

  int n, m; cin >> n >> m;
  vector<vector<edge>> g(n);
  for(int i = 0; i < m; i++){
    int u, v; cin >> u >> v;
    u--, v--;
    g[u].push_back({v, 1});
    g[v].push_back({u, 1});
  }

  int s, k; cin >> s >> k;
  s--;
  vector<int> t(k);
  for(int i = 0; i < k; i++){
    cin >> t[i];
    t[i]--;
  }
  vector<vector<int>> es(k, vector<int>(n));
  for(int i = 0; i < k; i++){
    es[i] = dikstra(g, t[i]);
  }

  auto dp = make_vec<int>(1 << k, k);
  auto dfs = [&](auto&& dfs, int S, int u)->int{
    if(dp[S][u] != -1) return dp[S][u];
    if(S == (1 << k) - 1) return dp[S][u] = 0;

    int res = INF;
    for(int v = 0; v < k; v++){
      if(!(S >> v & 1)){
        res = min(res, dfs(dfs, S | (1 << v), v) + es[u][t[v]]);
      }
    }
    return dp[S][u] = res;
  };

  int ans = INF;
  for(int i = 0; i < k; i++){
    fill(dp, -1);
    ans = min(ans, dfs(dfs, 1 << i, i)) + es[i][s];
  }
  cout << ans << endl;
  return 0;
}