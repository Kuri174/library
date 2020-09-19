#include <bits/stdc++.h>
using namespace std;
#ifdef _DEBUG
  #include "_DEBUG.hpp"
#endif
#define int long long
const int INF = 1LL << 60;

string ans[3] = {"pairwise coprime", "setwise coprime", "not coprime"};

//https://atcoder.jp/contests/abc177/editorial/82
signed main(){

  int n; cin >> n;
  vector<int> a(n);
  for(int i = 0; i < n; i++){
    cin >> a[i];
  }

  vector<int> d(1e6 + 1, -1);
  d[1] = 1;
  for(int i = 2; i <= 1e6; i++){
    if(d[i] != -1) continue;
    for(int j = i; j <= 1e6; j+=i){
      if(d[j] == -1) d[j] = i;
    }
  }

  bool judge = true;
  set<int> visited;
  for(int i = 0; i < n; i++){
    int t = a[i];
    set<int> st;
    while(t != 1){
      st.insert(d[t]);
      t /= d[t];
    }
    for(int p : st){
      if(visited.find(p) != visited.end()) judge = false;
      visited.insert(p);
    }
  }

  if(judge){
    cout << ans[0] << endl;
    return 0;
  }

  int val = a[0];
  for(int i = 0; i < n; i++){
    val = __gcd(val, a[i]);
  }
  cout << (val == 1 ? ans[1] : ans[2]) << endl;

  return 0;
}
