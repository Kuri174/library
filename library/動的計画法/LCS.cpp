#include<bits/stdc++.h>
using namespace std;
#define int long long

//https://atcoder.jp/contests/dp/tasks/dp_f
signed main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  string s,t; cin >> s >> t;
  static int dp[3001][3001];
  for(int i = 0; i < s.size(); i++){
    for(int j = 0; j < t.size(); j++){
      if(s[i] == t[j]) dp[i+1][j+1] = dp[i][j] + 1;
      else dp[i+1][j+1] = max(dp[i+1][j],dp[i][j+1]);
    }
  }

  string ans;
  int i = s.size(),j = t.size();
  while(dp[i][j] > 0){
    if(dp[i-1][j] == dp[i][j]) i--;
    else if(dp[i][j-1] == dp[i][j]) j--;
    else {
      i--,j--;
      ans += s[i];
    }
  }
  reverse(ans.begin(),ans.end());
  cout << ans << endl;

  return 0;
}
