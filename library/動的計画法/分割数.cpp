#include<bits/stdc++.h>
using namespace std;
#define int long long

#ifdef LOCAL_DEBUG
  #include "LOCAL_DEBUG.hpp"
#endif

const int MOD = 1e9+7;

//http://incognita.hatenablog.com/entry/20110305/1299344781
int PartNum(int n,int m,int k){ //nがm以下の自然数の和 k個で構成される分割数
  vector<vector<int>> dp(n+1,vector<int> (m+1,0)); //iをj以下の自然数の和に分ける場合の数
  dp[0][0] = 1;
  for(int i = 0; i <= n; i++){
    for(int j = 1; j <= m; j++){
      if(i-j >= 0){
        dp[i][j] = dp[i-j][j] + dp[i][j-1];
      }
      else {
        dp[i][j] = dp[i][i];
      }
      if(i-j-k >= 0){
        dp[i][j] += MOD - dp[i-j-k][j-1];
      }
      dp[i][j] %= MOD;
    }
  }
  return dp[n][m];
}

//https://yukicoder.me/problems/no/269
signed main(){

  int n,s,k; cin >> n >> s >> k;
  s -= (n-1)*k*n/2;
  if(s < 0){
    cout << 0 << endl;
    return 0;
  }
  cout << PartNum(s,n,1<<30) << endl;

  // //https://atcoder.jp/contests/joi2009yo/tasks/joi2009yo_f
  // int n,m,s; cin >> n >> m >> s;
  // n = n*n;
  // s -= n*(n+1)/2;
  // m -= n;
  // cout << PartNum(s,n,m) << endl;

  return 0;
}
