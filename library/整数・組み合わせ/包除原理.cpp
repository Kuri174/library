#include<bits/stdc++.h>
using namespace std;
#ifdef _DEBUG
  #include "_DEBUG.hpp"
#endif
#define int long long

//1~nの整数で, a1,a2,...amのうち、少なくとも一つで割り切れる個数
signed main(){

  int n, m; cin >> n >> m;
  vector<int> a(m);
  for(int i = 0; i < m; i++) cin >> a[i];

  int ans = 0;
  for(int i = 1; i < 1 << m; i++){
    int num = 0, lcm = 1;
    for(int j = 0; j < m; j++){
      if(i >> j & 1){
        lcm = lcm / __gcd(lcm, a[j]) * a[j];
        if(lcm > n) break;
        num++; //numはビットが立っている数　奇数個:+, 偶数個:-
      }
    }
    ans += n / lcm * (num%2 == 0 ? -1 : 1);
  }
  cout << ans << endl;

  return 0;
}
