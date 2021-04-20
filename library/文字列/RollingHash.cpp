#include<bits/stdc++.h>
using namespace std;
#ifdef _DEBUG
  #include "_DEBUG.hpp"
#endif
#define int long long

struct RollingHash{
  const int base1 = 1e3+7, base2 = 1e3+9;
  const int mod1 = 1e9+7, mod2 = 1e9+9;
  vector<int> hash1, hash2, pow1, pow2;

  RollingHash(string s){
    int n = s.size();
    hash1.assign(n+1, 0); hash2.assign(n+1, 0); pow1.assign(n+1, 1); pow2.assign(n+1, 1);
    for(int i = 0; i < n; ++i){
      hash1[i+1] = (hash1[i] * base1 + s[i]) % mod1;
      hash2[i+1] = (hash2[i] * base2 + s[i]) % mod2;
      pow1[i+1] = (pow1[i] * base1) % mod1;
      pow2[i+1] = (pow2[i] * base2) % mod2;
    }
  }

  pair<int, int> getval(int l, int r){
    int res1 = (hash1[r] - hash1[l] * pow1[r-l] % mod1 + mod1) % mod1;
    int res2 = (hash2[r] - hash2[l] * pow2[r-l] % mod2 + mod2) % mod2;
    return {res1, res2};
  }

  int getlcp(int a, int b){
    int left = 0, right = hash1.size() - max(a, b);
    while(right - left > 1){
      int mid = (left + right) / 2;
      (getval(a, a + mid) != getval(b, b + mid) ? right : left) = mid;
    }
    return left;
  }
};

signed main(){

  int n; cin >> n;
  string s; cin >> s;

  RollingHash rh(s);
  auto f = [&](int mid){
    map<pair<int ,int>, int> mp;
    for(int i = 0; i + mid <= n; i++){
      auto p = rh.getval(i, i + mid);
      if(mp.count(p)){
        if(i - mp[p] >= mid) return true;
      }else {
        mp[p] = i;
      }
    }
    return false;
  };

  int left = -1, right = n;
  while(right - left > 1){
    int mid = (left + right) / 2;
    (!f(mid) ? right : left) = mid;
  }
  cout << left << endl;

  return 0;
}
