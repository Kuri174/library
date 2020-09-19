#include<bits/stdc++.h>
using namespace std;
#ifdef LOCAL_DEBUG
  #include "LOCAL_DEBUG.hpp"
#endif
#define int long long

template <class T>
void rot90(vector<vector<T>> &cur){
  int H = cur.size();
  int W = cur[0].size();
  vector<vector<T>> rot(W,vector<T>(H));
  for(int i = 0; i < H; i++){
    for(int j = 0; j < W; j++){
      rot[j][W-1-i] = cur[i][j]; //右回転
      //rot[W-1 - j][i] = cur[i][j]; //左回転
    }
  }
  cur = rot;
}

signed main(){

  int H,W; cin >> H >> W;
  vector<vector<char>> table(H,vector<char>(W));
  for(int i = 0; i < H; i++){
    string s; cin >> s;
    for(int j = 0; j < W; j++){
      table[i][j] = s[j];
    }
  }

  vector<vector<int>> dp(H,vector<int>(W,0));
  for(int k = 0; k < 4; k++){
    for(int i = 0; i < H; i++){
      int cnt = 0;
      for(int j = 0; j < W; j++){
        if(table[i][j] == '.') cnt++;
        else cnt = 0;
        dp[i][j] += cnt;
      }
    }
    rot90(table);
    rot90(dp);
    swap(H,W);
  }

  int ans = 0;
  for(int i = 0; i < H; i++){
    for(int j = 0; j < W; j++){
      ans = max(ans,dp[i][j]);
    }
  }
  cout << max(0LL,ans-3) << endl;

  return 0;
}
