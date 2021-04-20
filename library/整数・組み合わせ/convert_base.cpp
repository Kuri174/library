#include<bits/stdc++.h>
using namespace std;
#ifdef _DEBUG
  #include "_DEBUG.hpp"
#endif
#define int long long

string convert_base(int x, int b){
  if(x == 0) return "0";
  string s;
  int base = 1;
  while(x != 0){
    if(x % (base * b) == 0){
      s += '0';
    }else{
      s += '1';
      x -= base;
    }
    base *= b;
  }
  reverse(s.begin(),s.end());
  return s;
}

signed main(){

  int n, b; cin >> n >> b;
  auto res = convert_base(n, b);
  cout << res << endl;

  return 0;
}
