#include<bits/stdc++.h>
using namespace std;
#ifdef _DEBUG
  #include "_DEBUG.hpp"
#endif
#define int long long

vector< int > z_algorithm(const string &s) {
  vector< int > prefix(s.size());
  for(int i = 1, j = 0; i < s.size(); i++) {
    if(i + prefix[i - j] < j + prefix[j]) {
      prefix[i] = prefix[i - j];
    } else {
      int k = max(0LL, j + prefix[j] - i);
      while(i + k < s.size() && s[k] == s[i + k]) ++k;
      prefix[i] = k;
      j = i;
    }
  }
  prefix[0] = (int) s.size();
  return prefix;
}

signed main(){

  int n; cin >> n;
  string s; cin >> s;

  int ans = 0;
  for(int i = 0; i < n; i++){
    auto v = z_algorithm(s.substr(i,n));
    for(int j = 1; j < v.size(); j++){
      int res = min(v[j], i+j - i);
      ans = max(ans, res);
    }
  }
  cout << ans << endl;

  return 0;
}
