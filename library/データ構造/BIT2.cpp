#include<bits/stdc++.h>
using namespace std;
#ifdef _DEBUG
  #include "_DEBUG.hpp"
#endif
#define int long long

template <class T>
struct BIT{
  int n;
  vector<T> bit; //[1,N]

  BIT(int _n){
    n = _n + 1;
    bit.resize(n,0);
  }

  T sum(int i){
    T sum = 0;
    while(i > 0){
      sum += bit[i];
      i -= i & -i;
    }
    return sum;
  }

  void add(int i,T x){
    while(i < n){
      bit[i] += x;
      i += i & -i;
    }
  }

  // 合計がx以上の最小の位置 O(log^2 n)
  int lower_bound(T x) {
    int left = -1, right = n;
    while(right - left > 1) {
      int mid = (left + right)/2;
      if(sum(mid) >= x) right = mid;
      else left = mid;
    }
    return right;
  }
};

template<class T>
vector<T> compress(vector<T> v){
  sort(v.begin(),v.end());
  v.erase(unique(v.begin(),v.end()),v.end());
  return v;
}

signed main(){

  int q,k; cin >> q >> k;
  vector<int> query(q),v(q),vs;
  for(int i = 0; i < q; i++){
    cin >> query[i];
    if(query[i] == 1) cin >> v[i],vs.push_back(v[i]);
  }
  vs = compress(vs);
  map<int,int> mp;
  for(int i = 0; i < vs.size(); i++){
    mp[vs[i]] = i+1;
  }

  BIT<int> bitval(vs.size());
  BIT<int> bitnum(vs.size());

  for(int i = 0; i < q; i++){
    if(query[i] == 1){
      bitval.add(mp[v[i]],v[i]);
      bitnum.add(mp[v[i]],1);
    }
    else {
      if(bitnum.sum(vs.size()) < k) cout << -1 << endl;
      else {
        int idx = bitnum.lower_bound(k);
        cout << vs[idx-1] << endl;
        bitnum.add(idx,-1);
      }
    }
  }

  return 0;
}

/*
// a[0]+...+a[ret] >= x
int lower_bound(T x){
  int ret = -1;
  int k = 1;
  while(2*k < n) k <<= 1;
  while(k > 0){
    if(ret+k < n && bit[ret+k] < x){
      x -= bit[ret+k];
      ret += k;
    }
    k >>= 1;
  }
  return ret+1;
}
*/
