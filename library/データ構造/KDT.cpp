#include<bits/stdc++.h>
using namespace std;
#define int long long

vector<int> ans;

struct KDT{
  struct point{
    int id,x,y;
    bool operator<(const point &u)const{
      return id < u.id;
    }
  };
  struct node{ int location,l,r; };

  vector<point> P;
  vector<node> T;
  int n,np = 0;

  void init(int n){
    P.resize(n);
    T.resize(n);
  }

  static bool cmpX(const point &a,const point &b){ return a.x < b.x; }
  static bool cmpY(const point &a,const point &b){ return a.y < b.y; }

  int maketree(int l,int r,int depth){
    if(!(l < r)) return -1;
    int mid = (l+r) / 2;
    int t = np++;
    if(depth%2 == 0) sort(P.begin()+l,P.begin()+r,cmpX);
    else sort(P.begin()+l,P.begin()+r,cmpY);
    T[t].location = mid;
    T[t].l = maketree(l,mid,depth+1);
    T[t].r = maketree(mid+1,r,depth+1);
    return t;
  }

  void find(int v,int sx,int tx,int sy,int ty,int depth){
    int x = P[T[v].location].x;
    int y = P[T[v].location].y;
    if(sx <= x && x <= tx && sy <= y && y <= ty){
      ans.push_back(P[T[v].location].id);
    }

    if(depth%2 == 0){
      if(T[v].l != -1){
        if(sx <= x) find(T[v].l,sx,tx,sy,ty,depth+1);
      }
      if(T[v].r != -1){
        if(x <= tx) find(T[v].r,sx,tx,sy,ty,depth+1);
      }
    }
    else {
      if(T[v].l != -1){
        if(sy <= y) find(T[v].l,sx,tx,sy,ty,depth+1);
      }
      if(T[v].r != -1){
        if(y <= ty) find(T[v].r,sx,tx,sy,ty,depth+1);
      }
    }
  }
}kd;

signed main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int n; cin >> n;
  kd.init(n+1);
  for(int i = 0; i < n; i++){
    int x,y; cin >> x >> y;
    kd.P[i] = {i,x,y};
  }
  int root = kd.maketree(0,n,0);

  int q; cin >> q;
  for(int i = 0; i < q; i++){
    int sx,tx,sy,ty; cin >> sx >> tx >> sy >> ty;
    ans.clear();
    kd.find(root,sx,tx,sy,ty,0);
    sort(ans.begin(),ans.end());
    for(int p : ans){
      cout << p << '\n';
    }
    cout << '\n';
  }

  return 0;
}
