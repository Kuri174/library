#include<bits/stdc++.h>
using namespace std;
#define int long long

struct BIT{
  int n;
  vector<int> bit; //[1,N]

  void init(int _n){
    n = _n+2;
    bit.resize(n);
  }

  int sum(int i){
    int sum = 0;
    while(i > 0){
      sum += bit[i];
      i -= i & -i;
    }
    return sum;
  }

  void add(int i,int x){
    while(i <= n){
      bit[i] += x;
      i += i & -i;
    }
  }
}bit;

signed main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int n; cin >> n;
  bit.init(n);
  vector<int> v(n),w(n);
  for(int i = 0; i < n; i++){
    cin >> v[i];
    w[i] = v[i];
  }
  sort(w.begin(),w.end());

  map<int,int> mp;
  for(int i = 0; i < n; i++){
    mp[w[i]] = i+1;
  }

  // 反転数
  int ans = 0;
  for(int i = 0; i < n; i++){
    ans += i - bit.sum(mp[v[i]]);
    bit.add(mp[v[i]],1);
  }
  cout << ans << endl;

  return 0;
}
