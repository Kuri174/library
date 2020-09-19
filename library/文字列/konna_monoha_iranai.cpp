#include<bits/stdc++.h>
using namespace std;
#define int long long

const int B = 1e9+7, H = 1e9+9;
//Hash(C) = (C1*B^(n-1)+...+Cn*B^0) mod H
//aはbに含まれているか
int contain(string a,string b){
  if(a.size() > b.size()) return false;

  int t = 1,ah = 0,bh = 0;
  for(int i = 0; i < a.size(); i++) ah = ah*B + a[i],t *= B;
  for(int i = 0; i < a.size(); i++) bh = bh*B + b[i];

  int cnt = 0;
  for(int i = a.size(); i <= b.size(); i++){
    if(ah == bh) cnt++;
    if(i >= b.size()) break;
    bh = bh*B + b[i] - b[i-a.size()]*t;
  }
  return cnt;
}

signed main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  string s; cin >> s;
  int m; cin >> m;
  int ans = 0;
  for(int i = 0; i < m; i++){
    string c; cin >> c;
    ans += contain(c,s);
  }
  cout << ans << endl;

  return 0;
}
