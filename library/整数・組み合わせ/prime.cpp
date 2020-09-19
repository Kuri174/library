#include<bits/stdc++.h>
using namespace std;
#define int long long

struct Prime{

  vector<int> prime; // 2,3,5,7,11...
  vector<bool> is_prime; // 素数=1,合成数=0
  void eratos(int n){
    is_prime.resize(n+1,true);
    is_prime[0] = is_prime[1] = false;
    for(int i = 2; i <= n; i++){
      if(is_prime[i]){
        prime.push_back(i);
        for(int j = i*2; j <= n; j+=i){
          is_prime[j] = false;
        }
      }
    }
  }

  //因数分解
  map<int,int> prime_factor(int n){
    map<int,int> mp; //{約数,個数}
    for(int i = 2; i*i <= n; i++){
      while(n%i == 0){
        mp[i]++;
        n /= i;
      }
    }
    if(n != 1) mp[n] = 1; //n=素数
    return mp;
  }

  //mpから作れる、約数をちょうどn個もつ数の個数
  int factor_cnt(map<int, int> mp, int n){
    vector<int> dp(n+2); //約数がちょうどi個の数の個数
    dp[1] = 1;
    for(auto p : mp) {
      for(int i = n; i > 0; i--) {
        for(int j = p.second; j > 0; j--) {
          dp[min(n+1, i * (j+1))] += dp[i];
        }
      }
    }
    return dp[n];
  }

}prime;

signed main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int n; cin >> n;
  map<int,int> mp;
  for(int i = 2; i <= n; i++){
    auto p = prime.prime_factor(i);
    for(auto x : p){
      mp[x.first] += x.second;
    }
  }

  cout << prime.factor_cnt(mp,75) << endl;

  return 0;
}
