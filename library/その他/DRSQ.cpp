#include<bits/stdc++.h>
using namespace std;
#define int long long

vector<int> v;

struct LazySegmentTree {
  int n;
  vector<int> node,delay;

  // 元配列 v をセグメント木で表現する
  void init(){
    n = 1; while(n < v.size()) n *= 2;
    node.resize(2*n-1,0);
    delay.resize(2*n-1,0);

    for(int i = 0; i < v.size(); i++) node[i+n-1] = v[i];
    for(int i = n-2; i >= 0; i--) node[i] = node[2*i+1] + node[2*i+2];
  }

  //k番目のノードの遅延評価
  void eval(int k,int l,int r){
    if(delay[k] != 0){
      node[k] += delay[k];
      if(r-l > 1){ //最下段でない場合
        // 子ノードは親ノードの1/2の範囲
        delay[2*k+1] += delay[k] / 2;
        delay[2*k+2] += delay[k] / 2;
      }
    }
    //遅延評価終わり
    delay[k] = 0;
  }

  void add(int a,int b,int x){ add(a,b,x,0,0,n); }
  void add(int a,int b,int x,int k,int l,int r){
    eval(k,l,r);
    if(b <= l || r <= a) return;
    if(a <= l && r <= b){
      delay[k] += (r-l) * x; //手動
      eval(k,l,r);
    }
    else {
      add(a,b,x,2*k+1,l,(l+r)/2);
      add(a,b,x,2*k+2,(l+r)/2,r);
      node[k] = node[2*k+1] + node[2*k+2];
    }
  }

  int getsum(int a,int b) { return getsum(a,b,0,0,n); }
  int getsum(int a,int b,int k ,int l,int r){
    eval(k,l,r);
    if(b <= l || r <= a) return 0;
    if(a <= l && r <= b) return node[k];
    int vl = getsum(a,b,2*k+1,l,(l+r)/2);
    int vr = getsum(a,b,2*k+2,(l+r)/2,r);
    return vl + vr;
  }
}seg;

signed main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int n,q; cin >> n >> q;
  v.resize(n,0);
  for(int i = 0; i < n; i++){

  }
  seg.init();
  for(int i = 0; i < q; i++){
    int query,s,t,x; cin >> query;
    if(query){
      cin >> s >> t;
      cout << seg.getsum(s-1,t) << endl;
    }
    else {
      cin >> s >> t >> x;
      seg.add(s-1,t,x);
    }
  }

  return 0;
}
