#include<bits/stdc++.h>
using namespace std;
#define int long long

struct Combination{

  const int MOD = 1e9+7;

  vector<int> fact; //　fact[i] = iの階乗
  void init(int n){
    fact.resize(n+1);
    fact[0] = fact[1] = 1;
    for(int i = 2; i <= n; i++){
      fact[i] = i * fact[i-1] % MOD;
    }
  }

  int nCr(int n,int r){ // nCr = n!/r!(n-r)!
    return fact[n] * inverse(fact[r]*fact[n-r] % MOD) % MOD;
  }

  int inverse(int n){ // a/n ≡ a*n^(p-2) nとpは互いに素
    int r = 1;
    for(int p = MOD - 2; p > 0; p >>= 1){
      if(p & 1LL) r = (r * n) % MOD;
      n = (n * n) % MOD;
    }
    return r; // r = n^(p-2) % MOD
  }

}nCr;

signed main(){
  cin.tie(0);
  ios::sync_with_stdio(false);
  
  vector< vector<int> > dp; // dp[n][r] = nCr
  dp.resize(n+1,vector<int> (n+1));
  for(int i = 0; i <= n; i++){
    dp[i][0] = 1;
    for(int j = 1; j <= i; j++){
      dp[i][j] = dp[i-1][j-1] + dp[i-1][j];
      dp[i][j] %= MOD;
    }
  }

  // ABC34C 経路
  int W,H; cin >> W >> H;
  if(W+H-2 <= 5000){
    nCr.table(W+H-2);
    cout << nCr.dp[W+H-2][min(W-1,H-1)] << endl;
  }
  else {
    nCr.init(W+H-2);
    cout << nCr.nCr(W+H-2,W-1) << endl;
  }

  return 0;
}
