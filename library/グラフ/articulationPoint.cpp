#include<bits/stdc++.h>
using namespace std;
#ifdef _DEBUG
  #include "_DEBUG.hpp"
#endif
#define int long long

struct edge{ int to,cost; };
std::vector<int> articulationPoint(const vector<vector<edge>> &g) {
    int n = g.size(), idx;
    std::vector<int> low(n), ord(n), art;
    std::function<void(int)> dfs = [&](int v) {
        low[v] = ord[v] = ++idx;
        for (auto& e : g[v]) {
            int w = e.to;
            if (ord[w] == 0) {
                dfs(w);
                low[v] = std::min(low[v], low[w]);
                if ((ord[v] == 1 && ord[w] != 2) || (ord[v] != 1 && low[w] >= ord[v]))
                    art.push_back(v);
            } else
                low[v] = std::min(low[v], ord[w]);
        }
    };
    for (int u = 0; u < n; u++)
        if (ord[u] == 0) {
            idx = 0;
            dfs(u);
        }
    sort(art.begin(), art.end());
    art.erase(unique(art.begin(), art.end()), art.end());
    return art;
}
signed main(){

  int n,m; cin >> n >> m;
  vector<vector<edge>> G(n);
  for(int i = 0; i < m; i++){
    int x,y; cin >> x >> y;
    G[x].push_back({y,1});
    G[y].push_back({x,1});
  }

  auto ans = articulationPoint(G);
  for(int p : ans){
    cout << p << endl;
  }

  return 0;
}
