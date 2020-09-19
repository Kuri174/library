#include<bits/stdc++.h>
using namespace std;
#define int long long

//https://atcoder.jp/contests/chokudai_S001/tasks/chokudai_S001_h
signed main(){

  int n; cin >> n;
  vector<int> a(n);
  for(int i = 0; i < n; i++){
    cin >> a[i];
  }

  SegmentTree<int> seg(vector<int>(n, 0),0,[&](int x,int y){
    return max(x, y);
  });
  for(int i = 0; i < n; i++){
    int res = seg.getval(0, a[i]) + 1;
    seg.update(a[i], max(res,(seg.getval(a[i], a[i]+1))));
  }
  cout << seg.getval(0, n) << endl;

  // multiset<int> st;
  // for(int i = 0; i < n; i++){
  //   auto it = st.lower_bound(a[i]);
  //   if(it != st.begin()){
  //     it--;
  //     st.erase(it);
  //   }
  //   st.insert(a[i]);
  // }
  // cout << st.size() << endl;

  // vector<int> dp(n,1 << 30); //長さをiとしたときの末尾の最小値
  // for(int i = 0; i < n; i++){
  //   int j = lower_bound(dp.begin(),dp.end(),a[i]) - dp.begin();
  //   dp[j] = a[i];
  // }
  // cout << lower_bound(dp.begin(),dp.end(),1 << 30) - dp.begin() << endl;


  return 0;
}
